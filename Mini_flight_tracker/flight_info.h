#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct info{
	char flight_call [20];
	char url[256];

	//data
	char flight_date[20];
	char flight_status[20];
	
	//flight
	char flight_iata[50];

	//airline
	char airline_name[50];
	
	//live
	int is_ground;
}Flight;

typedef struct flight_info{
	Flight *base;
	int fase;
	char airport[50];
	char iata[10];
	char time_scheduled[30];
    char time_estimated[30];
	char time_actual[30];
	int delay;
}Flight_info;


Flight *get_url(Flight* flight, char *call);

size_t callback_api(void *buffer, size_t itemsize, size_t nitems, void* qualcosa);

Flight_info *json_parse(Flight_info *flight, char *response);