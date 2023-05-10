#ifndef PORT_H
#define PORT_H

#include <stddef.h>
#include "string.h"
#include "field.h"


class Port : public Field {
    unsigned short upper_bound;
    unsigned short lower_bound;

public:
    Port(String pattern);
    ~Port();
    bool set_value(String val) ;
    /* Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
       matches 1.1.*.*) */
    bool match_value(String value) const;

};


#endif
