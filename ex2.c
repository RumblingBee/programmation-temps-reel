#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sched.h>
#include <sys/time.h>


#define NB_THREADS 4
#define POLICY SCHED_RR


void *execute_thread(void *arg){

	int numero_thread = (int) arg;

	int i;
	int j;
	int timeQuantum = 10;

	//On attend inversement au numero du threads	


	sleep(2);

	struct timeval startingTime, lastTime, currentTime;


	gettimeofday(&startingTime,NULL);

	currentTime = startingTime;

	long long int timeDiff; 

	while(1){
		
	
		do{

			lastTime = currentTime;

			//On actualise la date actuelle
			gettimeofday(&currentTime,NULL);

			if((currentTime.tv_sec - startingTime.tv_sec) > timeQuantum){
				pthread_exit(NULL);
			}
			timeDiff = currentTime.tv_sec - lastTime.tv_sec;
			timeDiff = timeDiff * 1000000;
			}while(timeDiff < 1000);

				fprintf(stdout, "%ld / %d prempte \n", currentTime.tv_sec, numero_thread);
				fprintf(stdout, "%ld / %d active \n", currentTime.tv_sec, numero_thread);
		
	}
	
	printf("\n Le thread numero %d demarre a  %ld  ",numero_thread,time(0));
	
	//Boucle d'execution fictive
	
	
	
	for(i=1;i<=100000;i++){
		for(j=1;j<=10000;j++){
	
		}	
	}
	

	printf("\n Le thread numero %d fini a %ld",numero_thread,time(0)); 
	pthread_exit(NULL);
}
		
	
	
int main(void){

int i;

int error_id;

pthread_t threads[NB_THREADS];

//Attributs des threads
pthread_attr_t attr;

//Masque de CPU qui définit quels CPUs utilisés (0 a 7)
cpu_set_t mask;

// Clear le masque de CPU
CPU_ZERO(&mask);


// Ajoute le CPU 0 au masque de CPU
CPU_SET(0,&mask);

struct sched_param param;

int init = pthread_attr_init(&attr);

printf("Avant la création des threads \n");


// Definition de la politique d ordonnancement
if( error_id = pthread_attr_setschedpolicy(&attr,POLICY) != 0 ){
	fprintf(stderr,"Erreur lors du parametrage de la politique d ordonancement %s \n", strerror(error_id));
exit(EXIT_FAILURE);

}

// Heritage de creation
if( error_id = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0 ){
	fprintf(stderr,"Erreur lors du parametrage de la regle d heritage %s \n", strerror(error_id));
exit(EXIT_FAILURE);

}
// Afiinité du thread
if( error_id = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &mask ) != 0 ){
	fprintf(stderr,"Erreur lors de l'attribution de l'affinité %s \n", strerror(error_id));
exit(EXIT_FAILURE);

}

// On attribue la même priorité à chaque Thread
param.sched_priority = 50;

// Enregistrement des paramètres des threads
	if( error_id = pthread_attr_setschedparam(&attr, &param) != 0 ){
		fprintf(stderr,"Erreur lors de l'attribution des paramètres du thread %s \n", strerror(error_id));
		exit(EXIT_FAILURE);

	}
// Boucle de creation des threads

for(i=0; i < NB_THREADS; i++){

	// Creation des threads
	
	if( error_id = pthread_create(&(threads[i]),&attr,execute_thread, (void *)(i+1) ) != 0 ){
		fprintf(stderr,"Erreur lors de la creation de thread %s \n", strerror(error_id));
		exit(EXIT_FAILURE);

	}
}


//On attend que les threads se terminent

for(i = 0; i < NB_THREADS; i++){
	pthread_join(threads[i], NULL);
}	

return EXIT_SUCCESS;
}
