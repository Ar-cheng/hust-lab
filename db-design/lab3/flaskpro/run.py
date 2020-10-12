# from method.db_utils import *
import method.db_utils
from flask import Flask, redirect, url_for, request, render_template, jsonify,session
from method.json_utils import tupletojson
import datetime

app = Flask(__name__)

app.secret_key = '168017'

db = method.db_utils.DataBaseHandle('127.0.0.1', 'root', '3323150', 'test', 3306)

@app.route("/")
def login():
    return render_template('login.html')

# @app.route("/login/post", methods=("GET", "POST"))
@app.route("/login", methods=("GET","POST"))
def login_post():
    if request.method=="GET":
        return render_template('login.html')
    if request.method=="POST":
        uid = request.form.get('uid')
        password = request.form.get('password')
        data = db.query('select * from log_info where UID = %s', uid, one=True)
        if (data[1] == password):
            authority = data[2]
            session['uid'] = uid
            session['password'] = password
            session['authority'] = authority
            session.permanent = True
            if(authority == 0):
                return render_template('index.html')
            else:
                return render_template('index-user.html')
        return render_template('login.html')

@app.route("/logout", methods=["get"])
def logout():
    session.clear()
    return {'res':'sucess'}

@app.context_processor
def my_context_processor():
    user = session.get('uid')
    if user:
        return {'login_user': user}
    return {}

@app.route("/index")
def index():
    if session:
        if session['authority'] == 0:
            return render_template('index.html')
        else:
            return render_template('index-user.html')
    else :
        return render_template('login.html')


@app.route("/index/get/employee_info", methods=["GET"])
def get_employee_info():
    sql = '''SELECT * from view_get_employee_info'''

    sql_user = '''SELECT * from view_get_employee_info where UID = %s'''

    if(session['authority'] == 1):
        data = db.query(sql_user,session['uid'])
    else:
        data = db.query(sql)
    dict = ('UID', 'UName', 'Age', 'Sex', 'DName', 'KName', 'Level', 'Base_salary','KID','DID')
    res = tupletojson(data, dict)
    return jsonify(res)


@app.route("/index/get/department_info", methods=["GET"])
def get_department_info():
    sql = '''select * from department_info'''
    data = db.query(sql)
    dict = ('DID', 'DName', 'DRef', 'DNum')
    res = tupletojson(data, dict)
    return jsonify(res)


@app.route("/index/get/kind_info", methods=["GET"])
def get_kind_info():
    sql = '''select * from kind_info'''
    data = db.query(sql)
    dict = ('KID', 'KName', 'Level', 'Base_salary')
    res = tupletojson(data, dict)
    return jsonify(res)


@app.route("/index/get/bonus_info", methods=["GET"])
def get_bonus_info():
    db = method.db_utils.DataBaseHandle('127.0.0.1', 'root', '3323150', 'test', 3306)
    sql = '''select UID, DATE_FORMAT(BDate, '%Y-%m-%d') as BDate, BType,BDays,Bonus from bonus_info'''
    sql_user = '''select UID, DATE_FORMAT(BDate, '%%Y-%%m-%%d') as BDate, BType,BDays,Bonus from bonus_info where UID = %s'''
    if(session['authority'] == 1):
        data = db.query(sql_user,session['uid'])
    else:
        data = db.query(sql)
    dict = ('UID', 'BDate', 'BType', 'BDays', 'Bonus')
    res = tupletojson(data, dict)
    return jsonify(res)


@app.route("/index/get/attendance_info", methods=["GET"])
def get_attendance_info():
    sql = '''select UID, DATE_FORMAT(ADate, '%Y-%m-%d') as ADate ,TIME_FORMAT(ATime,'%T') as ATime,TIME_FORMAT(STime,'%T') as STime from attendance_info'''
    sql_user = '''select UID,  DATE_FORMAT(ADate, '%%Y-%%m-%%d') as ADate ,TIME_FORMAT(ATime,'%%T') as ATime,TIME_FORMAT(STime,'%%T') as STime from attendance_info where UID = %s'''
    if(session['authority'] == 1):
        data = db.query(sql_user,session['uid'])
    else:
        data = db.query(sql)
    dict = ('UID', 'ADate', 'ATime', 'STime')
    res = tupletojson(data, dict)
    return jsonify(res)


@app.route("/index/get/salary_info", methods=["GET"])
def get_salary_info():
    sql = '''select UID, DATE_FORMAT(`Month`,'%Y-%m')`Month`, Base_salary,attendance_times,attendance_rate ,Bonus, Total_salary from salary_info'''
    sql_user = '''select UID, DATE_FORMAT(`Month`,'%%Y-%%m')`Month`, Base_salary,attendance_times,attendance_rate ,Bonus, Total_salary from salary_info where UID = %s'''
    if(session['authority'] == 1):
        data = db.query(sql_user,session['uid'])
    else:
        data = db.query(sql)
    dict = ('UID', 'Month', 'Base_salary','attendance_times','attendance_rate' ,'Bonus', 'Total_salary')
    res = tupletojson(data, dict)
    return jsonify(res)

@app.route("/index/get/log_info", methods=["GET"])
def get_log_info():
    sql = '''select * from log_info'''
    data = db.query(sql)
    dict = ('UID', 'Password', 'Authority')
    res = tupletojson(data, dict)
    return jsonify(res)

@app.route("/index/get/salary_report", methods=["GET"])
def get_salary_report():
    sql = '''SELECT
	UID,UName,DName,Salary,Award,Salary+Award as Total FROM view_get_salary_report;'''
    data = db.query(sql)
    dict = ('UID', 'UName', 'DName', 'Salary', 'Award' ,'Total')
    res = tupletojson(data, dict)
    return jsonify(res)

@app.route("/index/add/employee_info", methods=["POST"])
def employee_info_add():
    UID = request.get_json()['UID']
    UName = request.get_json()['UName']
    Age = int(request.get_json()['Age'])
    KID = int(request.get_json()['KID'])
    DID = int(request.get_json()['DID'])
    Sex = int(request.get_json()['Sex'])
    sql = '''insert into employee_info values(%s,%s,%s,%s,%s,%s)'''
    dict = [UID,UName,Age,Sex,KID,DID]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/update/employee_info", methods=["POST"])
def employee_info_update():
    UID = request.get_json()['UID']
    UName = request.get_json()['UName']
    Age = int(request.get_json()['Age'])
    KID = int(request.get_json()['KID'])
    DID = int(request.get_json()['DID'])
    Sex = int(request.get_json()['Sex'])
    sql = '''update employee_info set UName= %s , Age= %s ,Sex= %s, KID = %s, DID = %s where UID = %s'''
    dict = [UName,Age,Sex,KID,DID,UID]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/delete/employee_info", methods=["POST"])
def employee_info_delete():
    UID = request.get_json()['UID']
    sql = '''delete from employee_info where UID = %s'''
    data = db.query(sql,UID)
    return jsonify(data)


@app.route("/index/add/kind_info", methods=["POST"])
def kind_info_add():
    KID = request.get_json()['KID']
    KName = request.get_json()['KName']
    Level = int(request.get_json()['Level'])
    Base_salary = int(request.get_json()['Base_salary'])
    sql = '''insert into kind_info values(%s,%s,%s,%s)'''
    dict = [KID,KName,Level,Base_salary]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/update/kind_info", methods=["POST"])
def kind_info_update():
    KID = request.get_json()['KID']
    KName = request.get_json()['KName']
    Level = int(request.get_json()['Level'])
    Base_salary = int(request.get_json()['Base_salary'])
    sql = '''update kind_info set KName = %s, Level = %s, Base_salary = %s where KID = %s'''
    dict = [KName,Level,Base_salary,KID]
    data = db.query(sql,dict)
    return jsonify(data)


@app.route("/index/delete/kind_info", methods=["POST"])
def kind_info_delete():
    KID = request.get_json()['KID']
    sql = '''delete from kind_info where KID = %s'''
    data = db.query(sql,KID)
    return jsonify(data)


@app.route("/index/add/bonus_info", methods=["POST"])
def bonus_info_add():
    UID = request.get_json()['UID']
    BDate = datetime.datetime.strptime(  request.get_json()['BDate'],'%Y-%m-%d')
    BType = request.get_json()['BType']
    BDays = int(request.get_json()['BDays'])
    Bonus = int(request.get_json()['Bonus'])
    sql = '''insert into bonus_info values(%s,%s,%s,%s,%s)'''
    dict = [UID,BDate,BType,BDays,Bonus]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/update/bonus_info", methods=["POST"])
def bonus_info_update():
    UID = request.get_json()['UID']
    BDate = datetime.datetime.strptime(request.get_json()['BDate'],'%Y-%m-%d')
    BType = request.get_json()['BType']
    BDays = int(request.get_json()['BDays'])
    Bonus = int(request.get_json()['Bonus'])
    sql = '''update bonus_info set BType = %s, Bdays = %s, Bonus = %s where UID = %s and BDate = %s'''
    dict = [BType,BDays,Bonus,UID,BDate]
    data = db.query(sql,dict)
    return jsonify(data)


@app.route("/index/delete/bonus_info", methods=["POST"])
def bonus_info_delete():
    UID = request.get_json()['UID']
    BDate = datetime.datetime.strptime(request.get_json()['BDate'],'%Y-%m-%d')
    sql = '''delete from bonus_info where UID= %s and BDate = %s'''
    data = db.query(sql,[UID,BDate])
    return jsonify(data)

@app.route("/index/add/department_info", methods=["POST"])
def department_info_add():
    DID = request.get_json()['DID']
    DName = request.get_json()['DName']
    DRef = request.get_json()['DRef']
    sql = '''insert into department_info() values(%s,%s,%s,0)'''
    dict = [DID,DName,DRef]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/update/department_info", methods=["POST"])
def department_info_update():
    DID = request.get_json()['DID']
    DName = request.get_json()['DName']
    DRef = request.get_json()['DRef']
    sql = '''update department_info set DName = %s, DRef = %s where DID = %s'''
    dict = [DName,DRef,DID]
    data = db.query(sql,dict)
    return jsonify(data)


@app.route("/index/delete/department_info", methods=["POST"])
def department_info_delete():
    DID = request.get_json()['DID']
    sql = '''delete from department_info where DID = %s'''
    data = db.query(sql,DID)
    return jsonify(data)

@app.route("/index/update/log_info", methods=["POST"])
def log_info_update():
    UID = request.get_json()['UID']
    Password = request.get_json()['Password']
    Authority = request.get_json()['Authority']
    sql = '''update log_info set Password = %s, Authority = %s where UID = %s'''
    dict = [Password,Authority,UID]
    data = db.query(sql,dict)
    return jsonify(data)

@app.route("/index/update/attendance_info", methods=["POST"])
def attendance_info_update():
    UID = session['uid']
    type = request.get_json()['type']
    ADate = request.get_json()['ADate']
    ATime = request.get_json()['ATime']
    STime = request.get_json()['STime']
    sql = '''call attendance_update(%s,%s,%s,%s,%s)'''
    dict = [UID,ADate,ATime,STime,type]
    data = db.query(sql,dict)
    return jsonify(data)


if __name__ == '__main__':
    app.run(host='0.0.0.0')
    # app.run()
