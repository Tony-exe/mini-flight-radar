#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct info{
	char flight_num [20];
}Flight;

typedef struct {

}httpResponse;

// Callback interno (private)
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    HttpResponse *mem = (HttpResponse *)userp;
    
    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if(!ptr) {
        fprintf(stderr, "not enough memory\n");
        return 0;
    }
    
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;
    
    return realsize;
}