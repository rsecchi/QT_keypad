#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pArduino(new Arduino)
{
    ui->setupUi(this);

    QList<QSerialPortInfo> infolist = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::Iterator elem = infolist.begin();

    for(int i=0; i<infolist.length(); i++)
    {
        ui->comboBox->addItem(elem->portName());
        elem++;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_11_clicked()
{

    if (pArduino->isOpen()) {
        pArduino->close();
        ui->pushButton_11->setText("connect");
        return;
    }

    pArduino->setPortName(ui->comboBox->currentText());

    if (pArduino->openArduino()) {
        pArduino->flush();
        ui->label->setText("Arduino is connected");
        ui->pushButton_11->setText("disconnect");
    } else {
        ui->label->setText("Arduino is not connected");
        ui->pushButton_11->setText("connect");
    }
}


void MainWindow::on_pushButton_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("1\r");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("2\r");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("3\r");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("4\r");
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("5\r");
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("6\r");
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("7\r");
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("8\r");
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("9\r");
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    if (pArduino) {
        pArduino->waitForBytesWritten(100);
        pArduino->write("0\r");
    }
}


