#include "../headers/libreria.h"

pcap_t *open_device(pcap_if_t *device, char *errbuf)
{
    pcap_t *handle = pcap_open_live(device->name, 65536, 1, 1000, errbuf);

    if (handle == NULL)
    {
        printf("No se puede abrir el dispositivo\n");
        exit(1);
    }

    return handle;
}