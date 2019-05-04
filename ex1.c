#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sched.h>

#define NB_THREADS 4
#define POLICY SCHED_FIFO


void *execute_thread(void *arg){

	int numero_thread = (int) arg;

	int i;
	int j;

	//On attend inversement au numero du threads	
	
	sleep(numero_thread * 2);
	
	printf("Le ihread numero %d demarre a  %ld / \n ",numero_thread,time(0));
	
	//Boucle d'execution fictive
	for(i=1;i<=200000;i++){
	
	}
	

	printf("Le thread numero %d fini a / %ld",numero_thread,time(0)); 
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

printf("Avant la création des thread \n");


// Definition de la politique d ordonnancement
if( error_id = pthread_attr_setschedpolicy(&attr,SCHED_FIFO) != 0 ){
	fprintf(stderr,"Erreur lors du parametrage de la politique d ordonancement %s \n", strerror(error_id));
exit(EXIT_FAILURE);

}

// Heritage de creation
if( error_id = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0 ){
	fprintf(stderr,"Erreur lors du parametrage de la regle d heritage %s \n", strerror(error_id));
exit(EXIT_FAILURE);

}

// Boucle de creation des threads

for(i=0; i < NB_THREADS; i++){

//On attribue la priorité à chaque Threads 

	
	param.sched_priority = (i+1)*10;

	// Enregistrement des paramètres du thread
	if( error_id = pthread_attr_setschedparam(&attr, &param) != 0 ){
		fprintf(stderr,"Erreur lors de l'attribution des paramètres du thread %s \n", strerror(error_id));
		exit(EXIT_FAILURE);

	}


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
