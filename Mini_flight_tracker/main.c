#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "flight_info.h"
#include "ui.h"

pthread_mutex_t lock_data = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_updated = PTHREAD_COND_INITIALIZER;

void *fetch_data(void* arg){

}

int main(int argc, char argv)
{
	CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
	if(result) {
    	fprintf(stderr, "curl_global_init failed\n");
    	return 1;
	}

	Flight *to_track = malloc(sizeof(Flight));
	


	opening();
	fgets(to_track->flight_call, 20, stdin);
	printf("String: %s", to_track->flight_call);
	get_url(to_track, to_track->flight_call);
	printf("\nAPI URL: %s", to_track->url);



	
	pthread_t worker_t;
	pthread_create(&worker_t, NULL, fetch_data, to_track);
	
	while(1){
		pthread_cond_wait(&data_updated, &lock_data);
	}
	
	pthread_join(worker_t,NULL);

}