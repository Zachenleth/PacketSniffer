#include "../headers/libreria.h"
#include "../headers/estructuras.h"

struct packet_info packets[MAX_PACKETS];
int packet_count = 0;

void print_packet_summary(struct packet_info *p)
{
    printf("%d | %s | %s | %s | %d\n",
           p->id,
           p->src_ip,
           p->dst_ip,
           p->protocol,
           p->size);
}

void save_packet(const u_char *packet, struct pcap_pkthdr header, unsigned char *src, unsigned char *dst, unsigned char protocol, int ip_header_length)
{

    if (packet_count >= MAX_PACKETS)
        return;

    struct packet_info *p = &packets[packet_count];

    p->id = packet_count + 1;
    p->size = header.len;

    sprintf(p->src_ip, "%d.%d.%d.%d", src[0], src[1], src[2], src[3]);
    sprintf(p->dst_ip, "%d.%d.%d.%d", dst[0], dst[1], dst[2], dst[3]);

    if (protocol == 6)
    {
        strcpy(p->protocol, "TCP");
        p->protocol_id = 6;
    }
    else if (protocol == 17)
    {
        strcpy(p->protocol, "UDP");
        p->protocol_id = 17;
    }
    else if (protocol == 1)
    {
        strcpy(p->protocol, "ICMP");
        p->protocol_id = 1;
    }
    else
    {
        strcpy(p->protocol, "OTRO");
        p->protocol_id = protocol;
    }

    print_packet_summary(p);

    packet_count++;
}

void process_packet(const u_char *packet, struct pcap_pkthdr header)
{
    if (!(packet[12] == 0x08 && packet[13] == 0x00))
        return;

    // MessageBox(NULL, "Paquete capturado", "DEBUG", MB_OK); // Para windows.h, deshabilitado
    struct ip_header *iph = (struct ip_header *)(packet + 14);
    int ip_header_length = (iph->ver_ihl & 0x0F) * 4;

    unsigned char *src = (unsigned char *)&iph->saddr;
    unsigned char *dst = (unsigned char *)&iph->daddr;

    unsigned char protocol = iph->proto;

    save_packet(packet, header, src, dst, protocol, ip_header_length);
}

void start_capture(pcap_t *handle)
{
    struct pcap_pkthdr header;
    const u_char *packet;

    while (packet_count < MAX_PACKETS)
    {
        packet = pcap_next(handle, &header);

        if (packet == NULL)
            continue;

        process_packet(packet, header);
    }
}
