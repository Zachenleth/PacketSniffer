#include "../headers/libreria.h"
#include "../headers/estructuras.h"
#include "../headers/funciones.h"

void export_all_csv(const char *);

int main()
{
    system("cls");
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    // nombre archivo
    char filename[100];
    printf("Nombre del archivo CSV (incluye .csv al final): ");
    scanf("%s", filename);

    // listar interfaces
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        printf("Error: %s\n", errbuf);
        return 1;
    }

    list_devices(alldevs);

    // seleccionar interfaz
    int choice = select_device();
    pcap_if_t *device = get_device_by_index(alldevs, choice);

    // abrir
    pcap_t *handle = open_device(device, errbuf);

    printf("\nCapturando paquetes...\n");

    // capturar (limitado por MAX_PACKETS)
    start_capture(handle);

    printf("\nCaptura finalizada. Total paquetes: %d\n", packet_count);

    // exportar TODO
    export_all_csv(filename);

    pcap_freealldevs(alldevs);
    pcap_close(handle);

    return 0;
}

void export_all_csv(const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error creando archivo\n");
        return;
    }

    fprintf(file, "ID,IP_SRC,IP_DST,PROTO,SPORT,DPORT,SIZE\n");

    for (int i = 0; i < packet_count; i++)
    {
        struct packet_info *p = &packets[i];

        fprintf(file, "%d,%s,%s,%s,%d,%d,%d\n",
                p->id,
                p->src_ip,
                p->dst_ip,
                p->protocol,
                p->src_port,
                p->dst_port,
                p->size);
    }

    fclose(file);

    printf("\nArchivo %s generado correctamente\n", filename);
}