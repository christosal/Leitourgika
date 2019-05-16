#include "res.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>


pthread_mutex_t caller_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t average_time_waiting_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t average_time_service_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t plan_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t screen_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;



typedef struct product_arguments {
	int firstArgument;
	int secondArgument;
} PRODUCT_ARGUMENTS;






void * callers(void *args){

	PRODUCT_ARGUMENTS * products;
	products = (PRODUCT_ARGUMENTS *)args;

	int seats= rand() % Nseathigh + Nseatlow;
	int transaction = products->secondArgument;
	int rc;

	rc = pthread_mutex_lock(&caller_mutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
			pthread_exit(&rc);
		}		
	available_callers-=1;
		//an oi dia8esimoi tilefonites einai 0 tote mpes se wait
		result = clock_gettime(CLOCK_REALTIME, &start);
			
		
		while (available_callers<= 0) {	
		
			rc = pthread_cond_wait(&cond, &caller_mutex);
			if (rc != 0) {	
				printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
				pthread_exit(&rc);
			}
			
		}

		
	clock_gettime(CLOCK_REALTIME, &end);
	num_seconds_waiting += end.tv_sec-start.tv_sec;

	counter +=seats;

	if(seats<=num_available_seats){
			
			result = clock_gettime(CLOCK_REALTIME, &start);
			unsigned int num_seconds = rand() % 5 + 5;
			sleep(num_seconds);
			

			num_available_seats -= seats;
			int r = rand() % 99 +1;
			
			if(r<=90){
				
				total_revenue += Cseat*seats;
				
				printf("oi dia8esimoi callers einai: %d \n",available_callers);
				printf("H sunallagi olokliro8ike epitixos. O arithmos sunallagis einai %d \n",transaction);
				
				printf(	"oi theseis sas einai<");
				for(int i=0; i<seats-1; i++){
				printf(	"%d,",counter -seats +i); 	
				}
				printf(	"%d> kai to kostos sunallagis einai <%d>\n",counter-1,seats*Cseat);
				
			}

			else {
				counter-=seats;
				num_available_seats+=seats;
				printf("ERROR: Not enough cash in credit card.\n");
				}
	}

	else{	
	printf("ERROR: not enough available seats.\n");
	}

	clock_gettime(CLOCK_REALTIME, &end);
	num_seconds_servicing += end.tv_sec-start.tv_sec;

	available_callers +=1;
	rc = pthread_mutex_unlock(&caller_mutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
			pthread_exit(&rc);
		}
	pthread_mutex_lock(&caller_mutex);
		
		
		
		//eidopoiei ta alla threads oti exei ksekinisei.
	if(available_callers==1){	rc = pthread_cond_broadcast(&cond);}
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_broadcast() is %d\n", rc);
			pthread_exit(&rc);
		}
		pthread_mutex_unlock(&caller_mutex);

	pthread_exit(NULL);

}







void * customers(void* args){
 
}






int main(int argc, char *argv[]) {
	unsigned int tn= atoi(argv[1]);
		//pthread_t Mainthread;
	int rc;

	srand(tn);

	//pthread_create( &Mainthread, NULL, customers, NULL);

	PRODUCT_ARGUMENTS prod;
	pthread_t thread_id[100];
	int countArray[100];
	int threadCount;
		
		for(threadCount = 0; threadCount <100; threadCount++) {
			countArray[threadCount] = threadCount + 1;
			/*dimiourgia tou thread*/
				rc = pthread_create(&thread_id[threadCount], NULL, callers, &countArray[threadCount]);
			
			/*elegxos oti to thread dimiourgithike swsta.*/
				if (rc != 0) {
					printf("ERROR: return code from pthread_create() is %d\n", rc);
					exit(-1);
				}
			}
	for(threadCount = 0; threadCount < 100; threadCount++) {
			countArray[threadCount] = threadCount + 1;
			/*dimiourgia tou thread*/
				rc = pthread_join(thread_id[threadCount], NULL);
			
			
			}
		

	//pthread_join(Mainthread,NULL);

	pthread_mutex_destroy(&caller_mutex);
	pthread_cond_destroy(&cond);
		printf("Main: Thread finished.\n");
		printf("total revenue is %d\n", total_revenue);
		printf("o mesos xronos se deuterolepta pou perimenan sthn anamoni einai: %d \n",num_seconds_waiting/100);
		printf("o mesos xronos se deuterolepta pou perimenan gia to service einai: %d \n",num_seconds_servicing/100);
		return 1;
}
