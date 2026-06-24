#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

// Archivos del backend
#include "backend/libreria.h"
#include "backend/estructuras.h"
#include "backend/funciones.h"
#include "backend/export_csv.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Clase principal de la ventana
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Funciones que se ejecutan al usar los botones o elementos de la interfaz
    void on_btnIniciar_clicked();
    void on_btnPausar_clicked();
    void on_btnLimpiar_clicked();
    void on_btnExportar_clicked();
    void on_btnAplicarFiltros_clicked();
    void on_tablaPaquetes_cellClicked(int row, int column);
    void on_comboFiltro_currentTextChanged(const QString &arg1);
    void capturarUnPaquete();

private:
    Ui::MainWindow *ui;

    // Variables usadas para manejar las interfaces de red con Npcap
    pcap_if_t *alldevs;
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    QTimer *timerCaptura;

    // Funciones internas para preparar y actualizar la interfaz
    void configurarTabla();
    void configurarFiltros();
    void cargarInterfaces();
    void mostrarPaquetesEnTabla();

};

#endif