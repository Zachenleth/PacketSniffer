#include "libreria.h"
#include "estructuras.h"

struct packet_info packets[MAX_PACKETS];
int packet_count = 0;

// Convierte los bytes del paquete a texto hexadecimal
void save_raw_hex(const u_char *packet, int size, char *raw, int raw_size)
{
    raw[0] = '\0';

    int limite = size;

    if (limite > 256)
    {
        limite = 256; // Solo guardamos los primeros 256 bytes para no llenar demasiado
    }

    int pos = 0;

    for (int i = 0; i < limite && pos < raw_size - 4; i++)
    {
        pos += snprintf(raw + pos, raw_size - pos, "%02X ", packet[i]);

        if ((i + 1) % 16 == 0 && pos < raw_size - 2)
        {
            pos += snprintf(raw + pos, raw_size - pos, "\n");
        }
    }
}

void print_packet_summary(struct packet_info *p)
{
    printf("%d | %s | %s | %s | %d\n",
           p->id,
           p->src_ip,
           p->dst_ip,
           p->protocol,
           p->size);
}

void save_packet(const u_char *packet,
                 struct pcap_pkthdr header,
                 unsigned char *src,
                 unsigned char *dst,
                 unsigned char protocol,
                 int ip_header_length)
{
    if (packet_count >= MAX_PACKETS)
        return;

    struct packet_info *p = &packets[packet_count];

    p->id = packet_count + 1;
    p->size = header.len;

    p->src_port = 0;
    p->dst_port = 0;

    sprintf(p->src_ip, "%d.%d.%d.%d", src[0], src[1], src[2], src[3]);
    sprintf(p->dst_ip, "%d.%d.%d.%d", dst[0], dst[1], dst[2], dst[3]);

    if (protocol == 6)
    {
        strcpy(p->protocol, "TCP");
        p->protocol_id = 6;

        struct tcp_header *tcp = (struct tcp_header *)(packet + 14 + ip_header_length);

        p->src_port = ntohs(tcp->source_port);
        p->dst_port = ntohs(tcp->dest_port);
    }
    else if (protocol == 17)
    {
        strcpy(p->protocol, "UDP");
        p->protocol_id = 17;

        struct udp_header *udp = (struct udp_header *)(packet + 14 + ip_header_length);

        p->src_port = ntohs(udp->source_port);
        p->dst_port = ntohs(udp->dest_port);
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

    save_raw_hex(packet, header.len, p->raw, MAX_RAW_TEXT);

    print_packet_summary(p);

    packet_count++;
}

void process_packet(const u_char *packet, struct pcap_pkthdr header)
{
    if (packet_count >= MAX_PACKETS)
        return;

    // IPv4
    if (packet[12] == 0x08 && packet[13] == 0x00)
    {
        struct ip_header *iph = (struct ip_header *)(packet + 14);
        int ip_header_length = (iph->ver_ihl & 0x0F) * 4;

        unsigned char *src = (unsigned char *)&iph->saddr;
        unsigned char *dst = (unsigned char *)&iph->daddr;

        unsigned char protocol = iph->proto;

        save_packet(packet, header, src, dst, protocol, ip_header_length);
        return;
    }

    // ARP / IPv6 / OTRO
    struct packet_info *p = &packets[packet_count];

    p->id = packet_count + 1;
    p->size = header.len;

    strcpy(p->src_ip, "N/A");
    strcpy(p->dst_ip, "N/A");

    p->src_port = 0;
    p->dst_port = 0;

    if (packet[12] == 0x08 && packet[13] == 0x06)
    {
        strcpy(p->protocol, "ARP");
        p->protocol_id = 2054;
    }
    else if (packet[12] == 0x86 && packet[13] == 0xDD)
    {
        strcpy(p->protocol, "IPv6");
        p->protocol_id = 34525;
    }
    else
    {
        strcpy(p->protocol, "OTRO");
        p->protocol_id = 0;
    }

    save_raw_hex(packet, header.len, p->raw, MAX_RAW_TEXT);

    packet_count++;
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