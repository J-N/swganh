#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/building/endor/shared_endor_lake_platform_cap.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Building()
	
		result.template = "object/building/endor/shared_endor_lake_platform_cap.iff"
		result.attribute_template_id = -1
		result.stfName("building_name","endor_lake_platform")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())