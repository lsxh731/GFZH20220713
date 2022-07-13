#ifndef GPIORW_H
#define GPIORW_H
#include <stdio.h>
#include <string>
#include "commmacro.h"

#ifdef UBUNTU_DEV
#include <unistd.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <termio.h>
#endif

#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

#include <QMutex> //add by zqc 2019.06.03

class CGPIORW
{
public:
    CGPIORW();
    ~CGPIORW();
 public:
    bool read_adi(char address,int *buffer_read,int fd);
    void write_do(char address,short int data,int fd);
    long int ai_data_compute(int *data_in);
 private:
    QMutex m_rwMutex;//·ÀÖ¹¶ÁÐ´³åÍ»µÄ»¥³âËø,add by zqc 2019.06.03
};

#endif // GPIORW_H
