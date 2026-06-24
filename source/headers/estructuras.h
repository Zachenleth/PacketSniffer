#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_PACKETS 500
#define MAX_RAW_TEXT 2048

struct ip_header
{
    unsigned char ver_ihl; // versión + longitud
    unsigned char tos;
    unsigned short tlen;
    unsigned short identification;
    unsigned short flags_fo;
    unsigned char ttl;
    unsigned char proto;
    unsigned short crc;
    unsigned int saddr; // IP origen
    unsigned int daddr; // IP destino
};

struct tcp_header
{
    unsigned short source_port;
    unsigned short dest_port;
    unsigned int seq_num;
    unsigned int ack_num;
    unsigned char data_offset;
    unsigned char flags;
    unsigned short window;
    unsigned short checksum;
    unsigned short urgent_ptr;
};

struct udp_header
{
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short checksum;
};

struct packet_info
{
    int id;
    char src_ip[16];
    char dst_ip[16];
    char protocol[10];
    int protocol_id;
    int src_port;
    int dst_port;
    int size;

    char raw[MAX_RAW_TEXT];
};

extern struct packet_info packets[MAX_PACKETS];
extern int packet_count;

#endif