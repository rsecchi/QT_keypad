#include "arduino.h"

Arduino::Arduino()
{
    // configuring the UART
    setBaudRate(QSerialPort::Baud9600);
    setParity(QSerialPort::NoParity);
    setDataBits(QSerialPort::Data8);
    setFlowControl(QSerialPort::NoFlowControl);

}

bool Arduino::openArduino()
{
    if (portName() == "") {
        QMessageBox::warning(NULL, "", "Port not selected");
        return false;
    }

    if (!open(QIODevice::ReadWrite)) {
        QMessageBox::warning(NULL, "", "Could not open Arduino "+ errorString());
        return false;
    }

    return true;
}
