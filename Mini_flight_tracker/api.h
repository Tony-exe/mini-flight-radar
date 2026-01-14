#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "flight_info.h"

void *http_get(){
	CURL *curl = curl_easy_init();
	Flight *response = malloc(sizeof(Flight));

	curl_easy_setopt(curl,CURLOPT_URL, "url");
}