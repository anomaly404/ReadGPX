#include"GPXByteBuffer.h"
#include <QDebug>
GPXByteBuffer::GPXByteBuffer(QByteArray buff) {
    buffer = buff;
    position = 0;
    BUFFER_TYPE_BITS = 8;
}

int GPXByteBuffer::length() {
    return buffer.length();
}

int GPXByteBuffer::offset() {
    return position/BUFFER_TYPE_BITS;
}

bool GPXByteBuffer::end() {
    return offset() >= length();
}

int GPXByteBuffer::readBit() {
    int bit = -1;
    int byteIndex = ( position / BUFFER_TYPE_BITS );
    int byteOffset = ( (BUFFER_TYPE_BITS - 1) - ( position % BUFFER_TYPE_BITS ) );
    if( byteIndex >= 0 && byteIndex < buffer.length() ){
        bit = ( ((buffer[ byteIndex ] & 0xff) >> byteOffset ) & 0x01 );
           position ++;
 //          qDebug()<<" pos "<<bit<<endl;
    }
    return bit;
}
int GPXByteBuffer::readBits(int count) {
    int bits = 0;
    for( int i = (count - 1) ; i >= 0 ; i -- ){
        bits |= ( readBit() << i  );
    }
    return bits;
}
int GPXByteBuffer::readBitsReversed(int count) {
    int bits = 0;
    for( int i = 0 ; i < count ; i ++ ){
        bits |= ( readBit() << i  );
    }
    return bits;
}
QByteArray GPXByteBuffer::readBytes(int count) {
    QByteArray bytes;
    for( int i = 0 ; i < count ; i++ ){
        bytes[i] = (unsigned char)readBits(8);
        qDebug()<<"voila "<<bytes[i]<<endl;
    }
    return bytes;

}
