create.sql为建表和触发器，函数创建相关的文件

backup.sql为数据库的结构和数据转储文件，可直接在mysql数据库中允许对数据库进行恢复



关于实验项目的相关说明

web项目目前部署在：http://121.199.43.169/

服务到期之前均可通IP进行访问



若服务停止，也可通过以下方式构建flask本地项目进行演示：

- 装好本地python3环境
- pip安装 ./flaskpro/requirement.txt中的相关依赖包
- 本地启动flask项目，5000端口访问，run.py为项目主文件