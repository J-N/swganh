#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *

class Template(BaseTemplate):
	name = "object/building/poi/hq/shared_rebel_med.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Building()
	
		result.template = "object/building/poi/hq/shared_rebel_med.iff"
		result.attribute_template_id = -1
		result.stfName("poi_n","hq_rebel_med")		
		
		#### BEGIN MODIFICATIONS ####
		####  END MODIFICATIONS  ####
		
		return result

def loadTemplates(addTemplate):
	addTemplate(Template())