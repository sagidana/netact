#include "../headers/extractor.h"

void extract(struct connection* conn, unsigned char* packet, int size)
{
	conn->timestamp = (int)time(NULL);
	extract_ip(conn, packet, size);
	extract_tcp(conn, packet, size);
	extract_udp(conn, packet, size);
}

void extract_udp(struct connection* conn, unsigned char* packet, int size)
{
	unsigned short ip_header_length;
	struct iphdr *ip_header;
	struct udphdr *udp_header;

	ip_header = (struct iphdr *) packet;
	ip_header_length = ip_header->ihl * 4;

	if (ip_header->protocol != 16)
		return;

	udp_header = (struct udphdr * )(packet + ip_header_length);

	conn->source_port = ntohs(udp_header->source);
	conn->destination_port = ntohs(udp_header->dest);
	conn->protocol = UDP;
}

void extract_tcp(struct connection* conn, unsigned char* packet, int size)
{
	unsigned short ip_header_length;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;

	ip_header = (struct iphdr *) packet;
	ip_header_length = ip_header->ihl * 4;

	if (ip_header->protocol != 6)
		return;

	tcp_header = (struct tcphdr * )(packet + ip_header_length);

	conn->source_port = ntohs(tcp_header->source);
	conn->destination_port = ntohs(tcp_header->dest);
	conn->protocol = TCP;
}

void extract_ip(struct connection* conn, unsigned char* packet, int size)
{
	struct iphdr *ip_header = (struct iphdr *) packet;

	memset(&conn->source, 0, sizeof(conn->source));
	memset(&conn->destination, 0, sizeof(conn->destination));

	// Initialize source and destination ip addresses.
	conn->source.sin_addr.s_addr = ip_header->saddr;
	conn->destination.sin_addr.s_addr = ip_header->daddr;
}











