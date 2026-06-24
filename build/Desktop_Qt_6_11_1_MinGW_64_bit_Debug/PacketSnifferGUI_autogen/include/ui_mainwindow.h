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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1299, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboInterfaces = new QComboBox(centralwidget);
        comboInterfaces->setObjectName("comboInterfaces");
        comboInterfaces->setGeometry(QRect(100, 40, 261, 28));
        btnIniciar = new QPushButton(centralwidget);
        btnIniciar->setObjectName("btnIniciar");
        btnIniciar->setGeometry(QRect(30, 100, 121, 29));
        btnLimpiar = new QPushButton(centralwidget);
        btnLimpiar->setObjectName("btnLimpiar");
        btnLimpiar->setGeometry(QRect(280, 100, 90, 29));
        tablaPaquetes = new QTableWidget(centralwidget);
        tablaPaquetes->setObjectName("tablaPaquetes");
        tablaPaquetes->setGeometry(QRect(30, 150, 1241, 221));
        txtDetalles = new QTextEdit(centralwidget);
        txtDetalles->setObjectName("txtDetalles");
        txtDetalles->setGeometry(QRect(30, 430, 1241, 111));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 40, 71, 31));
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 400, 191, 31));
        btnExportar = new QPushButton(centralwidget);
        btnExportar->setObjectName("btnExportar");
        btnExportar->setGeometry(QRect(390, 100, 111, 29));
        comboFiltro = new QComboBox(centralwidget);
        comboFiltro->setObjectName("comboFiltro");
        comboFiltro->setGeometry(QRect(870, 40, 141, 28));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(810, 40, 63, 31));
        btnPausar = new QPushButton(centralwidget);
        btnPausar->setObjectName("btnPausar");
        btnPausar->setGeometry(QRect(170, 100, 90, 29));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
