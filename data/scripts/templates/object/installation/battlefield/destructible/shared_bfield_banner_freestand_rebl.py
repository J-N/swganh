#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/installation/battlefield/destructible/shared_bfield_banner_freestand_rebl.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Installation()
	
		result.template = "object/installation/battlefield/destructible/shared_bfield_banner_freestand_rebl.iff"
		result.attribute_template_id = -1
		result.stfName("battlefield","rebel_banner")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())