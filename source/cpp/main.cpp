#include <iostream>
#include <pcap.h>
#include <vector>
#include <cstring>
#include <cctype>
#include <sstream>
#include <chrono>
#include <thread>

#define SNAP_LEN 65536

// Cabecera IP
struct ip_header {
    u_char ver_ihl;
    u_char tos;
    u_short tlen;
    u_short identification;
    u_short flags_fo;
    u_char ttl;
    u_char proto;
    u_short crc;
    u_int saddr;
    u_int daddr;
};

bool capturando = true;

// Convertir IP manualmente (sin winsock)
std::string ipToString(unsigned int ip) {
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;

    return std::to_string(bytes[0]) + "." +
           std::to_string(bytes[1]) + "." +
           std::to_string(bytes[2]) + "." +
           std::to_string(bytes[3]);
}

// Deteccion de teclas (para parar simulacion)
void escucharTecla() {
    std::cout << "\nPresiona 'q' y ENTER para detener captura...\n";
    char c;
    while (capturando) {
        std::cin >> c;
        if (c == 'q') {
            capturando = false;
            break;
        }
    }
}

// Protocolo
std::string getProtocolName(int proto) {
    switch (proto) {
        case 1: return "ICMP";
        case 6: return "TCP";
        case 17: return "UDP";
        default: return "OTHER";
    }
}

// Callback
void packetHandler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data) {
    const int ethernetSize = 14;

    const ip_header* ip = (ip_header*)(pkt_data + ethernetSize);

    std::string src_ip = ipToString(ip->saddr);
    std::string dst_ip = ipToString(ip->daddr);
    std::string protocol = getProtocolName(ip->proto);

    int ip_header_len = (ip->ver_ihl & 0x0F) * 4;

    const u_char* payload = pkt_data + ethernetSize + ip_header_len;
    int payload_len = header->len - (ethernetSize + ip_header_len);

    std::string message = "";
    for (int i = 0; i < payload_len && i < 50; i++) {
        if (isprint(payload[i]))
            message += payload[i];
        else
            message += '.';
    }

    std::cout << "----------------------------------\n";
    std::cout << "Origen: " << src_ip << "\n";
    std::cout << "Destino: " << dst_ip << "\n";
    std::cout << "Protocolo: " << protocol << "\n";
    std::cout << "Mensaje: " << message << "\n";
}

// Mostrar interfaces
std::vector<pcap_if_t*> listarInterfaces(pcap_if_t* alldevs) {
    std::vector<pcap_if_t*> interfaces;
    int i = 0;

    for (pcap_if_t* d = alldevs; d != nullptr; d = d->next) {
        interfaces.push_back(d);
        std::cout << i++ << ": " << d->name;
        if (d->description)
            std::cout << " (" << d->description << ")";
        std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return interfaces;
}

// Captura
void iniciarCaptura(pcap_if_t* device) {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle = pcap_open_live(device->name, SNAP_LEN, 1, 1000, errbuf);
    if (!handle) {
        std::cerr << "Error al abrir interfaz\n";
        return;
    }

    capturando = true;

    std::thread hiloTeclado(escucharTecla);

    std::cout << "\nCapturando paquetes...\n";

    while (capturando) {
        struct pcap_pkthdr* header;
        const u_char* data;

        int res = pcap_next_ex(handle, &header, &data);

        if (res == 1) {
            packetHandler(nullptr, header, data);

            // 🔹 Delay de 0.5 segundos
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if (res == 0) {
            continue; // timeout
        }
        else {
            break; // error o final
        }
    }

    std::cout << "Captura detenida.\n";

    hiloTeclado.join();
    pcap_close(handle);
}

// MAIN con menú
int main() {
    pcap_if_t* alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error: " << errbuf << std::endl;
        return 1;
    }

    std::vector<pcap_if_t*> interfaces = listarInterfaces(alldevs);

    if (interfaces.empty()) {
        std::cerr << "No hay interfaces disponibles.\n";
        return 1;
    }

    int opcion;

    while (true) {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Seleccionar interfaz y capturar\n";
        std::cout << "2. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            int index;
            std::cout << "Selecciona interfaz: ";
            std::cin >> index;

            if (index >= 0 && index < interfaces.size()) {
                iniciarCaptura(interfaces[index]);
            } else {
                std::cout << "Indice invalido\n";
            }
        }
        else if (opcion == 2) {
            break;
        }
        else {
            std::cout << "Opcion invalida\n";
        }
    }

    pcap_freealldevs(alldevs);
    return 0;
}