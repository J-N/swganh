#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/tangible/loot/loot_schematic/shared_tanning_hide_s02_schematic.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Tangible()
	
		result.template = "object/tangible/loot/loot_schematic/shared_tanning_hide_s02_schematic.iff"
		result.attribute_template_id = -1
		result.stfName("craft_item_ingredients_n","tanning_hide_s02")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())