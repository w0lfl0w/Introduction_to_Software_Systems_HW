#ifndef IP_H
#define IP_H

#include <stddef.h>

#include "field.h" 
#include "string.h"



class Ip : public Field {
    int ip_rule; 
    int size_of_mask;
    
 
public:
    Ip(String pattern);
    ~Ip();
    bool set_value(String val);
    /* Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
       matches 1.1.*.*) */
    bool match_value(String value) const;
};


#endif
 
