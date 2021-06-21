#include "jsmn.h"
#include "jsmn_traversal.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#define PICO_ARCH

#ifdef PICO_ARCH
#include <tusb.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/stdio.h"
#endif

#define MAXL 300

/*
 * A small example of jsmn parsing and traversing when JSON structure number of
 * tokens is predictable.
 */

static const char *JSON_STRING =
    "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
    "\"groups\": [\"users\", \"wheel\", \"audio\", {\"type\": \"video\", \"length\": 17} ]}";

int main() {

#ifdef PICO_ARCH	
	stdio_init_all();
    while (!tud_cdc_connected()) {sleep_ms(300);}
	printf("Started \n");
#endif

  int i;
  int r;
  int extra;
  jsmn_parser p;
  jsmntok_t t[200]; /* We expect no more than 200 tokens */
  char mystring[MAXL] ;
  
  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  JSMNobject myJSON(JSON_STRING, &t[0]) ;
  
  /* Assume the top-level element is an object */
  if (r < 1 || myJSON.isOf() != JSMN_OBJECT) {
    printf("Object expected\n");
    return 1;
  } 

  /* Loop over all keys of the root object only traverse first level arrays */
  for (i = 0; i < myJSON.sizeIter() ; i++) {
	myJSON.iterKey(mystring, 30) ;
    printf("%d: key = %s, \n",i,mystring) ;
	myJSON.iterElem().asString(mystring,MAXL) ;
	printf("    value = %s\n", mystring) ;
	if ( myJSON.iterElem().isOf() == JSMN_ARRAY) {
		JSMNobject arr = myJSON.iterElem() ;
		for (int j = 0 ; j < arr.sizeIter() ; j++) {
			arr.iterElem().asString(mystring,MAXL) ;
			printf ("      arrayvalue[%d] = %s\n", j,mystring);
			arr.iterate() ;
		};
	};
	myJSON.iterate() ;
  }
    
	printf ("Parsing Done\n");
  
  myJSON.select("uid").asString(mystring,MAXL);
  printf("Extracted %s\n",mystring);
  myJSON.select("groups").element(3).asString(mystring,MAXL);
  printf("Extracted %s\n",mystring);
  myJSON.select("groups").element(3).select("type").asString(mystring,MAXL);
  printf("Extracted %s\n",mystring);
  
  #ifdef PICO_ARCH
  sleep_ms(1000) ;
  #endif
  
  printf ("Parsing Done\n"); 
  return EXIT_SUCCESS;
}
