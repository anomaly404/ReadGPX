#ifndef GPXBYTEBUFFER_H
#define GPXBYTEBUFFER_H
#include <QByteArray>



class GPXByteBuffer {
    int BUFFER_TYPE_BITS;
    int position;
    QByteArray buffer;

public :
    GPXByteBuffer(QByteArray buff);
    int length();
    int offset();
    bool end();
    int readBit();
    int readBits(int count);
    int readBitsReversed(int count);
    QByteArray readBytes(int count);
    ~GPXByteBuffer();
};

#endif // GPXBYTEBUFFER_H
