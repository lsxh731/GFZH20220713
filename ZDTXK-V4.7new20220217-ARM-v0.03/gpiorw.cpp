/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: gpiorw.cpp
** 摘要: GPIO数据读写类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.11.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.11.01   V1.0      创建
**
****************************************************************************/
#include "gpiorw.h"
#include <QMutexLocker> //add by zqc 2019.06.03

//构造函数
CGPIORW::CGPIORW()
{
}
//析构函数
CGPIORW::~CGPIORW()
{
}
bool CGPIORW::read_adi(char address,int *buffer_read,int fd)
{
#ifdef UBUNTU_DEV //Compiler Switch
  QMutexLocker locker(&m_rwMutex);
    int i,j,ret;
    ssize_t length_w,length_r = MAX_SIZE;
        //step 1: set all gpio input
    int buffer_read_tmp[MAX_SIZE];
     for(i=0;i<MAX_SIZE;i++)
     {
         buffer_read_tmp[i]=-1;
     }
    if(ret = read (fd ,buffer_read_tmp,length_r))
    {
            perror("read\n");
            close(fd);
            return false;
    }
    //step 2: write address
    ret = ioctl(fd,(address&0x01)>>0,4);
    ret = ioctl(fd,(address&0x02)>>1,5);
    ret = ioctl(fd,(address&0x04)>>2,6);
    ret = ioctl(fd,(address&0x08)>>3,7);

    ret = ioctl(fd,(address&0x10)>>4,8);
    ret = ioctl(fd,(address&0x20)>>5,9);
    ret = ioctl(fd,(address&0x40)>>6,10);
    ret = ioctl(fd,(address&0x80)>>7,11);
    //step 3: Enable chipselect and OE
    ret = ioctl(fd, 1,3);  //RW
    for(j=0;j<10;j++);
    ret = ioctl(fd, 0,0);  //CS0
    ret = ioctl(fd, 0,2);  //OE
    //usleep(100);
    //step 4: read data
    if(ret = read (fd ,buffer_read_tmp,length_r))
    {
            perror("read\n");
            close(fd);
            return false;
     }
    for(i=0;i<MAX_SIZE;i++)
        buffer_read[i] = buffer_read_tmp[i];
    //step 5: disable chipselect and OE
    ret = ioctl(fd, 1,2);
    ret = ioctl(fd, 1,0);
#endif //Compiler Switch
    return true;
}
void  CGPIORW::write_do(char address,short int data,int fd)
{
#ifdef UBUNTU_DEV //Compiler Switch
   QMutexLocker locker(&m_rwMutex);
    int i,j,ret;
    //write DO

    //step 1: write address
    /************Write DO*****address = 0x0C*****************/
    ret = ioctl(fd,(address&0x01)>>0,4);
    ret = ioctl(fd,(address&0x02)>>1,5);
    ret = ioctl(fd,(address&0x04)>>2,6);
    ret = ioctl(fd,(address&0x08)>>3,7);

    ret = ioctl(fd,(address&0x10)>>4,8);
    ret = ioctl(fd,(address&0x20)>>5,9);
    ret = ioctl(fd,(address&0x40)>>6,10);
    ret = ioctl(fd,(address&0x80)>>7,11);

    //step 2: write data
    /************Write DO*****data = 0x0C*****************/
    ret = ioctl(fd,(data&0x0001)>>0,12);
    ret = ioctl(fd,(data&0x0002)>>1,13);
    ret = ioctl(fd,(data&0x0004)>>2,14);
    ret = ioctl(fd,(data&0x0008)>>3,15);

    ret = ioctl(fd,(data&0x0010)>>4,16);
    ret = ioctl(fd,(data&0x0020)>>5,17);
    ret = ioctl(fd,(data&0x0040)>>6,18);
    ret = ioctl(fd,(data&0x0080)>>7,19);

    ret = ioctl(fd,(data&0x0100)>>8,20);
    ret = ioctl(fd,(data&0x0200)>>9,21);
    ret = ioctl(fd,(data&0x0400)>>10,22);
    ret = ioctl(fd,(data&0x0800)>>11,23);

    ret = ioctl(fd,(data&0x1000)>>12,24);
    ret = ioctl(fd,(data&0x2000)>>13,25);
    ret = ioctl(fd,(data&0x4000)>>14,26);
    ret = ioctl(fd,(data&0x8000)>>15,27);

    //step 3: Enable chipselect and WE ;disable OE
    ret = ioctl(fd, 1,2); //disable OE
    for(j=0;j<10;j++);
    ret = ioctl(fd, 0,0); //enable chipselect
    ret = ioctl(fd, 0,3); //enable WE

    //step 4:delay 500ns
    for(j=0;j<10;j++);

    //step 5:disable chipselect and WE
    ret = ioctl(fd, 1,3); //enable WE
    ret = ioctl(fd, 1,0); //enable chipselect
#endif //Compiler Switch
}

long int CGPIORW::ai_data_compute(int *data_in)
{
    long int data_out=0;
#ifdef UBUNTU_DEV //Compiler Switch
    data_out = data_in[15]*pow(2,15) + data_in[14]*pow(2,14) + data_in[13]*pow(2,13) + data_in[12]*pow(2,12)+ data_in[11]*pow(2,11) + data_in[10]*pow(2,10) + data_in[9]*pow(2,9)+ data_in[8]*pow(2,8)
    + data_in[7]*pow(2,7) + data_in[6]*pow(2,6) + data_in[5]*pow(2,5) + data_in[4]*pow(2,4) + data_in[3]*pow(2,3) + data_in[2]*pow(2,2) + data_in[1]*pow(2,1) + data_in[0]*pow(2,0);
#else
    data_out = data_in[15]*qPow(2,15) + data_in[14]*qPow(2,14) + data_in[13]*qPow(2,13) + data_in[12]*qPow(2,12)+ data_in[11]*qPow(2,11) + data_in[10]*qPow(2,10) + data_in[9]*qPow(2,9)+ data_in[8]*qPow(2,8)
    + data_in[7]*qPow(2,7) + data_in[6]*qPow(2,6) + data_in[5]*qPow(2,5) + data_in[4]*qPow(2,4) + data_in[3]*qPow(2,3) + data_in[2]*qPow(2,2) + data_in[1]*qPow(2,1) + data_in[0]*qPow(2,0);
#endif
    return data_out;
}
