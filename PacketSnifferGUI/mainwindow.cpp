#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QStringList>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QFileDialog>
#include <QDebug>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    alldevs = nullptr;
    handle = nullptr;

    timerCaptura = new QTimer(this);

    connect(timerCaptura, SIGNAL(timeout()),
            this, SLOT(capturarUnPaquete()));

    configurarTabla();
    configurarFiltros();
    cargarInterfaces();

    ui->txtDetalles->setReadOnly(true);
    ui->txtRaw->setReadOnly(true);

    ui->btnPausar->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if (timerCaptura != nullptr)
    {
        timerCaptura->stop();
    }

    if (handle != nullptr)
    {
        pcap_close(handle);
        handle = nullptr;
    }

    if (alldevs != nullptr)
    {
        pcap_freealldevs(alldevs);
    }

    delete ui;
}

// Configura la tabla donde se muestran los paquetes
void MainWindow::configurarTabla()
{
    ui->tablaPaquetes->setColumnCount(7);

    QStringList encabezados;
    encabezados << "ID"
                << "IP Origen"
                << "IP Destino"
                << "Protocolo"
                << "Puerto Origen"
                << "Puerto Destino"
                << "Tamaño";

    ui->tablaPaquetes->setHorizontalHeaderLabels(encabezados);

    ui->tablaPaquetes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaPaquetes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaPaquetes->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tablaPaquetes->horizontalHeader()->setStretchLastSection(true);
}

// Agrega las opciones de filtrado por protocolo
void MainWindow::configurarFiltros()
{
    ui->comboFiltro->clear();

    ui->comboFiltro->addItem("Todos");
    ui->comboFiltro->addItem("TCP");
    ui->comboFiltro->addItem("UDP");
    ui->comboFiltro->addItem("ICMP");
    ui->comboFiltro->addItem("OTRO");
}

// Carga las interfaces de red disponibles
void MainWindow::cargarInterfaces()
{
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        QMessageBox::critical(this, "Error", errbuf);
        return;
    }

    ui->comboInterfaces->clear();

    for (pcap_if_t *d = alldevs; d != nullptr; d = d->next)
    {
        QString descripcion;

        if (d->description != nullptr)
        {
            descripcion = d->description;
        }
        else
        {
            descripcion = d->name;
        }

        // Evita mostrar interfaces virtuales o poco útiles
        if (descripcion.contains("WAN Miniport", Qt::CaseInsensitive) ||
            descripcion.contains("Wi-Fi Direct", Qt::CaseInsensitive) ||
            descripcion.contains("VirtualBox", Qt::CaseInsensitive) ||
            descripcion.contains("Bluetooth", Qt::CaseInsensitive))
        {
            continue;
        }

        QString texto = descripcion + "\n" + QString(d->name);

        // Guardamos el apuntador real de la interfaz dentro del ComboBox
        quintptr ptr = reinterpret_cast<quintptr>(d);
        ui->comboInterfaces->addItem(texto, QVariant::fromValue(static_cast<qulonglong>(ptr)));
    }

    if (ui->comboInterfaces->count() == 0)
    {
        QMessageBox::warning(this, "Aviso", "No se encontraron interfaces de red útiles");
    }
}

// Inicia la captura de paquetes
void MainWindow::on_btnIniciar_clicked()
{
    if (alldevs == nullptr)
    {
        QMessageBox::warning(this, "Error", "No hay interfaces cargadas");
        return;
    }

    if (timerCaptura->isActive())
    {
        QMessageBox::information(this, "Aviso", "La captura ya está en ejecución");
        return;
    }

    if (ui->comboInterfaces->currentIndex() < 0)
    {
        QMessageBox::warning(this, "Error", "No hay una interfaz seleccionada");
        return;
    }

    // Recuperamos el apuntador real de la interfaz seleccionada
    qulonglong valor = ui->comboInterfaces->currentData().toULongLong();
    pcap_if_t *device = reinterpret_cast<pcap_if_t *>(static_cast<quintptr>(valor));

    if (device == nullptr)
    {
        QMessageBox::warning(this, "Error", "Interfaz inválida");
        return;
    }

    qDebug() << "Nombre de interfaz:" << device->name;

    if (device->description != nullptr)
    {
        qDebug() << "Descripcion:" << device->description;
    }

    ui->tablaPaquetes->setRowCount(0);
    ui->txtDetalles->clear();

    packet_count = 0;

    handle = open_device(device, errbuf);

    if (handle == nullptr)
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el dispositivo");
        return;
    }

    timerCaptura->start(50);

    // Mientras captura, no dejamos cambiar la interfaz
    ui->comboInterfaces->setEnabled(false);

    ui->btnPausar->setEnabled(true);
    ui->btnPausar->setText("Pausar");
}

// Pausa o reanuda la captura
void MainWindow::on_btnPausar_clicked()
{
    if (handle == nullptr)
    {
        return;
    }

    if (timerCaptura->isActive())
    {
        timerCaptura->stop();
        ui->btnPausar->setText("Reanudar");
    }
    else
    {
        timerCaptura->start(50);
        ui->btnPausar->setText("Pausar");
    }
}

// Muestra los paquetes capturados aplicando el filtro seleccionado
void MainWindow::mostrarPaquetesEnTabla()
{
    ui->tablaPaquetes->setRowCount(0);

    QString filtroProtocolo = ui->comboFiltro->currentText();
    QString filtroSrcIP = ui->txtFiltroSrcIP->text();
    QString filtroDstIP = ui->txtFiltroDstIP->text();
    QString filtroSrcPort = ui->txtFiltroSrcPort->text();

    for (int i = 0; i < packet_count; i++)
    {
        struct packet_info *p = &packets[i];

        QString protocolo = QString(p->protocol);
        QString srcIP = QString(p->src_ip);
        QString dstIP = QString(p->dst_ip);

        /*if (protocolo != "TCP" && protocolo != "UDP" && protocolo != "ICMP")
        {
            continue;
        }
        */

        if (filtroProtocolo != "Todos" && protocolo != filtroProtocolo)
        {
            continue;
        }

        if (!filtroSrcIP.isEmpty() && !srcIP.contains(filtroSrcIP))
        {
            continue;
        }

        if (!filtroDstIP.isEmpty() && !dstIP.contains(filtroDstIP))
        {
            continue;
        }

        if (!filtroSrcPort.isEmpty() && p->src_port != filtroSrcPort.toInt())
        {
            continue;
        }

        int fila = ui->tablaPaquetes->rowCount();

        ui->tablaPaquetes->insertRow(fila);

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(p->id));

        itemId->setData(Qt::UserRole, i);

        ui->tablaPaquetes->setItem(fila, 0, itemId);
        ui->tablaPaquetes->setItem(fila, 1, new QTableWidgetItem(p->src_ip));
        ui->tablaPaquetes->setItem(fila, 2, new QTableWidgetItem(p->dst_ip));
        ui->tablaPaquetes->setItem(fila, 3, new QTableWidgetItem(p->protocol));
        ui->tablaPaquetes->setItem(fila, 4, new QTableWidgetItem(QString::number(p->src_port)));
        ui->tablaPaquetes->setItem(fila, 5, new QTableWidgetItem(QString::number(p->dst_port)));
        ui->tablaPaquetes->setItem(fila, 6, new QTableWidgetItem(QString::number(p->size)));
    }
}

// Limpia la tabla y los detalles
void MainWindow::on_btnLimpiar_clicked()
{
    if (timerCaptura->isActive())
    {
        timerCaptura->stop();
    }

    if (handle != nullptr)
    {
        pcap_close(handle);
        handle = nullptr;
    }

    ui->tablaPaquetes->setRowCount(0);
    ui->txtDetalles->clear();
    ui->txtRaw->clear();

    ui->txtFiltroSrcIP->clear();
    ui->txtFiltroDstIP->clear();
    ui->txtFiltroSrcPort->clear();

    packet_count = 0;

    ui->comboInterfaces->setEnabled(true);

    ui->btnPausar->setEnabled(false);
    ui->btnPausar->setText("Pausar");
}

// Muestra los detalles del paquete seleccionado
void MainWindow::on_tablaPaquetes_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    if (row < 0)
    {
        return;
    }

    QTableWidgetItem *itemId = ui->tablaPaquetes->item(row, 0);

    if (itemId == nullptr)
    {
        return;
    }

    int indiceReal = itemId->data(Qt::UserRole).toInt();

    if (indiceReal < 0 || indiceReal >= packet_count)
    {
        return;
    }

    struct packet_info *p = &packets[indiceReal];

    QString detalles;

    detalles += "ID del paquete: " + QString::number(p->id) + "\n";
    detalles += "IP Origen: " + QString(p->src_ip) + "\n";
    detalles += "IP Destino: " + QString(p->dst_ip) + "\n";
    detalles += "Protocolo: " + QString(p->protocol) + "\n";
    detalles += "Puerto Origen: " + QString::number(p->src_port) + "\n";
    detalles += "Puerto Destino: " + QString::number(p->dst_port) + "\n";
    detalles += "Tamaño: " + QString::number(p->size) + " bytes\n";

    ui->txtDetalles->setText(detalles);

    // Muestra el contenido RAW del paquete
    ui->txtRaw->setText(QString(p->raw));
}

// Exporta los paquetes capturados a un archivo CSV
void MainWindow::on_btnExportar_clicked()
{
    if (packet_count == 0)
    {
        QMessageBox::warning(this, "Aviso", "No hay paquetes para exportar");
        return;
    }

    QString archivo = QFileDialog::getSaveFileName(
        this,
        "Guardar captura como CSV",
        "captura.csv",
        "Archivos CSV (*.csv)"
        );

    if (archivo.isEmpty())
    {
        return;
    }

    QByteArray nombreArchivo = archivo.toLocal8Bit();

    export_all_csv(nombreArchivo.data());

    QMessageBox::information(this, "CSV generado", "El archivo CSV se guardó correctamente");
}

// Actualiza la tabla cuando cambia el filtro
void MainWindow::on_comboFiltro_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    mostrarPaquetesEnTabla();
    ui->txtDetalles->clear();
    ui->txtRaw->clear();
}

// Captura un paquete cada vez que se activa el timer
void MainWindow::capturarUnPaquete()
{
    if (handle == nullptr)
    {
        return;
    }

    if (packet_count >= MAX_PACKETS)
    {
        timerCaptura->stop();

        pcap_close(handle);
        handle = nullptr;

        ui->comboInterfaces->setEnabled(true);

        ui->btnPausar->setEnabled(false);
        ui->btnPausar->setText("Pausar");

        QMessageBox::information(this, "Captura finalizada", "Se alcanzó el límite de paquetes");
        return;
    }

    struct pcap_pkthdr header;
    const u_char *packet;

    int antes = packet_count;

    packet = pcap_next(handle, &header);

    if (packet == nullptr)
    {
        qDebug("pcap_next no regreso paquete");
        return;
    }

    qDebug() << "Llego paquete. Tamano:" << header.len;

    process_packet(packet, header);

    if (packet_count > antes)
    {
        qDebug() << "Paquete guardado. Total:" << packet_count;
        mostrarPaquetesEnTabla();
    }
    else
    {
        qDebug("Llego un paquete, pero process_packet lo ignoró");
    }
}

void MainWindow::on_btnAplicarFiltros_clicked()
{
    mostrarPaquetesEnTabla();
    ui->txtDetalles->clear();
    ui->txtRaw->clear();
}