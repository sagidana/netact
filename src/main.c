#include <stdio.h>		/* std... */
#include <stdlib.h> 		/* malloc() */
#include <unistd.h> 		/* close() */
#include <stdbool.h> 		/* bool */
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <pthread.h>

#include "../headers/common.h"  	/* enum protocol, struct connection */
#include "../headers/extractor.h"	/* extract() */
#include "../headers/list.h"		/* list */

void print_connection(struct connection* conn);
void* sniff(void* ptr);
void* clean(void* ptr);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const int BUFFER_SIZE = 65535;
const int CLEANER_SEC = 60 * 5;

void print_connections();

int main()
{
	pthread_t sniffer_thread, cleaner_thread;
	int ret = 0;

	ret = pthread_create(&sniffer_thread, NULL, sniff, NULL);
	if (ret)
		printf("pthread_create - failed!\n");

	ret = pthread_create(&cleaner_thread, NULL, clean, NULL);
	if (ret)
		printf("pthread_create - failed!\n");

	while(1)
	{
		print_connections();
		sleep(2);
	}

	return 0;
}

void print_connections()
{
	system ("tput clear");
	
	pthread_mutex_lock(&mutex);

	struct node* curr = list_get_head();

	while(curr != NULL)
	{	
		struct connection* conn = (struct connection * )curr->value;
		print_connection(conn);
		
		curr = curr->next;
	}

	pthread_mutex_unlock(&mutex);
}

void* clean(void* ptr)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);

		struct node* curr = list_get_head();

		while(curr != NULL)
		{	
			struct connection* conn = (struct connection * )curr->value;
		
			if (conn->timestamp + CLEANER_SEC < time(NULL))
			{
				list_remove((unsigned char * )conn, connection_compare);
				free(conn);
			}
		
			curr = curr->next;
		}

		pthread_mutex_unlock(&mutex);

		sleep(10);
	}

	return NULL;
}

void* sniff(void* ptr)
{
	unsigned char *buffer = (unsigned char *) malloc(BUFFER_SIZE);
	struct connection* conn = (struct connection*) malloc(sizeof(struct connection));

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

	if (s < 0)
	{	
		printf("Socket error!\n");
		return NULL;
	}	
	
	while(1)
	{
		unsigned int data_size = recv(s, buffer, BUFFER_SIZE, 0);
		
		if (data_size < 0)
		{
			printf("recv() error!\n");
			break;
		}
		
		extract(conn, buffer, data_size);

		if (!list_search(( unsigned char * )conn, connection_compare))
		{
			list_add(( unsigned char * )conn);
			
			// After adding the current connection -> allocate new connection.
			conn = (struct connection*) malloc(sizeof(struct connection));
		}
		else
		{	
			// Updating the timestamp on the connection record.
			list_update(( unsigned char * )conn, connection_compare, connection_update);
		}
	}

	close(s);

	printf("Finished!\n");
	return NULL;
}


void print_connection(struct connection* conn)
{
	char* protocol = "";
	switch (conn->protocol)
	{
		case(TCP):
			protocol = "TCP";
			break;
		case(UDP):
			protocol = "UDP";
			break;
		case(HTTP):
			protocol = "HTTP";
			break;
		case(ICMP):
			protocol = "ICMP";
			break;
		case(OTHER):
			protocol = "UNKOWN";
			break;
	}

	time_t t = (time_t)conn->timestamp;
	struct tm tm = *localtime(&t);

	printf("%s: ", protocol);
	printf("\t%-22s:%u", inet_ntoa(conn->source.sin_addr), conn->source_port);
	printf("\t%-22s:%u \t%d:%d:%d\n", inet_ntoa(conn->destination.sin_addr), 
							conn->destination_port, 
							tm.tm_hour, 
							tm.tm_min, 
							tm.tm_sec);
}























