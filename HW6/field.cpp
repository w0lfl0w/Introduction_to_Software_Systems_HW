
#include "field.h"
#include "string.h"


Field::Field(String pattern) {
	this->pattern = pattern;

}

Field::~Field() {}

/* Returns true iff "packet" matches "this" */
bool Field::match(String packet) {

	String *output;
	size_t size;
	
	bool is_match;
	packet.split("=, ", &output, &size);
	
	for(size_t i = 0; i < size ; i++){
		/*check if packet matches this*/
		if((output[i]).equals(pattern)) {
			is_match = this->match_value(output[i+1]);
			delete[] output;
			return is_match;
		}
	}
	
	delete[] output;
	return false;
}
