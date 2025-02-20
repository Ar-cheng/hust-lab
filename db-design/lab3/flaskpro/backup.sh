#!/bin/bash
#功能说明：本功能用于备份mysql数据库
#编写日期：2020/06/9
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/local/mysql/bin
export PATH
#数据库用户名
dbuser='user'
#数据库密码
dbpasswd='3323150'
#数据库名,可以定义多个数据库，中间以空格隔开，如：test test1 test2
dbname='test'
#备份时间
backtime=`date +%Y%m%d%H%M%S`
#日志备份路径
logpath='/opt/mysqlbackup/log'
#数据备份路径
datapath='/opt/mysqlbackup'
#日志记录头部
echo ‘”备份时间为${backtime},备份数据库表 ${dbname} 开始” >> ${logpath}/mysqllog.log
#正式备份数据库
for table in $dbname; do
source=`mysqldump  -u${dbuser} -p${dbpasswd} --single-transaction ${table}> ${datapath}/${backtime}.sql` 2>> ${logpath}/mysqllog.log;
#备份成功以下操作
if [ "$?" == 0 ];then
cd $datapath
#为节约硬盘空间，将数据库压缩
tar jcf ${table}${backtime}.tar.bz2 ${backtime}.sql > /dev/null
#删除原始文件，只留压缩后文件
rm -f ${datapath}/${backtime}.sql
echo “数据库表 ${dbname} 备份成功!!” >> ${logpath}/mysqllog.log
else
#备份失败则进行以下操作
echo “数据库表 ${dbname} 备份失败!!” >> ${logpath}/mysqllog.log
fi
done