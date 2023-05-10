#include <iostream>
#include <stddef.h>

#include "field.h"
#include "string.h"
#include "port.h"

const unsigned short VALID_PARAM = 2;
const unsigned short MAX_SHORT = 65535;

Port::Port(String pattern) : Field(pattern) {}

Port::~Port() {}

/* return true is set rule's value successfully */
bool Port::set_value(String val) {
	
	String* output;
	size_t size;
	val.String::split("-, ", &output, &size);
	if (size != VALID_PARAM) {
		delete[] output;
		return false;
	}

	int lower_tmp = output[0].String::to_integer();
	int upper_tmp = output[1].String::to_integer();
	/* if rule is not valid */
	if ((upper_tmp > MAX_SHORT) || (lower_tmp < 0) || 
		(lower_tmp > MAX_SHORT) || (upper_tmp < 0)) {
		delete[] output;
		return false;
	}

	this->lower_bound = (unsigned short)lower_tmp;
	this->upper_bound = (unsigned short)upper_tmp;

	delete[] output;
	return true;
}

/* Returns true iff "value" matches the value of this */
bool Port::match_value(String value) const {

	int tmp_port = value.String::to_integer();
	
	if ((tmp_port > MAX_SHORT) || (tmp_port < 0)) {
		return false;
	}

	unsigned short curr_port = (unsigned short)tmp_port;
	/* check if value matches this */
	if ((curr_port > (this->upper_bound)) || 
		(curr_port < (this->lower_bound))) {
		return false;
	}
	return true;
}
