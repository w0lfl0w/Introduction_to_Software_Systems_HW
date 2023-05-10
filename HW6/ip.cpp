#include <iostream>
#include <stddef.h>
#include <bitset>
#include "field.h"
#include "string.h"
#include "ip.h"

const int FIRST_BYTE = 24;
const int SECOND_BYTE = 16;
const int THIRD_BYTE = 8;
const int FOUR_BYTES = 32;

const int VALID_PARAM = 5;

Ip::Ip(String pattern) : Field(pattern) {}

Ip::~Ip() {}

/* Return true if set the rule's "value" successfully */
bool Ip::set_value(String val) {

	String *output;
	size_t size;
	
	val.String::split("., /", &output, &size);
	
	if (size != VALID_PARAM) {
		delete[] output;
		return false;
	}

	/* create mask */
	int curr_ip = (output[0].String::to_integer() << FIRST_BYTE) |
		      (output[1].String::to_integer() << SECOND_BYTE) |
		      (output[2].String::to_integer() << THIRD_BYTE) |
		      (output[3].String::to_integer());
	
	this->size_of_mask =output[4].String::to_integer();
	
	if((size_of_mask < 0) || (size_of_mask > 32)){
		return false;
	}
	
	int mask = curr_ip >> (FOUR_BYTES - (this->size_of_mask));
	mask = mask << (FOUR_BYTES - (this->size_of_mask));
	
	(this->ip_rule) = mask;

	delete[] output;
	return true;
}

/* Returns true iff "value" matches the value of this */
bool Ip::match_value(String value) const {
	
	String* output;
	size_t size;
	
	value.String::split("., ", &output, &size);
	if (size != (VALID_PARAM - 1)) {
		delete[] output;
		return false;
	}
	
	int curr_ip = (output[0].String::to_integer() << FIRST_BYTE) |
		(output[1].String::to_integer() << SECOND_BYTE) |
		(output[2].String::to_integer() << THIRD_BYTE) |
		(output[3].String::to_integer());

	int masked_val = curr_ip >> (FOUR_BYTES - (this->size_of_mask));	
	masked_val = masked_val << (FOUR_BYTES - (this->size_of_mask));

	/*check if the masked ip and the rule is the same, 
	  or if the size_of_mask is 0*/
	if ((!((this->ip_rule) ^ masked_val) || (!size_of_mask))) {
		delete[] output;
		return true;
	}
	
	delete[] output;
	return false;
}
