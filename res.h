#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdbool.h>

int counter=0;
int available_callers=8;
int Nseat[250];
int num_available_seats = 250;
int Ntel=8 ;
int Nseatlow=1;
int Nseathigh=5;
int tseatlow=5 ;
int tseathigh=10;
bool Pcard_success;
int Cseat=20 ;
int num_seats;
int result=0;
int num_seconds_servicing=0;
int total_revenue=0;
int tid=0;
struct timespec start,end;
 unsigned int num_seconds_waiting;


void * callers(void* args);
void * customers(void* args);

#endif
