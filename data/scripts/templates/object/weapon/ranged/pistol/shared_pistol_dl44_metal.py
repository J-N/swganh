#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/weapon/ranged/pistol/shared_pistol_dl44_metal.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Weapon()
	
		result.template = "object/weapon/ranged/pistol/shared_pistol_dl44_metal.iff"
		result.attribute_template_id = 10
		result.stfName("weapon_name","pistol_dl44_metal")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())