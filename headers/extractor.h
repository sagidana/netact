#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <netinet/ip.h>    	/* ip header  */
#include<netinet/udp.h>   	/* udp header */
#include <netinet/tcp.h>   	/* tcp header */
#include <string.h> 		/* memset() */
#include <time.h>		/*  */

#include "../headers/common.h"  /* enum protocol, struct connection */

void extract(struct connection* conn, unsigned char* packet, int size);
void extract_tcp(struct connection* conn, unsigned char* packet, int size);
void extract_udp(struct connection* conn, unsigned char* packet, int size);
void extract_ip(struct connection* conn, unsigned char* packet, int size);

#endif
