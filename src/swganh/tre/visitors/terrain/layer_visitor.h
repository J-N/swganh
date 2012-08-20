#ifndef SWGANH_TRE_LAYER_VISITOR_H_
#define SWGANH_TRE_LAYER_VISITOR_H_

#include "swganh/tre/visitors/visitor_interface.h"
#include <vector>
#include <list>
#include <stack>

namespace swganh
{
namespace tre
{
	class Layer;
	class ContainerLayer;

	class LayerVisitor : public VisitorInterface
	{
	public:

		~LayerVisitor();

		/**
			@brief returns the VisitorType associated with this visitor
		*/
		virtual VisitorType getType() { return LAY_VISITOR; }

		/**
			@brief interprets a IFF::FileNode associated with this visitor.
			This should only be called by the IFFFile code.
		*/
		virtual void visit_data(uint32_t depth, std::shared_ptr<file_node> node);

		/**
			@brief interprets a IFF::FolderNode associated with this visitor.
			This should only be called by the IFFFile code.
		*/
		virtual void visit_folder(uint32_t depth, std::shared_ptr<folder_node> node);

		std::vector<ContainerLayer*>& GetLayers() { return layers_; }

	private:
		std::stack<std::pair<ContainerLayer*, uint32_t>> layer_stack_;
		Layer* working_layer_;
		std::vector<ContainerLayer*> layers_;
	};
}
}

#endif