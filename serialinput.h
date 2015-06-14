#ifndef SERIALINPUT_H
#define SERIALINPUT_H

#include <QObject>

class QString;
class QSerialPort;

class SerialInput : public QObject {
    Q_OBJECT

public:
    SerialInput();
    void Open() { Open(SelectSerialPort()); }
signals:
    void error(const QString &s);
    void message(const QString &s);

private:
    static QString SelectSerialPort();

    void Open(QString portName);
    QString ReadLine();

    QSerialPort *serial;
    QString buffer;

private slots:
    void Read();

};

#endif // SERIALINPUT_H
