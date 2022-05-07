/*
    Rafael Anderson Dalmolin
    Engenharia de Computação
    RA 1436287
    SISTEMAS OPERACIONAIS
    
    Necessario alterar o msg_max local
    sudo -i
    echo number > /proc/sys/fs/mqueue/msg_max
    
    // gcc T_12.c -o T_12 -lrt -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdbool.h>

#define NUM_COZINHEIROS 1
#define NUM_GAULESES 6
#define QUANT_JAVALIS 14
#define mainSleepTime 15

typedef struct messbuf
{
	int javali;
	int counter;
} messbuf_t;

mqd_t fd;				// descritor da fila de mensagens
struct mq_attr attr;	// atributos da fila de mensagens
messbuf_t data;			// as mensagens são do tipo messbuf_t
messbuf_t *ptr = &data; // ponteiro para facilitar a vida

char nome[NUM_GAULESES] = "RAFAEL";
pthread_mutex_t mutex_c;
pthread_mutex_t mutex_g;
pthread_mutex_t mutex;

void initializeData()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_c, NULL);
	pthread_mutex_init(&mutex_g, NULL);
	pthread_mutex_lock(&mutex_c);
	pthread_mutex_lock(&mutex);
	ptr->counter = 0;
}

int random_number()
{
	return ((rand() % 100));
}
void RetiraJavali(int *gaules)
{

	pthread_mutex_lock(&mutex_g);
	if (ptr->counter == 0)
	{

		printf("\t\t\t\tGaules %c(%d): Acordou o cozinheiro\n", nome[*gaules], *gaules);
		printf("\t\t\t\tGaules %c(%d): Avisou cozinheiro sobre mesa vazia\n", nome[*gaules], *gaules);
		ptr->counter = 0;
		mq_send(fd, (void *)ptr, sizeof(messbuf_t), 0);
		pthread_mutex_unlock(&mutex_c);
		pthread_mutex_lock(&mutex);
	}

	mq_receive(fd, (void *)ptr, sizeof(messbuf_t), 0);
	printf("\t\t\t\tGaules %c(%d): Comendo javali[%d]\n", nome[*gaules], *gaules, (int)ptr->javali);
	if (ptr->counter == QUANT_JAVALIS)
	{
		ptr->counter = 0;
	}
	pthread_mutex_unlock(&mutex_g);
	sleep(1);
}

void *Gaules(int *gaules)
{
	while (true)
	{
		RetiraJavali(gaules);
	}
}

void ColocaJavalis(int *cozin)
{

	pthread_mutex_lock(&mutex_c);
	mq_receive(fd, (void *)ptr, sizeof(messbuf_t), 0);
	while (ptr->counter < QUANT_JAVALIS)
	{

		ptr->javali = random_number();
		printf("Cozinheiro [%d] fez o javali [%d] \n", *cozin, (int)ptr->javali);
		ptr->counter++;
		mq_send(fd, (void *)ptr, sizeof(messbuf_t), 0); // envia a mensagem
		printf("Colocando  o javali  na mesa\n");
	}
	pthread_mutex_unlock(&mutex);
}
void *Cozinheiro(int *cozin)
{
	while (true)
	{
		ColocaJavalis(cozin);
	}
}

int main(void)
{

	attr.mq_maxmsg = QUANT_JAVALIS;		 // capacidade para 10 mensagens
	attr.mq_msgsize = sizeof(messbuf_t); // tamanho de cada mensagem
	attr.mq_flags = 0;

	mq_unlink("/myqueue");
	fd = mq_open("/myqueue", O_RDWR | O_CREAT, 0666, &attr); // abre ou cria a fila com permissoes 0666
	initializeData();

	pthread_t cozinheiro[NUM_COZINHEIROS];
	pthread_t gauleses[NUM_GAULESES];
	int cozin[NUM_COZINHEIROS];
	int gaules[NUM_GAULESES];

	long status, i;

	for (i = 0; i < NUM_COZINHEIROS; i++)
	{
		printf("cria trhead cozinheiro [%ld]\n", i);
		cozin[i] = i;
		status = pthread_create(&cozinheiro[i], NULL, (void *)Cozinheiro, (int *)&cozin[i]);
		if (status) // ocorreu um erro
		{
			perror("pthread_create Cozinheiro");
			exit(-1);
		}
	}

	for (i = 0; i < NUM_GAULESES; i++)
	{
		gaules[i] = i;
		printf("cria trhead Gaules [%ld]\n", i);
		status = pthread_create(&gauleses[i], NULL, (void *)Gaules, (int *)&gaules[i]);
		if (status) // ocorreu um erro
		{
			perror("pthread_create Gaules");
			exit(-1);
		}
	}
	sleep(mainSleepTime);
	printf("Exit the program\n");
	pthread_exit(NULL);
	exit(0);
}
