#include "mainwindow.h"
#include <QFile>
#include "ui_mainwindow.h"
#include "GPXByteBuffer.h"
#include <QThread>
#include <QDebug>
#include <QBuffer>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curPos = 0 ; //temp
    this->start();
}

void MainWindow::start() {
    fp = new QFile("/home/anomaly/Downloads/gpx.gpx");
    QString text = "";
    if (!fp->open(QIODevice::ReadOnly))
                text = "error opening";
    QString type;
    QByteArray out=getBytes();
    GPXByteBuffer *srcBuff = new GPXByteBuffer(out);
    int expectLen = 0;
    type = srcBuff->readBytes(4);
    qDebug()<<type;
    QByteArray bcfsBuffer;
    int s=0;
    if(type == "BCFZ") {
        expectLen = getInt(srcBuff->readBytes(4),0);
        qDebug()<<expectLen<<endl;
        while ( !srcBuff->end() && srcBuff->offset() < expectLen ){
            int flag = srcBuff->readBits(1);
            if (flag == 1) {
                int bits = srcBuff->readBits(4);
                int offs = srcBuff->readBitsReversed(bits);
                int size = srcBuff->readBitsReversed(bits);

                QByteArray bcfsBytes = bcfsBuffer;
                int pos = ( bcfsBytes.length() - offs );
                for( int i = 0; i < (size > offs ? offs : size) ; i ++ ){
                    bcfsBuffer[s++] = bcfsBytes[pos + i];
                    //qDebug()<<bcfsBuffer[s-1];
                }
            }
            else {
                int size = srcBuff->readBitsReversed(2);
                for(int i = 0; i < size; i ++ ){
                    bcfsBuffer[s++] = srcBuff->readBits(8);
                    //qDebug()<<bcfsBuffer[s-1];
                }
            }
        }
    }
    QFile f ("/home/anomaly/temp.txt");
    f.open(QIODevice::WriteOnly);
    QDataStream ou(&f);   // we will serialize the data into the file
    for(int i = 0; i<s;i++)
    std::cout<<(bcfsBuffer[i]);

}
int MainWindow::getInt(QByteArray source, int offset) {
    QByteArray bytes;
    bytes[0] = source[ offset + 0];
    bytes[1] = source[ offset + 1];
    bytes[2] = source[ offset + 2];
    bytes[3] = source[ offset + 3];
    return ((bytes[3] & 0xff) << 24) | ((bytes[2] & 0xff) << 16) | ((bytes[1] & 0xff) << 8) | (bytes[0] & 0xff);
}

//.........................................
// READ
//........................................
void MainWindow::read(void* p, qint64 len)
      {
      if (len == 0)
            return;
      qint64 rv = fp->read((char*)p, len);
      if (rv != len) {
            abort();
            }
      curPos += len;
      }

//---------------------------------------------------------
//   readChar
//---------------------------------------------------------

int MainWindow::readChar()
      {
      char c;
      read(&c, 1);
      return c;
      }

//---------------------------------------------------------
//   readUChar
//---------------------------------------------------------

int MainWindow::readUChar()
      {
      uchar c;
      read(&c, 1);
      return c;
      }
//---------------------------------------------------------
//   readInt
//---------------------------------------------------------

int MainWindow::readInt()
      {
      uchar x;
      read(&x, 1);
      int r = x;
      read(&x, 1);
      r += x << 8;
      read(&x, 1);
      r += x << 16;
      read(&x, 1);
      r += x << 24;
      return r;
      }

// GET BYTES
QByteArray MainWindow::getBytes() {
    QByteArray out;
    int read = 0;
    char p;
    int i=0,j=0;
    while((read = fp->read(&p,1)) != 0){
      out[i++] = (uchar)(p);
    }

    return out;
}

MainWindow::~MainWindow()
{
    delete ui;
}
