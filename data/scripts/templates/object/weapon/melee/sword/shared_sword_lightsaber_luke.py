#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/weapon/melee/sword/shared_sword_lightsaber_luke.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Weapon()
	
		result.template = "object/weapon/melee/sword/shared_sword_lightsaber_luke.iff"
		result.attribute_template_id = 10
		result.stfName("weapon_name","sword_lightsaber_luke")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())