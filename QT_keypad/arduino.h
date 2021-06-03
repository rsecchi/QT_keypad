#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QMessageBox>

class Arduino: public QSerialPort
{
public:
    Arduino();
    bool openArduino();

};

#endif // ARDUINO_H
