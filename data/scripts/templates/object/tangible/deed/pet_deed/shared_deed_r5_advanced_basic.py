#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *	

def create(kernel):
	result = Tangible()

	result.template = "object/tangible/deed/pet_deed/shared_deed_r5_advanced_basic.iff"
	result.attribute_template_id = 2
	result.stfName("deed","r5_advanced_basic_deed")		
	
	#### BEGIN MODIFICATIONS ####
	result.setStringAttribute("radial_filename", "radials.deed_datapad")
	result.setStringAttribute("deed_result", "object/intangible/pet/shared_r5_crafted.iff")
	####  END MODIFICATIONS  ####
	
	return result