#include "libreria.h"

pcap_t *open_device(pcap_if_t *device, char *errbuf)
{
    pcap_t *handle = pcap_open_live(device->name, 65536, 1, 100, errbuf);

    if (handle == NULL)
    {
        return nullptr;
    }

    return handle;
}