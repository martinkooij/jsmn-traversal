# jsmn-traversal
 Traversing JSON tokens from JSMN parsing

# Usage
 Use the tokenizer by zserge: https://github.com/zserge/jsmn
 This only needs the header file jsmn.h to be inlcude in your project. 
 
 Use the traverser in c++ from this repository. You only need to include jsmn_traversal.hpp
 
In short by inlcuding jsmn.h and jsmn_traversal.cpp you have a lightweight parser and traversal. 

# Functionality
For use of jsmn see https://github.com/zserge/jsmn. 

Methods from the traverser:

````
// Constructor:
//Pointers to the jason string that was parsed and the start token of the JSON object
JSMNobject(const char * str, jsmntok_t * token_start);  


//Methods on an object:
//Type of token 
jsmntype_t isOf();

//Is token of type undefined?
bool isUndef(); 

//return the integer value	
int asInt() {

//return the string value in the string pointed to by str, with maxlength
int asString(char * str, int maxlength); 

//return the bool value	
bool asBool();
	
//return true if null jason value
bool isNULL();
	
//return the raw pointer to the jsmn token value
jsmntok_t * asToken() ;

// return the size of an iterable (OBJECT: number of "fields", ARRAY: number of itenms)
int sizeIter();

// Each iterable JSON element has a built-in iterator that is default at the first subelement. 
// Each call to iterate()  advances this internal iterator one step, and wraps to beginning again if at end. 
// You can call iterate() endlessly, it will just wrap. 
// Iterate() works on OBJECT -- cycling through the "fields" -- and ARRAY --cycling through the elements
void iterate();
	
// Get the Key of the current iterator element (if we are iterating through an JSON OBJRECT)
void iterKey(char * str, int maxlength);
    
// get the JSON object of the current iterator (in case OBJECT the value of beloging to the key, in case of ARRAY the current element)
JSMNobject iterElem();
	
// select the value of the OBJECT with field name str. If not present return the undef object. 
JSMNobject select (const char * str);
 
// select the element's value of an ARRAY, 0 = first. 	
JSMNobject element(int el);
````

# Example
An example cross-compiling for the pi pico is added. By removing #PICO_ARCH definition it should work for all platforms, but mind the include dircetories.  

