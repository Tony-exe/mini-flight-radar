#include "flight_info.h"



Flight *get_url(Flight* flight, char *call){
	sprintf(flight->url,"https://api.aviationstack.com/v1/flights?access_key=d83f99e238aa5ec4f777cc8fd06b8f1b&flight_iata=%s", flight->flight_call);
	flight->url[strcspn(flight->url, "\n")] = 0;
	return flight;
}

size_t callback_api(void *buffer, size_t itemsize, size_t nitems, void* userp){
	size_t rsize = itemsize * nitems;
	char *http = (char*) userp;
    strncat(http, (char *)buffer, rsize);
	return rsize;
}

/*================================ JSON PARSING ==============================================*/

Flight_info *json_parse(Flight_info *flight, char *response){
    cJSON *json = cJSON_Parse(response);

    if(!json) return flight;

    cJSON *data_array = cJSON_GetObjectItem(json, "data");
    if(!data_array || !data_array->child){
        cJSON_Delete(json);
        return flight;
    }

    cJSON *flight_data = data_array->child;
    cJSON *item;

    //============== DATA ===============//
    
    /*=== DATE ===*/
    item = cJSON_GetObjectItem(flight_data, "flight_date");
    if(item && item->valuestring){
        strncpy(flight->base->flight_date, item->valuestring, sizeof(flight->base->flight_date)-1);
    }

    /*=== STATUS ===*/
    item = cJSON_GetObjectItem(flight_data, "flight_status");
    if(item && item->valuestring){
        strncpy(flight->base->flight_status, item->valuestring, sizeof(flight->base->flight_status)-1);
    }

    //============== FLIGHT ===============//
    cJSON *flight_obj= cJSON_GetObjectItem(flight_data, "flight");
    if(flight_obj){
        /*=== IATA ===*/
        item = cJSON_GetObjectItem(flight_obj, "iata");
        if(item && item->valuestring){
        strncpy(flight->base->flight_iata, item->valuestring, sizeof(flight->base->flight_iata)-1);
        }
    }

    //============== AIRLINE ===============//
    cJSON *airline_obj= cJSON_GetObjectItem(flight_data, "airline");
    if(airline_obj){
        /*=== NAME ===*/
        item = cJSON_GetObjectItem(airline_obj, "name");
        if(item && item->valuestring){
        strncpy(flight->base->airline_name, item->valuestring, sizeof(flight->base->airline_name)-1);
        }
    }

    //============== LIVE ===============//
    cJSON *live_obj= cJSON_GetObjectItem(flight_data, "live");
    if(live_obj){
        /*=== IS_GROUND ===*/
        item = cJSON_GetObjectItem(flight_obj, "is_ground");
        if(item && item->type == cJSON_True){
            flight->base->is_ground = 1;
        }else if (item && item->type == cJSON_False){
            flight->base->is_ground = 0;
        }
    }

    if(flight->fase == 1){
        /* ==================== ARRIVAL ====================== */
        cJSON *arrival_obj= cJSON_GetObjectItem(flight_data, "arrival");
        if(arrival_obj){
            /*=== AIRPORT ===*/
            item = cJSON_GetObjectItem(arrival_obj, "airport");
            if(item && item->valuestring){
                strncpy(flight->airport, item->valuestring, sizeof(flight->airport)-1);
            }

            /*=== IATA ===*/
            item = cJSON_GetObjectItem(arrival_obj, "iata");
            if(item && item->valuestring){
                strncpy(flight->iata, item->valuestring, sizeof(flight->iata)-1);
            }

            /*=== SCHEDULED ===*/
            item = cJSON_GetObjectItem(arrival_obj, "scheduled");
            if(item && item->valuestring){
                strncpy(flight->time_scheduled, item->valuestring, sizeof(flight->time_scheduled)-1);
            }   

            /*=== ESTIMATED ===*/
            item = cJSON_GetObjectItem(arrival_obj, "estimated");
            if(item && item->valuestring){
                strncpy(flight->time_estimated, item->valuestring, sizeof(flight->time_estimated)-1);
            }

            /*=== ACTUAL ===*/
            item = cJSON_GetObjectItem(arrival_obj, "actual");
            if(item && item->valuestring){
                strncpy(flight->time_actual, item->valuestring, sizeof(flight->time_actual)-1);
            }

            item = cJSON_GetObjectItem(arrival_obj, "delay");
            if (item && item->type == cJSON_Number) {
                flight->delay = item->valueint;
            }
        }
    }else{
        /* ==================== DEPARTURE ====================== */
        cJSON *departure_obj= cJSON_GetObjectItem(flight_data, "departure");
        if(departure_obj){
            /*=== AIRPORT ===*/
            item = cJSON_GetObjectItem(departure_obj, "airport");
            if(item && item->valuestring){
                strncpy(flight->airport, item->valuestring, sizeof(flight->airport)-1);
            }

            /*=== IATA ===*/
            item = cJSON_GetObjectItem(departure_obj, "iata");
            if(item && item->valuestring){
                strncpy(flight->iata, item->valuestring, sizeof(flight->iata)-1);
            }

            /*=== SCHEDULED ===*/
            item = cJSON_GetObjectItem(departure_obj, "scheduled");
            if(item && item->valuestring){
                strncpy(flight->time_scheduled, item->valuestring, sizeof(flight->time_scheduled)-1);
            }

            /*=== ESTIMATED ===*/
            item = cJSON_GetObjectItem(departure_obj, "estimated");
            if(item && item->valuestring){
                strncpy(flight->time_estimated, item->valuestring, sizeof(flight->time_estimated)-1);
            }

            /*=== ACTUAL ===*/
            item = cJSON_GetObjectItem(departure_obj, "actual");
            if(item && item->valuestring){
                strncpy(flight->time_actual, item->valuestring, sizeof(flight->time_actual)-1);
            }

            item = cJSON_GetObjectItem(departure_obj, "delay");
            if (item && item->type == cJSON_Number) {
                flight->delay = item->valueint;
            }
        }
    }

    cJSON_Delete(json);

    return flight;
}