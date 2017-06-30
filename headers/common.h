#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h> 		/* bool */

enum protocol{
	TCP, 
	UDP, 
	HTTP, 
	ICMP,
	OTHER
};

struct connection{
	struct sockaddr_in source;
	struct sockaddr_in destination;
	int timestamp;
	uint16_t source_port;
	uint16_t destination_port;
	enum protocol protocol;
};

bool connection_compare(struct connection* first, struct connection* second)
{
	// Check any combination to see if the ip addresses are match.
	if (!(((first->source.sin_addr.s_addr == second->source.sin_addr.s_addr) && 
	       (first->destination.sin_addr.s_addr == second->destination.sin_addr.s_addr)) ||
	      ((first->destination.sin_addr.s_addr == second->source.sin_addr.s_addr) && 
	       (first->source.sin_addr.s_addr == second->destination.sin_addr.s_addr))))
	{
		return false;
	}

	/* Ignoring the ports.
	if(!(((first->source_port == second->source_port) && 
	      (first->destination_port == second->destination_port)) || 
	     ((first->source_port == second->destination_port) && 
	      (first->destination_port == second->source_port))))
	{
		return false;
	}
	*/

	return true;
}

void connection_update(struct connection* first, struct connection* second)
{
	first->timestamp = second->timestamp;
}

#endif

