#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct info{
	char flight_call [20];
	char *url[256];
}Flight;

typedef struct {

}httpResponse;

char get_url(Flight* flight, char *call){
	sprintf(flight->url,"https://opendata.adsb.fi/api/v2/callsign/%s", flight->flight_call);

	return flight->url;
}