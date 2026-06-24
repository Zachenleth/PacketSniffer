#include "libreria.h"

pcap_if_t *alldevs;

void list_devices(pcap_if_t *alldevs)
{
    int i = 0;
    for (pcap_if_t *d = alldevs; d; d = d->next)
    {
        printf("%d. %s - %s\n", ++i, d->name, d->description);
    }
}