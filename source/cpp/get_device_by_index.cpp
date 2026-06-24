#include "libreria.h"

pcap_if_t *get_device_by_index(pcap_if_t *alldevs, int choice)
{
    int i = 1;
    pcap_if_t *d;

    for (d = alldevs; d && i < choice; d = d->next, i++)
        ;

    return d;
}