/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboInterfaces;
    QPushButton *btnIniciar;
    QPushButton *btnLimpiar;
    QTableWidget *tablaPaquetes;
    QTextEdit *txtDetalles;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnExportar;
    QComboBox *comboFiltro;
    QLabel *label_3;
    QPushButton *btnPausar;
    QTextEdit *txtRaw;
    QLabel *label_4;
    QLineEdit *txtFiltroSrcIP;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtFiltroDstIP;
    QLineEdit *txtFiltroSrcPort;
    QPushButton *btnAplicarFiltros;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1299, 721);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboInterfaces = new QComboBox(centralwidget);
        comboInterfaces->setObjectName("comboInterfaces");
        comboInterfaces->setGeometry(QRect(100, 60, 261, 28));
        btnIniciar = new QPushButton(centralwidget);
        btnIniciar->setObjectName("btnIniciar");
        btnIniciar->setGeometry(QRect(30, 130, 121, 29));
        btnLimpiar = new QPushButton(centralwidget);
        btnLimpiar->setObjectName("btnLimpiar");
        btnLimpiar->setGeometry(QRect(280, 130, 90, 29));
        tablaPaquetes = new QTableWidget(centralwidget);
        tablaPaquetes->setObjectName("tablaPaquetes");
        tablaPaquetes->setGeometry(QRect(30, 170, 1241, 291));
        txtDetalles = new QTextEdit(centralwidget);
        txtDetalles->setObjectName("txtDetalles");
        txtDetalles->setGeometry(QRect(30, 520, 601, 111));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 60, 71, 31));
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 490, 191, 31));
        btnExportar = new QPushButton(centralwidget);
        btnExportar->setObjectName("btnExportar");
        btnExportar->setGeometry(QRect(390, 130, 111, 29));
        comboFiltro = new QComboBox(centralwidget);
        comboFiltro->setObjectName("comboFiltro");
        comboFiltro->setGeometry(QRect(850, 40, 141, 28));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(640, 40, 63, 31));
        btnPausar = new QPushButton(centralwidget);
        btnPausar->setObjectName("btnPausar");
        btnPausar->setGeometry(QRect(170, 130, 90, 29));
        txtRaw = new QTextEdit(centralwidget);
        txtRaw->setObjectName("txtRaw");
        txtRaw->setGeometry(QRect(670, 520, 601, 111));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(670, 490, 141, 31));
        txtFiltroSrcIP = new QLineEdit(centralwidget);
        txtFiltroSrcIP->setObjectName("txtFiltroSrcIP");
        txtFiltroSrcIP->setGeometry(QRect(1120, 40, 151, 28));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(720, 40, 121, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(1030, 40, 81, 31));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(740, 90, 91, 31));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(1000, 90, 121, 31));
        txtFiltroDstIP = new QLineEdit(centralwidget);
        txtFiltroDstIP->setObjectName("txtFiltroDstIP");
        txtFiltroDstIP->setGeometry(QRect(840, 90, 151, 28));
        txtFiltroSrcPort = new QLineEdit(centralwidget);
        txtFiltroSrcPort->setObjectName("txtFiltroSrcPort");
        txtFiltroSrcPort->setGeometry(QRect(1120, 90, 151, 28));
        btnAplicarFiltros = new QPushButton(centralwidget);
        btnAplicarFiltros->setObjectName("btnAplicarFiltros");
        btnAplicarFiltros->setGeometry(QRect(1159, 130, 111, 29));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(tooltip)
        btnIniciar->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Inicia la captura de los paquetes de la interfaz seleccionada.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnIniciar->setText(QCoreApplication::translate("MainWindow", "Iniciar captura", nullptr));
#if QT_CONFIG(tooltip)
        btnLimpiar->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Limpia la tabla de los paquetes</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLimpiar->setText(QCoreApplication::translate("MainWindow", "Limpiar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Interfaz:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Detalles del paquete: </span></p></body></html>", nullptr));
        btnExportar->setText(QCoreApplication::translate("MainWindow", "Exportar CSV", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Filtros:</span></p></body></html>", nullptr));
        btnPausar->setText(QCoreApplication::translate("MainWindow", "Pausar", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Contenido RAW:</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Por protocolo:</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Ip origen: </span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Ip destino: </span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Puerto origen:</span></p></body></html>", nullptr));
        btnAplicarFiltros->setText(QCoreApplication::translate("MainWindow", "Aplicar filtros", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
