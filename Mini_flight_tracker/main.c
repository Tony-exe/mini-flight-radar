#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
//CUSTOM HEADERS
#include "flight_info.h"
#include "ui.h"
#include "api.h"

pthread_mutex_t lock_data = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_updated = PTHREAD_COND_INITIALIZER;

void ui_print(char *response, Flight_info *dep, Flight_info *arr){
	dep = json_parse(dep, response);
	arr = json_parse(arr, response);
	print_data_header();
	print_data(dep, arr);

}

int main(int argc, char argv)
{
	CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
	if(result) {
    	fprintf(stderr, "curl_global_init failed\n");
    	return 1;
	}

	Flight *to_track = malloc(sizeof(Flight));
	Flight_info *departure = malloc(sizeof(Flight_info));
	Flight_info *arrival = malloc(sizeof(Flight_info));
	departure->base = arrival->base = to_track;
	departure->fase = 0;
	arrival->fase = 1;

	opening();
	fgets(to_track->flight_call, 20, stdin);
	to_track->flight_call[strcspn(to_track->flight_call, "\n")] = 0;

	get_url(to_track, to_track->flight_call);
	char response [4096]; //4 KB max
	http_get(to_track, response);

	ui_print(response, departure, arrival);

	//printf("\n\n%s", response);

}