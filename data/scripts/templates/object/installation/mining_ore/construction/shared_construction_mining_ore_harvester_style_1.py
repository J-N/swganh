#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_1.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Installation()
	
		result.template = "object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_1.iff"
		result.attribute_template_id = -1
		result.stfName("player_structure","temporary_structure")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())