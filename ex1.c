#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *thread_1(void *inutilise){
	int i;

	
	for(i=1;i<=200;i++){
		printf("1");
	}
	
	pthread_exit(NULL);
}
	
int main(void){

pthread_t thread1;
printf("Avant la création du thread \n");

//Renvoie 0 si le thread est créé
if(pthread_create(&thread1, NULL,thread_1, NULL) == -1){
	perror("Erreur lors de la creation du thread 1");
	return EXIT_FAILURE;
	}

if(pthread_join(thread1,NULL)){
	perror("pthread_join");
	return EXIT_FAILURE;
}
printf("Après la création du thread.\n");

return EXIT_SUCCESS;
}
