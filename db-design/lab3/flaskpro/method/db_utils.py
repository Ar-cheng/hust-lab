#coding=utf-8
import pymysql

class DataBaseHandle(object):
    ''' 定义一个 MySQL 操作类'''

    def __init__(self,host,username,password,database,port):
        '''初始化数据库信息并创建数据库连接'''
        self.host = host
        self.username = username
        self.password = password
        self.database = database
        self.port = port

    def query(self, sql, args=None, one=False):
        self.db = pymysql.connect(self.host,self.username,self.password,self.database,self.port,charset='utf8')
        self.cursor = self.db.cursor()
        data = None
        try:
            self.cursor.execute(sql, args)
            if one:
                data = self.cursor.fetchone()
            else:
                data = self.cursor.fetchall()
            self.db.commit()
        except pymysql.Error as e:
            self.db.rollback()
            print(e.args[0], e.args[1])
        finally:
            self.db.close()
        return data

    def execute(self, sql, args=None,response=False):
        self.db = pymysql.connect(self.host,self.username,self.password,self.database,self.port,charset='utf8')
        self.cursor = self.db.cursor()
        data = None
        try:
            self.cursor.execute(sql, args)
            data = self.cursor.fetchall()
            self.db.commit()
        except pymysql.Error as e:
            self.db.rollback()
            print(e.args[0], e.args[1])
        finally:
            self.db.close()
        if response:
            return data
