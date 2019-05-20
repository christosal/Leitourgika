#include "res.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _POSIX_TIMERS
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>


pthread_mutex_t caller_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t average_time_waiting_callers_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t average_time_service_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t plan_zoneA_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t plan_zoneB_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t plan_zoneC_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t screen_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int planChooser;



void * callers(void *args){
	

	int rc;
	int id = *(int*) args;


	rc = pthread_mutex_lock(&caller_mutex);

	
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}

	int randomNumber = (rand()%9)+1;
	if (randomNumber<=PzoneA){
		planChooser=1;
	}else if (randomNumber<=PzoneB){
		planChooser=2;
	}else{
		planChooser=3;
	}

	int seats= (rand() % (Nseathigh-1)) + Nseatlow;

	switch (planChooser)
	{
	case (1):
		printf("Πελάτης %u, καλεί και θέλει %d θέσεις στην ζώνη %c\n",id,seats,'A');
		break;
	case (2):
		printf("Πελάτης %u, καλεί και θέλει %d θέσεις στην ζώνη %c\n",id,seats,'B');
		break;
	case (3):
		printf("Πελάτης %u, καλεί και θέλει %d θέσεις στην ζώνη %c\n",id,seats,'C');
		break;
	}
	
	
	time_t start=time(NULL);
	
	//sleep(1);
	while (Ntel== 0) {	
		rc = pthread_cond_wait(&cond, &caller_mutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}

	Ntel-=1;
	printf("Πελάτης %d, εξυπηρετείται... Τηλεφωνητές = %d\n",id,Ntel);

	switch (planChooser)
	{
	case (1):
		counterForSeatsZoneA+=seats;
		break;
	case (2):
		counterForSeatsZoneB+=seats;
		break;
	case (3):
		counterForSeatsZoneC+=seats;
		break;
	}
	
	time_t end = time(NULL);
	pthread_mutex_unlock(&caller_mutex);

	pthread_mutex_lock(&average_time_waiting_callers_mutex);
		average_time_waiting+= (end-start);
	pthread_mutex_unlock(&average_time_waiting_callers_mutex);

			
	

	
	time_t start2 = time(NULL);
	if (checkForAvailableSeats(planChooser,seats)){
		if (planChooser==1){
			pthread_mutex_lock(&plan_zoneA_mutex);
				int Nreserved[seats];
				for (int y=0;y<seats;y++){
					Nreserved[y]=reserveSeats(seats,planChooser,id);
				}
			pthread_mutex_unlock(&plan_zoneA_mutex);

			int num_seconds = (rand() % (tseathigh-1)) + tseatlow;
			
		}
	}

	if(counter<=num_available_seats){
			
			pthread_mutex_lock(&plan_mutex);
			int Nreserved[seats];
			for (int y=0;y<seats;y++){
				Nreserved[y]=reserveSeats(seats,id);
			}
			pthread_mutex_unlock(&plan_mutex);
			
			int num_seconds = rand() % tseathigh + tseatlow;
			sleep(num_seconds);
			
			pthread_mutex_lock(&average_time_service_mutex);
			
			int r = rand() % 99 +1;
			
			if(r<=90){
				
				total_revenue += Cseat*seats;
				
				//printf("oi dia8esimoi callers einai: %d \n",available_callers);
				printf("Η κράτηση ολοκληρώθηκε επιτυχώς. Ο αριθμός συναλλαγής είναι <%d> , ",id);
				
				printf(	"οι θέσεις σας είναι οι <");
				for(int i=0; i<seats; i++){
				printf(	"%d,",Nreserved[i]+1); 	
				}
				printf(	"> και το κόστος συναλλαγής είναι <%d> ευρώ",seats*Cseat);
				
			}
			else {
				counter-=seats;
				for (int y=0;y<seats;y++){
					Nseat[Nreserved[y]]=0;
				}
				printf("--> ERROR: Η κράτηση ματαιώθηκε γιατί η συναλλαγή με την πιστωτική κάρτα δεν έγινε αποδεκτή .");
				}
	}else{
		counter-=seats;	
		printf("--> ERROR: Η κράτηση ματαιώθηκε γιατί δεν υπάρχουν αρκετές διαθέσιμες θέσεις..");
	}
	Ntel +=1;
	time_t end2 = time(NULL);
	printf(	". Χρόνος εξ = %.2f \n",(float)(end2-start2));
	average_time_servicing += end2-start2;
	rc = pthread_cond_broadcast(&cond);
		if (rc != 0) {	
			printf("--> ERROR: return code from pthread_cond_broadcast() is %d\n", rc);
			pthread_exit(&rc);
		}
	rc = pthread_mutex_unlock(&average_time_service_mutex);
		if (rc != 0) {	
			printf("--> ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
			pthread_exit(&rc);
		}

}

bool checkForAvailableSeats(int planChooser,int seats){
	int counter=0;
	if (planChooser==1){
		bool isFound=false;
		for (int i=0;i<NzoneA;i++){
			for (int y=0;y<Nseat;y++){
				if (TheatrePlanZoneA[i][y]==0){
					if (y+seats-1<=Nseat){
						for (int p=y;p<y+seats-1;p++){
							if (TheatrePlanZoneA[i][p]!=0){
								break;
							}else if ((p==y+seats-1))
							{
								return true;
							}
						}
					}else{
						break;
					}
				}
				if (isFound) break;
			}
			if(isFound) break;
		}
		return false;
	}
}


int reserveSeats(int numberOfReservedSeats,int id){
	for (int i=0;i<sizeof(Nseat);i++){
		if (Nseat[i]==0){
			Nseat[i]=id;
			return i;
		}
	}
	return -1;
}


int main(int argc, char *argv[]) {
	int CUSTOMERS= 10;//atoi(argv[1]);
	int seed = 10;
	int rc;

	srand(seed);



	pthread_t thread_id[CUSTOMERS];
	int countArray[CUSTOMERS];
	int threadCount,threadCount2;
		
		for(threadCount = 0; threadCount < CUSTOMERS; threadCount++) {
			countArray[threadCount] = threadCount + 1;
			/*dimiourgia tou thread*/
			rc = pthread_create(&thread_id[threadCount], NULL, callers, &countArray[threadCount]);
			
			/*elegxos oti to thread dimiourgithike swsta.*/
				if (rc != 0) {
					printf("ERROR: return code from pthread_create() is %d\n", rc);
					exit(-1);
				}
			}
	for(threadCount2 = 0; threadCount2 < CUSTOMERS; threadCount2++) {
			//countArray[threadCount] = threadCount + 1;
			/*dimiourgia tou thread*/
				rc = pthread_join(thread_id[threadCount2], NULL);
			
			
			}
		

	//pthread_join(Mainthread,NULL);

	pthread_mutex_destroy(&caller_mutex);
	pthread_mutex_destroy(&average_time_service_mutex);
	pthread_cond_destroy(&cond);
		printf("\nΤο πλάνο των θέσεων είναι:\n");
		for (int i=0;i<counter;i++){
			printf("  ( Θέση %d -> Πελάτης %d ) ",i+1,Nseat[i]);
			if (i+1%5==0){
				printf("\n");
			}
		}
		printf("\nΤα Συνολικά Έσοδα είναι: %d ευρώ\n", total_revenue);
		printf("Ο μέσος χρόνος αναμονής είναι: %.2f sec \n",average_time_waiting/CUSTOMERS);
		printf("Ο μέσος χρόνος εξυπηρέτησης είναι: %.2f sec \n",average_time_servicing/CUSTOMERS);
		return 1;
}
