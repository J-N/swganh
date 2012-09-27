// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "node.h"

#include <swganh/object/object.h>

std::stringstream current_collision_points;

template <typename Point>
void GetCollisionBoxPoints(Point const& p)
{
	current_collision_points << " " << p.x() << "," << p.y();
}

namespace quadtree
{

Node::Node(NodeQuadrant quadrant, Region region, uint32_t level, uint32_t max_level, Node* parent)
	: quadrant_(quadrant)
	, region_(region)
	, level_(level)
	, max_level_(max_level)
	, state_(LEAF)
	, parent_(parent)
	, leaf_nodes_()
{
	// If this is the root node, we need to do an initial split.
	if(quadrant_ == ROOT)
		Split();
}

Node::~Node(void)
{
}

void Node::InsertObject(std::shared_ptr<swganh::object::Object> obj)
{
	obj->BuildSpatialProfile();

	// If the amount of objects contained is equal to or exceeds (in the case of objects not fitting
	// completely into one node), and we havn't reached the "maximum level" count, and we are a LEAF
	// node, Split().
	if(objects_.size() >= 1 && level_ < max_level_ && state_ == LEAF)
	{
		Split();
	}

	// Flipped to true if a child node of proper size was found to
	// contain the object. Otherwise, the object will be added to 
	// this node.
	bool success = false;

	if(state_ == BRANCH)
	{
		std::for_each(leaf_nodes_.begin(), leaf_nodes_.end(), [=, &obj, &success](std::shared_ptr<Node> node){
			// If we can fit within the node, traverse.
			if(boost::geometry::within( obj->GetWorldBoundingVolume(), node->GetRegion() ))
			{
				node->InsertObject(obj);
				success = true;
				return;
			}
		});
	}

	if(success)
		return;


	objects_.insert(obj);
}

void Node::RemoveObject(std::shared_ptr<swganh::object::Object> obj)
{
	// Search this node for the object by id, if it it found
	// we can return;
	for(auto i = objects_.begin(); i != objects_.end(); )
	{
		if(obj->GetObjectId() == (*i)->GetObjectId())
		{
			i = objects_.erase(i);
			return;
		}
		i++;
	}

	// We didn't find the object in this branch, traverse through
	// each leaf node if we are a BRANCH.
	if(state_ == BRANCH)
	{
		auto bounding_volume = obj->GetWorldBoundingVolume();
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			// If we can actually fit inside the node, traverse farther.
			if(boost::geometry::within(bounding_volume, node->GetRegion()))
			{
				node->RemoveObject(obj);
				return;
			}
		}
	}
}

void Node::Split()
{
	if(state_ == BRANCH)
		return;

	state_ = BRANCH;

	Point center((region_.min_corner().x() + region_.max_corner().x()) / 2, (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point upper_center((region_.min_corner().x() + region_.max_corner().x()) / 2, region_.max_corner().y());
	Point left_center(region_.min_corner().x(), (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point right_center(region_.max_corner().x(), (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point bottom_center((region_.min_corner().x() + region_.max_corner().x()) / 2, region_.min_corner().y());

	leaf_nodes_[NW_QUADRANT] = std::make_shared<Node>(NW_QUADRANT, Region(left_center, upper_center), level_ + 1, max_level_, this);
	leaf_nodes_[NE_QUADRANT] = std::make_shared<Node>(NE_QUADRANT, Region(center, region_.max_corner()), level_ + 1, max_level_, this);
	leaf_nodes_[SW_QUADRANT] = std::make_shared<Node>(SW_QUADRANT, Region(region_.min_corner(), center), level_ + 1, max_level_, this);
	leaf_nodes_[SE_QUADRANT] = std::make_shared<Node>(SE_QUADRANT, Region(bottom_center, right_center), level_ + 1, max_level_, this);

	for(auto i = objects_.begin(); i != objects_.end();)
	{
		auto obj = (*i);
		auto bounding_volume = obj->GetWorldBoundingVolume();
		bool success = false;
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			if(boost::geometry::within(bounding_volume , node->GetRegion()))
			{
				i = objects_.erase(i);
				node->InsertObject(std::move(obj));
				success = true;
				break;
			}
		}

		if(!success)
			i++;
	}
}

std::list<std::shared_ptr<swganh::object::Object>> Node::Query(QueryBox query_box)
{
	std::list<std::shared_ptr<swganh::object::Object>> return_list;

	std::for_each(objects_.begin(), objects_.end(), [=,& return_list](std::shared_ptr<swganh::object::Object> obj) {
		if(boost::geometry::intersects(obj->GetWorldBoundingVolume(), query_box))
			return_list.push_back(obj);
	});

	if(state_ == BRANCH)
	{
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			// Node is within Query Box.
			if(boost::geometry::within(node->GetRegion(), query_box))
			{
				return_list.splice(return_list.end(), node->GetContainedObjects());
				continue;
			}
			
			// Query Box is within node.
			if(boost::geometry::within(query_box, node->GetRegion()))
			{
				return_list.splice( return_list.end(), node->Query(query_box) );
				break;
			}

			// Query Box intersects with node.
			if(boost::geometry::intersects(query_box, node->GetRegion()))
			{
				return_list.splice( return_list.end(), node->Query(query_box) );
			}
		}
	}

	return return_list;
}

std::list<std::shared_ptr<swganh::object::Object>> Node::GetContainedObjects(void)
{
	std::list<std::shared_ptr<swganh::object::Object>> objs(objects_.begin(), objects_.end());
	if(state_ == BRANCH)
	{
		for(const std::shared_ptr<Node> node : leaf_nodes_)
		{
			objs.splice(objs.end(), node->GetContainedObjects());
		}
	}
	return objs;
}

void Node::UpdateObject(std::shared_ptr<swganh::object::Object> obj, const swganh::object::BoundingVolume& old_bounding_volume, const swganh::object::BoundingVolume& new_bounding_volume)
{
	// Check the objects of this node.
	for(auto i = objects_.begin(); i != objects_.end(); i++) {
		auto node_obj = (*i);
		if(node_obj->GetObjectId() == obj->GetObjectId())
		{
			// If we are in the same node, we don't need to do anything.
			if(boost::geometry::within(new_bounding_volume, region_))
			{
				return;
			}

			// Move our object from this node to a new node.
			std::shared_ptr<Node> node = GetRootNode_()->GetNodeContainingVolume_(new_bounding_volume);
			objects_.erase(i);
			node->InsertObject(obj);
			return;
		}
	};

	if(state_ == BRANCH)
	{
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			// Go further into the tree if our point is within our child node.
			if(boost::geometry::within(old_bounding_volume, node->GetRegion()))
			{
				node->UpdateObject(obj, old_bounding_volume, new_bounding_volume);
				return;
			}
		}
	}
}

std::shared_ptr<Node> Node::GetNodeContainingVolume_(swganh::object::BoundingVolume volumn)
{
	// If we don't within the actual Spatial Indexing area, bail.
	if(!boost::geometry::within(volumn, region_))
		throw new std::runtime_error("Quadtree: Object position out of bounds.");

	if(state_ == BRANCH)
	{
		// See if we can fit inside leaf_nodes_
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			if(boost::geometry::within(volumn, node->GetRegion()))
			{
				return node->GetNodeContainingVolume_(volumn);
			}
		}
	}

	// If not, we are between or in this node.
	return std::shared_ptr<Node>(shared_from_this());
}

void Node::SvgDump(void)
{
	std::ofstream file;
	file.open("swganh_si_dump.svg");
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1440\" height=\"900\" version=\"1.1\" viewBox=\"-8300 -8300 16600 16600\" overflow=\"visible\">\n";
	
	file << "<g transform=\"scale(1 -1)\">\n";
	SvgDumpRegions(file);
	file << "<" << '/' << "g>\n";
	
	file << "<g transform=\"scale(1 -1)\">\n";
	SvgDumpObjects(file);
	file << "<" << '/' << "g>\n";

	file << "<" << '/' << "svg>";
	file.close();
}

void Node::SvgDumpRegions(std::ofstream& file)
{
	std::stringstream region_points;
	boost::geometry::box_view<Region> box_view(region_);
	for(boost::range_iterator<boost::geometry::box_view<Region> const>::type it = boost::begin(box_view); it != boost::end(box_view); ++it)
	{
		region_points << " " << (float)(*it).x() << "," << (float)(*it).y();
	}

	file << "<polygon points=\"" << region_points.str() << "\" style=\"fill-opacity:0;fill:none;stroke:green;stroke-width:5px\"" << '/' << "> \n";

	if(state_ == BRANCH)
	{
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			if(node != nullptr)
				node->SvgDumpRegions(file);
		}
	}
}

void Node::SvgDumpObjects(std::ofstream& file)
{

	for(std::shared_ptr<swganh::object::Object> obj : objects_)
	{
		std::stringstream bounding_volume_points;

		auto bounding_volume = obj->GetWorldBoundingVolume();
		auto collision_box = obj->GetWorldCollisionBox();

		current_collision_points = std::stringstream();
		boost::geometry::for_each_point(collision_box, GetCollisionBoxPoints<Point>);
		
		boost::geometry::box_view<swganh::object::BoundingVolume> bounding_volume_view(bounding_volume);
		for(boost::range_iterator<boost::geometry::box_view<swganh::object::BoundingVolume>>::type it = boost::begin(bounding_volume_view); it != boost::end(bounding_volume_view); ++it) 
		{
			bounding_volume_points << " " << (*it).x() << "," << (*it).y();
		}

		auto name = obj->GetCustomName();
		file << "<text x=\"" << obj->GetPosition().x << "\" y=\"" << obj->GetPosition().z << "\" fill=\"black\" style=\"text-anchor: middle;\" >" << std::string(name.begin(), name.end()) << "<" << '/' << "text>\n";
		file << "<polygon points=\"" << bounding_volume_points.str() << "\" style=\"fill-opacity:0;fill:none;stroke:red;stroke-width:0.4px\"" << '/' << "> \n";
		file << "<polygon points=\"" << current_collision_points.str() << "\" style=\"fill-opacity:0;fill:none;stroke:blue;stroke-width:0.4px\"" << '/' << "> \n";
	}

	if(state_ == BRANCH)
	{
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			if(node != nullptr)
				node->SvgDumpObjects(file);
		}
	}
}

} // namespace quadtree