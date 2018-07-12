#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtsharedmemory.h>

class MyValue : public QQtSharedMemory
{
    Q_OBJECT
public:
    explicit MyValue ( const QString& key, QObject* parent = 0 ) : QQtSharedMemory ( key, parent ) {
        str = "This is a test value";
    }

    void setString ( QByteArray str ) { this->str = str; }
    QByteArray getString() { return str; }

private:
    quint8 a;
    quint16 mSize;//
    //quint32 len;
    QByteArray str;
    quint16 b;

    // QQtSharedMemory interface
public:
    virtual void initializer() override {
        create ( 2048 );
        attach();
    }
    virtual void packer() override {
        lock();

        QByteArray bytes;
        bytes << a;
        bytes << mSize;
        writeString ( bytes, str );
        bytes << b;

        memcpy ( data(), bytes.constData(), bytes.size() );
        //pline() << data();
        //pline() << "write:" << str;

        unlock();
    }
    virtual void parser() override {
        lock();

        QByteArray bytes;
        bytes.resize ( size() );
        memcpy ( bytes.data(), data(), size() );

        //user data struct
        bytes >> a;
        bytes >> mSize;
        str = readString ( bytes );
        bytes >> b;

        //pline() << data();
        //pline() << "read:" << str;
        unlock();
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
