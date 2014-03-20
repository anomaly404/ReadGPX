#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    QFile *fp;
public:
    int curPos;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();
    void read(void* p, qint64 len);
    int readUChar();
    int readChar();
    int readInt();
    int getInt(QByteArray source, int offset);
    QByteArray getBytes();
public:  //Fpr temporary use
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
