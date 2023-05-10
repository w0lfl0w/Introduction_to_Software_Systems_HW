
#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"


/**
  * @brief Initiates an empty string
  */
String::String() {
	this->length = 0;
	this->data = new char[0];
}


/**
  * @brief Initiates string from other string
  */
String::String(const String& str) {
	this->length = str.length;
	this->data = new char[this->length + 1];
	strcpy(this->data, str.data);
}


/**
  * @brief Initiates a string from char array
  */
String::String(const char* str) {
	this->length = strlen(str);
	this->data = new char[this->length + 1];
	strcpy(this->data, str);
}


String::~String() {
	delete[] this->data;
}


/**
  * @brief Changes this from String
  */
String& String::operator=(const String& rhs) {
	if (this == &rhs) {
		return *this;
	}
	
	delete[] this->data;
	this->data = new char[rhs.length + 1];
	strcpy(this->data, rhs.data);
	this->length = rhs.length; 
	
	return *this;
}


/**
  * @brief Changes this from char array
  */
String& String::operator=(const char* str) {
	if (this->data == str) {
		return *this;
	}
	
	this->length = strlen(str);
	delete[] data;
	this->data = new char[(this->length) + 1];
	strcpy((this->data), str);
	
	return *this;
}


/**
  * @brief Returns true iff the contents of this equals to the
  * contents of rhs
  */
bool String::equals(const String& rhs) const {
	if (strcmp(this->data, rhs.data)) {
		return false;
	}

	return true;
}


/**
  * @brief Returns true iff the contents of this equals to rhs
  */
bool String::equals(const char* rhs) const {
	if (strcmp(this->data, rhs)) {
		return false;
	}

	return true;
}

/**
  * @brief Splits this to several sub-strings according to delimiters.
  * Allocates memory for output that the user must delete (using delete[]).
  * @note Does not affect this.
  * @note If "output" is set to NULL, do not allocated memory, only
  * compute "size".
  */
void String::split(const char* delimiters, String** output, size_t* size) const{

	String tmp_str_1(*this);
	int counter = 0;
	
	/* devide string into tokens according to delimiters and count them*/
	char *token = strtok(tmp_str_1.data, delimiters);

	while (token) {
		counter++;
		token = strtok(NULL, delimiters);
	}
	
	*size = counter;

	if (output == NULL) {
		return;
	}
	
	/* allocate array of pointers to strings*/
	*output = new String[counter];
	
	int i = 0;

	String tmp_str_2 = String(*this);
	token = strtok(tmp_str_2.data, delimiters); 
	
	while (token) {
		
		(*output)[i] = String(token);
		i++;
		
		token = strtok(NULL, delimiters);
	}
	
	return;
}


/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
	char* ptr = this->data;

	if (!ptr) {
		return 0;
	}

	return (atoi(this->data));
}


/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const {
	
	/*find how many spaces there are in the start of the string*/
	size_t i = 0;
	while ((this->data)[i] == ' ') {
		i++;
	}

	/*if string has only whitespaces*/
	if (i == this->length) {
		return NULL;
	}

	/*find how many spaces there are in the end of the string*/
	int j = this->length - 1;
	size_t k = 0;
	while ((this->data)[j] == ' ') {
		j--;
		k++;
	}

	/*use a copy function, from this+i, with a len of j+1-i, 
	to a new string tmp_str*/
	char* new_str = new char[(this->length) - i - k + 1];
	
	for (size_t m = 0; m < (this->length) - i - k; m++) {
		new_str[m] = (this->data)[m];
	}
	new_str[(this->length) - i - k] = '\0';

	String tmp_str = String(new_str);
	delete[] new_str;

	return tmp_str;
}

