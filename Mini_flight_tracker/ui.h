#include <stdio.h>
#include <string.h>
#include <math.h>

void opening(){
	/* PLANE ASCII */

    system("cls");

	printf("\n\n                                       |\n"
       "                                       |\n"
       "                                       |\n"
       "                                     .-'-.\n"
       "                                    ' ___ '\n"
       "                          ---------'  .-.  '---------\n"
       "          _________________________'  '-'  '_________________________\n"
       "           ''''''-|---|--/    \\==][^',_m_,'^][==/    \\--|---|-''''''\n"
       "                         \\    /  ||/   H   \\||  \\    /\n"
       "                          '--'   OO   O|O   OO   '--'\n\n");
	printf("/******************************************************************************/\n");
	printf("         ************** WELCOME TO MINI FLIGHT TRACKER! ***************\n"
			"Please type the flight number you wanna track: ");
}

void print_data_header(){
    printf("\n");
    printf("\t\t/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/\n");
    printf("\t\t/*=*=*=*=*         ALL FLIGHT DATA HERE        *=*=*=*=*/\n");
    printf("\t\t/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/\n");
}

void print_data(Flight_info *dep, Flight_info *arr){
    printf("\n");
    printf("*=*=*=*=*=*=*=*=*  AIRLINE: %s  *=*=*=*=*=*=*=*=*\n\n",dep->base->airline_name);
    printf("- Flight number:\t%s\n", dep->base->flight_iata);
    printf("- Flight route:\t%s - %s\n", dep->iata, arr->iata);
    printf("- Flight date:\t%s\n", dep->base->flight_date);
    printf("- Flight status:\t%s\n", dep->base->flight_status);
    if(dep->base->is_ground == 1){
        printf("- Is ground:\ton ground\n");
    }else{
        printf("- Is ground:\tin air\n");
    }

    printf("\n============== DEPARTURE INFO =================\n");
    printf("- Airport:\t%s - %s\n", dep->airport, dep->iata);
    printf("- Scheduled departure time:\t%s\n", dep->time_scheduled);
    printf("- Estimated departure time:\t%s\n", dep->time_estimated);
    printf("- Actual departure time:\t%s\n", dep->time_actual);
    printf("- Delay:\t%d\n", dep->delay);

    printf("\n============== ARRIVAL INFO =================\n");
    printf("- Airport:\t%s - %s\n", arr->airport, arr->iata);
    printf("- Scheduled departure time:\t%s\n", arr->time_scheduled);
    printf("- Estimated departure time:\t%s\n", arr->time_estimated);
    printf("- Actual departure time:\t%s\n", arr->time_actual);
    printf("- Delay:\t%d\n", arr->delay);
}
