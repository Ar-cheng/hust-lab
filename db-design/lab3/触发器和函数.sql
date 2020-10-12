//添加新用户时添加新账户

DROP TRIGGER
IF
	EXISTS add_new_log;

CREATE TRIGGER add_new_log AFTER INSERT ON employee_info FOR EACH ROW
BEGIN
		INSERT INTO log_info
	VALUES
	( new.UID, new.UID, 1 );
END;

//删除用户时删除对应的账户

DROP TRIGGER
IF
	EXISTS del_old_log;

CREATE TRIGGER del_old_log BEFORE DELETE ON employee_info FOR EACH ROW
BEGIN
	DELETE FROM log_info where log_info.UID=OLD.UID;
END;

//添加用户时对应的部门人数自增

DROP TRIGGER
IF
	EXISTS department_people_num_plus;
CREATE TRIGGER department_people_num_plus AFTER INSERT ON employee_info FOR EACH ROW
BEGIN
		UPDATE department_info 
		SET Dnum = IFNULL( Dnum, 0 )+ 1 
	WHERE
	DID = new.DID;
END;

//删除员工时对应的部门人数自减

DROP TRIGGER
IF
	EXISTS department_people_num_minus;
CREATE TRIGGER department_people_num_minus AFTER DELETE ON employee_info FOR EACH ROW
BEGIN
		UPDATE department_info 
		SET Dnum = Dnum - 1 
	WHERE
	DID = old.DID;
END;

//更新员工部门时，对离开的部门和加入的部门人数进行修正

DROP TRIGGER
IF
	EXISTS department_people_num_update;
CREATE TRIGGER department_people_num_update AFTER UPDATE ON employee_info FOR EACH ROW
BEGIN
	IF
		( old.DID != new.DID ) 
		THEN
			UPDATE department_info 
			SET Dnum = Dnum + 1 
		WHERE
			DID = new.DID;
		UPDATE department_info 
		SET Dnum = Dnum - 1 
		WHERE
			DID = old.DID;
		END IF;
END;


//签到和签退的存储过程
DROP PROCEDURE
IF
	EXISTS attendance_update;
CREATE PROCEDURE attendance_update ( UID CHAR ( 10 ), ADate date, ATime time, STime time, type INT ) BEGIN
	DECLARE
		flag INT;
	SELECT
		count(*) INTO flag 
	FROM
		attendance_info 
	WHERE
		attendance_info.UID = UID 
		AND attendance_info.ADate = ADate;
	IF
		type = 0 
		AND flag = 0 THEN
			INSERT INTO attendance_info
		VALUES
			( UID, ADate, ATime, NULL );
		
		ELSEIF type = 1 
		AND flag = 1 THEN
			UPDATE attendance_info 
			SET attendance_info.STime = STime 
			WHERE
				attendance_info.UID = UID 
				AND attendance_info.ADate = ADate;
			
		END IF;
END;


//查询基本工资的函数
DROP FUNCTION
IF
	EXISTS get_base_salary;
CREATE FUNCTION get_base_salary (
	UID CHAR ( 10 )) RETURNS INT BEGIN
	DECLARE
		ret INT;
	SELECT
		Base_salary 
	FROM
		employee_info,
		kind_info 
	WHERE
		employee_info.UID = UID 
		AND employee_info.KID = kind_info.KID INTO ret;
RETURN ret;
END;


//查询某个月份所有津贴的函数
DROP FUNCTION
IF
	EXISTS get_bonus_month;
CREATE FUNCTION get_bonus_month ( UID CHAR ( 10 ), whichmonth date ) RETURNS INT BEGIN
	DECLARE
		total_bonus INT;
	SELECT
		SUM( Bonus ) 
	FROM
		bonus_info 
	WHERE
		bonus_info.UID = UID 
		AND DATE_FORMAT( whichmonth, '%Y-%m' ) = DATE_FORMAT( bonus_info.BDate, '%Y-%m' ) INTO total_bonus;
	RETURN total_bonus;

END；

//插入数据到salary_info表的存储过程
DROP PROCEDURE
IF
	EXISTS calculate_salary_per_month;
CREATE PROCEDURE calculate_salary_per_month ( UID CHAR ( 10 ), whichmonth date ) BEGIN
	DECLARE
		Base_salary INT;
	DECLARE
		Bonus INT;
	DECLARE
		Total_salary INT;
	DECLARE
		attendance_times INT;
	DECLARE
		attendance_rate FLOAT;
	
	SET Base_salary = get_base_salary ( UID );
	
	SET Bonus = get_bonus_month ( UID, whichmonth );
	SELECT
		COUNT(*) INTO attendance_times 
	FROM
		attendance_info 
	WHERE
		attendance_info.UID = UID AND DATE_FORMAT( attendance_info.ADate, '%Y-%m' ) = DATE_FORMAT( whichmonth, '%Y-%m' ) 
		AND TIMESTAMPDIFF( HOUR, attendance_info.ATime, attendance_info.STime ) >= 8;
	
	SET attendance_rate = attendance_times / 22;
	
	SET Total_salary = Bonus + Base_salary * attendance_rate;
	DELETE 
	FROM
		salary_info 
	WHERE
		salary_info.UID = UID 
		AND DATE_FORMAT( salary_info.`Month`, '%Y-%m' ) = DATE_FORMAT( whichmonth, '%Y-%m' );
	INSERT INTO salary_info
	VALUES
	( UID, CONCAT( DATE_FORMAT( whichmonth, '%Y-%m' ), '-01' ),Base_salary, attendance_times, attendance_rate,  Bonus, Total_salary );
END


//当对津贴进行改动时重新计算并修改salary_info的触发器
DROP TRIGGER
IF
	EXISTS calculate_salary_per_month_when_insert_bonus;
CREATE TRIGGER calculate_salary_per_month_when_insert_bonus AFTER INSERT ON bonus_info FOR EACH ROW
BEGIN
		CALL calculate_salary_per_month ( NEW.UID, NEW.BDate );
	
END;
DROP TRIGGER
IF
	EXISTS calculate_salary_per_month_when_delete_bonus;
CREATE TRIGGER calculate_salary_per_month_when_delete_bonus AFTER DELETE ON bonus_info FOR EACH ROW
BEGIN
		CALL calculate_salary_per_month ( OLD.UID, OLD.BDate );
	
END;

DROP TRIGGER
IF
	EXISTS calculate_salary_per_month_when_update_bonus;
CREATE TRIGGER calculate_salary_per_month_when_update_bonus AFTER UPDATE ON bonus_info FOR EACH ROW
BEGIN
		CALL calculate_salary_per_month ( OLD.UID, OLD.BDate );
	IF
		OLD.BDate != NEW.BDate THEN
			CALL calculate_salary_per_month ( NEW.UID, OLD.BDate );
		
	END IF;
END;

//签退时更新当月的薪资情况
DROP TRIGGER
IF
	EXISTS get_salary_permonth_when_update_attendance;
CREATE TRIGGER get_salary_permonth_when_update_attendance AFTER UPDATE ON attendance_info FOR EACH ROW
BEGIN
	IF
		! isnull( NEW.STime ) THEN
			CALL calculate_salary_per_month ( NEW.UID, NEW.ADate );
		
	END IF;
END;


//获取员工基本信息的视图
DROP VIEW
IF
	EXISTS view_get_employee_info;
CREATE VIEW view_get_employee_info AS SELECT
UID, UName, Age, Sex, DName, KName, `Level`, Base_salary, kind_info.KID, department_info.DID 
FROM
	employee_info,
	department_info,
	kind_info 
WHERE
	employee_info.KID = kind_info.KID 
	AND employee_info.DID = department_info.DID;

//计算某个UID某年的总工资的函数
DROP FUNCTION
IF
	EXISTS get_salary_year;
CREATE FUNCTION get_salary_year (
	UID CHAR ( 10 ),
	whichyear CHAR ( 10 )) RETURNS INT BEGIN
	DECLARE
		total INT;
	SELECT
		SUM( salary_info.Total_salary ) 
	FROM
		salary_info 
	WHERE
		salary_info.UID = UID 
		AND DATE_FORMAT( salary_info.MONTH, '%Y' ) = whichyear INTO total;
	RETURN total;
	
END;

//计算某个UID某年的年终奖的函数
DROP FUNCTION
IF
	EXISTS get_year_end_awards_employee;
CREATE FUNCTION get_year_end_awards_employee (
	UID CHAR ( 10 ),
	whichyear CHAR ( 10 )) RETURNS INT BEGIN
		DECLARE
			ret INT;
		SET ret = get_salary_year(UID,whichyear) / 12;
		RETURN ret;
		
	END;
	


//获取年度报表视图
DROP VIEW
IF
	EXISTS view_get_salary_report;
CREATE VIEW view_get_salary_report AS 
SELECT
UID,
UName,
DName,
get_salary_year(UID, '2020') AS Salary,
get_year_end_awards_employee ( UID, '2020' ) AS Award
FROM
	employee_info,
	department_info
WHERE
	employee_info.DID = department_info.DID;
	
SELECT
	UID,UName,DName,Salary,Award,Salary+Award as Total
FROM
	view_get_salary_report;