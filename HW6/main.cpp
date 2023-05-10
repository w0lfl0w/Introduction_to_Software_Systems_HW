#include <iostream>
#include <stddef.h>

#include "input.h"
#include "field.h"
#include "string.h"
#include "port.h"
#include "ip.h"

int main(int argc, char** argv) {
	/*check if arguments are valid*/
	if (check_args(argc, argv)) {
		return false;
	}
	
	String *output;
	size_t size;
	
	/*prepare new rule for parsing*/
	String new_rule = String(argv[1]);
	String trimmed_rule = new_rule.String::trim();

	trimmed_rule.String::split("=, ", &output, &size);
	
	String trimmed_pattern = (output[0]).String::trim();
	String trimmed_data = (output[1]).String::trim();

	/*if rule is about port*/
	if (((trimmed_pattern).String::equals("src-port")) ||
		((trimmed_pattern).String::equals("dst-port"))) {

		Port curr_port(trimmed_pattern); 
				
		curr_port.Port::set_value(trimmed_data);
	
		parse_input(curr_port);
	}
	/*if rule is about ip address*/
	else if (((trimmed_pattern).String::equals("src-ip")) ||
			((trimmed_pattern).String::equals("dst-ip"))) {
		
		Ip curr_ip = Ip(trimmed_pattern);
		
		curr_ip.Ip::set_value(trimmed_data);

		parse_input(curr_ip);
	}

	/*free allcated data*/
	delete[] output;

	return true;
}
