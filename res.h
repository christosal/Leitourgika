#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdbool.h>

int counterForSeatsZoneA=0;
int counterForSeatsZoneB=0;
int counterForSeatsZoneC=0;
int const Nseat=10;
int const NzoneA=5;
int const NzoneB=10;
int const NzoneC=10;
int PzoneA=2; // random in [1,2] out of 10 possibilities
float PzoneB=6; // random in [3,4,5,6] out of 10 possibilities
float PzoneC=10; // random in [7,8,9,10] out of 10 possibilities
int Ntel=8;
int Ncash=4;
int Nseatlow=1;
int Nseathigh=5;
int tseatlow=5 ;
int tseathigh=10;
int tcashlow=2;
int tcashhigh=4;
float Pcard_success=0.9;
int CzoneA=30;
int CzoneB=25;
int CzoneC=20;
int result=0;
int total_revenue=0;
int tid=0;
int TheatrePlanZoneA[NzoneA][Nseat];
int TheatrePlanZoneB[NzoneB][Nseat];
int TheatrePlanZoneC[NzoneC][Nseat];
struct timespec start,end;
float average_time_waiting=0.0f;
float average_time_servicing=0.0f;

int reserveSeats(int numberOfReservedSeats,int id);
void * callers(void* args);
void * customers(void* args);

#endif
