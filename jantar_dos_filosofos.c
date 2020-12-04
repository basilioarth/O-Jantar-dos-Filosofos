//-- Importações -------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <Windows.h>
//-- Constantes --------------------------------------------------------------//
#define N 		  5						   // Número total de filósofos
#define THINKING 'T'					   // O filósofo está pensando
#define HUNGRY 	 'H'					   // O filósofo está tentando pegar os garfos
#define EATING 	 'E'					   // O filósofo está comendo
#define LEFT 	 (num_philosopher+N-1)%N   // Número do vizinho a esquerda de i                       
#define RIGHT 	 (num_philosopher+1)%N     // Número do vizinho a direita de i
//-- Variáveis Globais -------------------------------------------------------//
sem_t philosophers_sem[N]; 				   // Um semáforo para cada filósofo
pthread_mutex_t mutex;					   // Mutex que garantirá a exclusão mútua no acesso à região crítica
pthread_t philosophers[N];				   // Um thread para representar cada filósofo
char state[N] = {'T', 'T', 'T', 'T', 'T'}; // Array para controlar o estado de cada filósofo
int num_philosopher[N]={0,1,2,3,4};		   // Array que servirá de argumento para a função de criação dos threads
//-- Prototipações -----------------------------------------------------------//
void *philosopher(void *num);
void take_forks(int);
void put_forks(int);
void test(int);
void print_philosophers(void);
//-- Funções -----------------------------------------------------------------//
void *philosopher(void *num)
{
   while(1)
   {
      int *i = num;
      Sleep(2000); 							// O filósofo está pensando
      take_forks(*i);						// Pega dois garfos ou bloqueia
      Sleep(2000);							// O filósofo está comendo
      put_forks(*i);						// Devolve os dois garfos pra mesa
   }
}

void take_forks(int num_philosopher)
{
   pthread_mutex_lock(&mutex);				     // Entra na região crítica
   state[num_philosopher] = HUNGRY;			     // Registra que o filósofo está faminto
   
   /**printf("Filosofo %d tem fome.\n", num_philosopher);*/
   //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
   print_philosophers();
   
   test(num_philosopher);					     // Tenta pegar dois garfos
   pthread_mutex_unlock(&mutex);			     // Sai da região crítica
   
   sem_wait(&philosophers_sem[num_philosopher]); // Bloqueia o semáforo do filósofo passado se os garfos não foram pegos
   Sleep(2000);
}

void put_forks(int num_philosopher)
{
   pthread_mutex_lock(&mutex);					// Entra na região crítica		
   state[num_philosopher]=THINKING;				// O filósofo acabou de comer
   
   /**printf("Filosofo %d deixou os garfos %d e %d.\n", num_philosopher, LEFT, num_philosopher);
   printf("Filosofo %d esta a pensar.\n", num_philosopher);*/
   //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
   print_philosophers();
   
   test(LEFT);									// Vê se o vizinho da esquerda pode comer agora
   test(RIGHT);									// Vê se o vizinho da direita pode comer agora
   pthread_mutex_unlock(&mutex);
}

void test(int num_philosopher)
{
   if(state[num_philosopher]==HUNGRY && state[LEFT] !=EATING && state[RIGHT]!=EATING)
   {
      state[num_philosopher]=EATING;
      Sleep(2000);
      
      /**printf("Filosofo %d agarrou os garfos %d e %d.\n", num_philosopher, LEFT, num_philosopher+1);
      printf("Filosofo %d esta a comer.\n", num_philosopher);*/
      //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
      print_philosophers();
      
      Sleep(2000);
      sem_post(&philosophers_sem[num_philosopher]); // Se tiver algum thread bloqueado sob esse semáforo ele é desbloqueado; caso contrário, é incrementado o valor do semáforo
   }
}

void print_philosophers(){
	printf("\t\t\t\t\t\t       ( %c )        ",          state[0]);
	printf("\t\t\t\t\t\t                                    \n\n");
	printf("\t\t\t\t\t\t( %c )        ( %c )", state[4], state[1]);
	printf("\t\t\t\t\t\t                                    \n\n");
	printf("\t\t\t\t\t\t   ( %c )  ( %c )", state[3], state[2]   );
	printf("\t\t\t\t\t\t                                \n\n\n\n");
}

int main() {
   int i;
   pthread_mutex_init(&mutex, NULL);				// Inicia o mutex que controla o acesso à região crítica
   
   for(i=0;i<N;i++){
      sem_init(&philosophers_sem[i],0,0);			// Inicia o semáforo de cada um dos filósofos
   }
   
   for(i=0;i<N;i++)
   {
      pthread_create(&philosophers[i], NULL, philosopher, &num_philosopher[i]);
      // Cria cada um dos threads que representam cada um dos filósofos e envia para a fuinção philosopher
      if(i == N-1){
		  //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
		  print_philosophers();
	  }
      /**printf("Filosofo %d esta a pensar.\n",i);*/
   }
   
   for(i=0;i<N;i++){
   	   pthread_join(philosophers[i],NULL); 			// Realiza a junção das threads
   }
   
   return(0);
}