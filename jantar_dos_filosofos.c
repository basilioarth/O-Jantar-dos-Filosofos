//-- Importa��es -------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <Windows.h>
//-- Constantes --------------------------------------------------------------//
#define N 		  5						   // N�mero total de fil�sofos
#define THINKING 'T'					   // O fil�sofo est� pensando
#define HUNGRY 	 'H'					   // O fil�sofo est� tentando pegar os garfos
#define EATING 	 'E'					   // O fil�sofo est� comendo
#define LEFT 	 (num_philosopher+N-1)%N   // N�mero do vizinho a esquerda de i                       
#define RIGHT 	 (num_philosopher+1)%N     // N�mero do vizinho a direita de i
//-- Vari�veis Globais -------------------------------------------------------//
sem_t philosophers_sem[N]; 				   // Um sem�foro para cada fil�sofo
pthread_mutex_t mutex;					   // Mutex que garantir� a exclus�o m�tua no acesso � regi�o cr�tica
pthread_t philosophers[N];				   // Um thread para representar cada fil�sofo
char state[N] = {'T', 'T', 'T', 'T', 'T'}; // Array para controlar o estado de cada fil�sofo
int num_philosopher[N]={0,1,2,3,4};		   // Array que servir� de argumento para a fun��o de cria��o dos threads
//-- Prototipa��es -----------------------------------------------------------//
void *philosopher(void *num);
void take_forks(int);
void put_forks(int);
void test(int);
void print_philosophers(void);
//-- Fun��es -----------------------------------------------------------------//
void *philosopher(void *num)
{
   while(1)
   {
      int *i = num;
      Sleep(2000); 							// O fil�sofo est� pensando
      take_forks(*i);						// Pega dois garfos ou bloqueia
      Sleep(2000);							// O fil�sofo est� comendo
      put_forks(*i);						// Devolve os dois garfos pra mesa
   }
}

void take_forks(int num_philosopher)
{
   pthread_mutex_lock(&mutex);				     // Entra na regi�o cr�tica
   state[num_philosopher] = HUNGRY;			     // Registra que o fil�sofo est� faminto
   
   /**printf("Filosofo %d tem fome.\n", num_philosopher);*/
   //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
   print_philosophers();
   
   test(num_philosopher);					     // Tenta pegar dois garfos
   pthread_mutex_unlock(&mutex);			     // Sai da regi�o cr�tica
   
   sem_wait(&philosophers_sem[num_philosopher]); // Bloqueia o sem�foro do fil�sofo passado se os garfos n�o foram pegos
   Sleep(2000);
}

void put_forks(int num_philosopher)
{
   pthread_mutex_lock(&mutex);					// Entra na regi�o cr�tica		
   state[num_philosopher]=THINKING;				// O fil�sofo acabou de comer
   
   /**printf("Filosofo %d deixou os garfos %d e %d.\n", num_philosopher, LEFT, num_philosopher);
   printf("Filosofo %d esta a pensar.\n", num_philosopher);*/
   //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
   print_philosophers();
   
   test(LEFT);									// V� se o vizinho da esquerda pode comer agora
   test(RIGHT);									// V� se o vizinho da direita pode comer agora
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
      sem_post(&philosophers_sem[num_philosopher]); // Se tiver algum thread bloqueado sob esse sem�foro ele � desbloqueado; caso contr�rio, � incrementado o valor do sem�foro
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
   pthread_mutex_init(&mutex, NULL);				// Inicia o mutex que controla o acesso � regi�o cr�tica
   
   for(i=0;i<N;i++){
      sem_init(&philosophers_sem[i],0,0);			// Inicia o sem�foro de cada um dos fil�sofos
   }
   
   for(i=0;i<N;i++)
   {
      pthread_create(&philosophers[i], NULL, philosopher, &num_philosopher[i]);
      // Cria cada um dos threads que representam cada um dos fil�sofos e envia para a fuin��o philosopher
      if(i == N-1){
		  //printf("[%c, %c, %c, %c, %c]\n", state[0], state[1], state[2], state[3], state[4]);
		  print_philosophers();
	  }
      /**printf("Filosofo %d esta a pensar.\n",i);*/
   }
   
   for(i=0;i<N;i++){
   	   pthread_join(philosophers[i],NULL); 			// Realiza a jun��o das threads
   }
   
   return(0);
}