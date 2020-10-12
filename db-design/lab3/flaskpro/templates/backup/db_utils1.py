#! /usr/bin/env python3
# -*- coding:utf-8 -*-

import pymysql

class PyMysql:

    host = 'localhost'
    user = 'user'
    password = 'pwssword'
    db = 'test'
    charset = 'utf8mb4'
    cursorclass = pymysql.cursors.DictCursor

    @classmethod
    def query(self,sql,args=None,fetchone=False):
        # 创建连接
        connection = pymysql.connect(host=self.host, user=self.user,
                                     password=self.password, db=self.db, charset =self.charset, cursorclass = self.cursorclass)
        result = None
        try:
            # 开启游标
            with connection.cursor() as cursor:
                # 返回响应结果数
                effect_row = cursor.execute(self.sql_args_2_sql(sql, args))
                if fetchone:
                    result = cursor.fetchone()
                else:
                    result = cursor.fetchall()
        except Exception as e:
            print(e)
        finally:
            # 关闭连接
            connection.close()

        return result

    @classmethod
    def execute(self,sql,args=None,response=False):
        connection = pymysql.connect(host=self.host, user=self.user,
                                     password=self.password, db=self.db, charset =self.charset, cursorclass = self.cursorclass)
        result = None
        try:
            with connection.cursor() as cursor:
                effect_row = cursor.execute(self.sql_args_2_sql(sql, args))
                if response:
                    result = cursor.fetchall()

            # connection is not autocommit by default. So you must commit to save your changes.
            connection.commit()
        except Exception as e:
            print(e)
            # error rollback
            connection.rollback()
        finally:
            connection.close()

        if response:
            return result

    @staticmethod
    def sql_args_2_sql(sql,args):
        '''
        fix  issue  %d format: a number is required, not str
        :param sql: sql语句
        :param args: 格式化参数
        :return: 组合之后的sql语句
        '''
        if args is None:
            return sql
        if sql.find('%') > -1:
            return sql % args
        elif sql.find('{') > -1:
            if type(args) is dict:
                return sql.format(**args)
            else:
                return sql.format(*args)
        return sql

