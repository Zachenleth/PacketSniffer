#include "export_csv.h"
#include "libreria.h"
#include "estructuras.h"

// Exporta todos los paquetes capturados a un archivo CSV
void export_all_csv(const char *filename)
{
    FILE *file = fopen(filename, "w");

    // Si no se pudo crear el archivo, termina la función
    if (file == NULL)
    {
        return;
    }

    // Encabezados del archivo CSV
    fprintf(file, "ID,IP_SRC,IP_DST,PROTO,SPORT,DPORT,SIZE\n");

    // Escribe cada paquete guardado en el arreglo
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

    // Cierra el archivo
    fclose(file);
}