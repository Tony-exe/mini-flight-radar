#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "flight_info.h"

/************ -- API -- ************ */
/* d83f99e238aa5ec4f777cc8fd06b8f1b */
/********************************* */

void *http_get(Flight *flight, char *http){
	CURL *curl = curl_easy_init();
	Flight *response = (Flight *)malloc(sizeof(Flight));

	curl_easy_setopt(curl, CURLOPT_URL, flight->url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_api);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, http);

	CURLcode result = curl_easy_perform(curl);

	if(result != CURLE_OK){
		fprintf(stderr, "download problem");
	}

	curl_easy_cleanup(curl);
}