#include "serialinput.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


SerialInput::SerialInput(): serial(0){
}


QString SerialInput::SelectSerialPort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if( info.portName().contains("USB") )
            if( !info.isBusy() )
                return info.portName();
    }
    return "";
}


void SerialInput::Open(QString portName)
{
    if( serial )
    {
        serial->close();
    }
    else
    {
        serial = new QSerialPort(this);
    }
    serial->setPortName(portName);
    if (!serial->open(QIODevice::ReadWrite)) {
        emit error(tr("Can't open '%1', error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }

    if (!serial->setBaudRate(QSerialPort::Baud115200)) {
        emit error(tr("Can't set baud rate 115200 baud to port %1, error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }

    if (!serial->setDataBits(QSerialPort::Data8)) {
        emit error(tr("Can't set 8 data bits to port %1, error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }

    if (!serial->setParity(QSerialPort::NoParity)) {
        emit error(tr("Can't set no patity to port %1, error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }

    if (!serial->setStopBits(QSerialPort::OneStop)) {
        emit error(tr("Can't set 1 stop bit to port %1, error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }

    if (!serial->setFlowControl(QSerialPort::NoFlowControl)) {
        emit error(tr("Can't set no flow control to port %1, error code %2")
                   .arg(portName).arg(serial->error()));
        return;
    }
    connect(serial, SIGNAL(readyRead()), this, SLOT(Read()));
}


void SerialInput::Read()
{
    QString s = ReadLine();
    if( s != "" ) emit message(s);
}


QString SerialInput::ReadLine()
{
    QString msg;
    if( serial->isOpen() ) {
//        if (serial->waitForReadyRead(10))
        {
            while(1)
            {
                // read all there is to read
                if( serial->isReadable() )
                {
                    buffer += serial->readAll();
                }

                // check for message termitator, quit if none
                int i = buffer.indexOf('\r');
                if( i < 0 ) break;

                // we got full message so process it
                msg = buffer.left(i);

                // remove processed message from buffer and any leading unprintables
                while(i < buffer.length() && buffer[i] <= ' ') i++;
                buffer = buffer.remove(0,i);
            }
        }
    }
    return msg;
}
