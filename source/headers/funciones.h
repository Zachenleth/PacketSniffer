#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "libreria.h"

void list_devices(pcap_if_t *);
int select_device();
pcap_if_t *get_device_by_index(pcap_if_t *, int);
pcap_t *open_device(pcap_if_t *, char *);
void start_capture(pcap_t *);
void print_packet_summary(struct packet_info *);
void save_packet(const u_char *, struct pcap_pkthdr, unsigned char *, unsigned char *, unsigned char, int);
void process_packet(const u_char *, struct pcap_pkthdr);

#endif