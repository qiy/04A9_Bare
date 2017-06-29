#
# Copyright (C) 2013 100ask
#              http://www.100ask.net/
####################################

if [ -z $1 ]  #判断参数1的字符串是否为空，如果为空，则打印出帮助信息
then
    echo "usage: sd_fusing.sh <SD Reader's device file> <Source file>"
    exit 0
fi

if [ -z $2 ]  #判断参数2的字符串是否为空，如果为空，则打印出帮助信息
then
    echo "usage: sd_fusing.sh <SD Reader's device file> <Source file>"
    exit 0
fi

if [ -b $1 ]  #判断参数1所指向的设备节点是否存在
then
    echo "$1 reader is identified."
else
    echo "$1 is NOT identified."
    exit -1
fi

####################################
#<verify device>

BDEV_NAME=`basename $1`
BDEV_SIZE=`cat /sys/block/${BDEV_NAME}/size`

#如果卡的容量小于0，则打印失败信息，并退出
if [ ${BDEV_SIZE} -le 0 ]; then 
 echo "Error: NO media found in card reader."
 exit 1
fi

#如果卡的容量大于32000000，则打印失败信息，并退出
if [ ${BDEV_SIZE} -gt 32000000 ]; then                               
 echo "Error: Block device size (${BDEV_SIZE}) is too large"
 exit 1
fi

####################################
# check files

SOURCE_FILE=$2
MKBL2=my_mkbl2

#检查source file是否存在
if [ ! -f ${SOURCE_FILE} ]; then                                     
 echo "Error: $2 NOT found, please build it & try again."
 exit -1
fi


#<make bl2>
#使用my_mkbl2工具来处理传入的bin，从而生成bl2.bin
${MKBL2} ${SOURCE_FILE} bl2.bin 14336                                

####################################
# fusing images

signed_bl1_position=1  #bl1的镜像烧写到sd卡的第1个扇区
bl2_position=17        #bl2的镜像烧写到sd卡的第17个扇区

#<BL1 fusing>
echo "---------------------------------------"
echo "BL1 fusing"
# 烧写bl1到SD卡512字节处
dd iflag=dsync oflag=dsync if=/work/4412/tools/E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

# 如果失败则退出
if [ $? -ne 0 ]
then
   echo Write BL1 Error!
   exit -1
fi

#<BL2 fusing>
echo "---------------------------------------"
echo "BL2 fusing"
# 烧写bl2到SD卡(512+8K)字节处, 512+8K=17x512,即第17个block
dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

# 如果失败则退出
if [ $? -ne 0 ]
then
   echo Write BL2 Error!
   exit -1
fi


#<flush to disk>
# 同步文件
sync

rm bl2.bin

####################################
#<Message Display>
echo "---------------------------------------"
echo "source file image is fused successfully."
echo "Eject SD card and insert it to Exynos 4412 board again."

