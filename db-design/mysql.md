开启服务：mysqld start

关闭服务：mysqladmin -u root -p shutdown

备份：mysqldump -u root -p train > d:/train_backup.sql

恢复: create database train;

​		mysql -u root -p train < d:/train_backup.sql;