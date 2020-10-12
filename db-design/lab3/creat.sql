/*
 Navicat Premium Data Transfer

 Source Server         : aliyun
 Source Server Type    : MySQL
 Source Server Version : 50730
 Source Host           : localhost:3306
 Source Schema         : test

 Target Server Type    : MySQL
 Target Server Version : 50730
 File Encoding         : 65001

 Date: 23/06/2020 23:30:24
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for attendance_info
-- ----------------------------
DROP TABLE IF EXISTS `attendance_info`;
CREATE TABLE `attendance_info`  (
  `UID` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ADate` date NOT NULL,
  `ATime` time(0) NULL DEFAULT NULL,
  `STime` time(0) NULL DEFAULT NULL,
  PRIMARY KEY (`UID`, `ADate`) USING BTREE,
  CONSTRAINT `attendance_info_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `employee_info` (`UID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for bonus_info
-- ----------------------------
DROP TABLE IF EXISTS `bonus_info`;
CREATE TABLE `bonus_info`  (
  `UID` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `BDate` date NOT NULL,
  `BType` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `BDays` smallint(6) NULL DEFAULT NULL,
  `Bonus` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`UID`, `BDate`, `BType`) USING BTREE,
  CONSTRAINT `bonus_info_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `employee_info` (`UID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for department_info
-- ----------------------------
DROP TABLE IF EXISTS `department_info`;
CREATE TABLE `department_info`  (
  `DID` smallint(6) NOT NULL,
  `DName` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `DRef` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `Dnum` smallint(6) NULL DEFAULT NULL,
  PRIMARY KEY (`DID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for employee_info
-- ----------------------------
DROP TABLE IF EXISTS `employee_info`;
CREATE TABLE `employee_info`  (
  `UID` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `UName` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `Age` smallint(6) NULL DEFAULT NULL,
  `Sex` tinyint(1) NULL DEFAULT NULL,
  `KID` smallint(6) NULL DEFAULT NULL,
  `DID` smallint(6) NULL DEFAULT NULL,
  PRIMARY KEY (`UID`) USING BTREE,
  INDEX `KID`(`KID`) USING BTREE,
  INDEX `DID`(`DID`) USING BTREE,
  CONSTRAINT `employee_info_ibfk_1` FOREIGN KEY (`KID`) REFERENCES `kind_info` (`KID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `employee_info_ibfk_2` FOREIGN KEY (`DID`) REFERENCES `department_info` (`DID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for kind_info
-- ----------------------------
DROP TABLE IF EXISTS `kind_info`;
CREATE TABLE `kind_info`  (
  `KID` smallint(6) NOT NULL,
  `KName` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `Level` smallint(6) NULL DEFAULT NULL,
  `Base_salary` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`KID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for log_info
-- ----------------------------
DROP TABLE IF EXISTS `log_info`;
CREATE TABLE `log_info`  (
  `UID` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Password` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `Authority` smallint(6) NULL DEFAULT NULL,
  PRIMARY KEY (`UID`) USING BTREE,
  CONSTRAINT `log_info_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `employee_info` (`UID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for salary_info
-- ----------------------------
DROP TABLE IF EXISTS `salary_info`;
CREATE TABLE `salary_info`  (
  `UID` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Month` date NOT NULL,
  `Base_salary` int(11) NULL DEFAULT NULL,
  `attendance_times` smallint(6) NULL DEFAULT NULL,
  `attendance_rate` float NULL DEFAULT NULL,
  `Bonus` int(11) NULL DEFAULT NULL,
  `Total_salary` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`UID`, `Month`) USING BTREE,
  CONSTRAINT `salary_info_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `employee_info` (`UID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- View structure for view_get_employee_info
-- ----------------------------
DROP VIEW IF EXISTS `view_get_employee_info`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `view_get_employee_info` AS select `employee_info`.`UID` AS `UID`,`employee_info`.`UName` AS `UName`,`employee_info`.`Age` AS `Age`,`employee_info`.`Sex` AS `Sex`,`department_info`.`DName` AS `DName`,`kind_info`.`KName` AS `KName`,`kind_info`.`Level` AS `Level`,`kind_info`.`Base_salary` AS `Base_salary`,`kind_info`.`KID` AS `KID`,`department_info`.`DID` AS `DID` from ((`employee_info` join `department_info`) join `kind_info`) where ((`employee_info`.`KID` = `kind_info`.`KID`) and (`employee_info`.`DID` = `department_info`.`DID`));

-- ----------------------------
-- View structure for view_get_salary_report
-- ----------------------------
DROP VIEW IF EXISTS `view_get_salary_report`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `view_get_salary_report` AS select `employee_info`.`UID` AS `UID`,`employee_info`.`UName` AS `UName`,`department_info`.`DName` AS `DName`,`get_salary_year`(`employee_info`.`UID`,'2020') AS `Salary`,`get_year_end_awards_employee`(`employee_info`.`UID`,'2020') AS `Award` from (`employee_info` join `department_info`) where (`employee_info`.`DID` = `department_info`.`DID`);

-- ----------------------------
-- Procedure structure for attendance_update
-- ----------------------------
DROP PROCEDURE IF EXISTS `attendance_update`;
delimiter ;;
CREATE PROCEDURE `attendance_update`(UID CHAR ( 10 ), ADate date, ATime time, STime time, type INT)
BEGIN
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
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for calculate_salary_per_month
-- ----------------------------
DROP PROCEDURE IF EXISTS `calculate_salary_per_month`;
delimiter ;;
CREATE PROCEDURE `calculate_salary_per_month`(UID CHAR ( 10 ), whichmonth date)
BEGIN
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
		attendance_info.UID = UID AND	DATE_FORMAT( attendance_info.ADate, '%Y-%m' ) = DATE_FORMAT( whichmonth, '%Y-%m' ) 
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
;;
delimiter ;

-- ----------------------------
-- Function structure for get_base_salary
-- ----------------------------
DROP FUNCTION IF EXISTS `get_base_salary`;
delimiter ;;
CREATE FUNCTION `get_base_salary`(UID CHAR ( 10 ))
 RETURNS int(11)
BEGIN
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
END
;;
delimiter ;

-- ----------------------------
-- Function structure for get_bonus_month
-- ----------------------------
DROP FUNCTION IF EXISTS `get_bonus_month`;
delimiter ;;
CREATE FUNCTION `get_bonus_month`(UID CHAR ( 10 ), whichmonth date)
 RETURNS int(11)
BEGIN
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

END
;;
delimiter ;

-- ----------------------------
-- Function structure for get_salary_year
-- ----------------------------
DROP FUNCTION IF EXISTS `get_salary_year`;
delimiter ;;
CREATE FUNCTION `get_salary_year`(UID CHAR ( 10 ),
	whichyear CHAR ( 10 ))
 RETURNS int(11)
BEGIN
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
END
;;
delimiter ;

-- ----------------------------
-- Function structure for get_year_end_awards_employee
-- ----------------------------
DROP FUNCTION IF EXISTS `get_year_end_awards_employee`;
delimiter ;;
CREATE FUNCTION `get_year_end_awards_employee`(UID CHAR ( 10 ),
	whichyear CHAR ( 10 ))
 RETURNS int(11)
BEGIN
		DECLARE
			ret INT;
		SET ret = get_salary_year(UID,whichyear) / 12;
		RETURN ret;
		
	END
;;
delimiter ;

-- ----------------------------
-- Function structure for plus
-- ----------------------------
DROP FUNCTION IF EXISTS `plus`;
delimiter ;;
CREATE FUNCTION `plus`(arg1 INT, arg2 INT)
 RETURNS int(11)
BEGIN
	DECLARE
		total INT;
	
	SET total = arg1 + arg2;
RETURN total;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table attendance_info
-- ----------------------------
DROP TRIGGER IF EXISTS `get_salary_permonth_when_update_attendance`;
delimiter ;;
CREATE TRIGGER `get_salary_permonth_when_update_attendance` AFTER UPDATE ON `attendance_info` FOR EACH ROW BEGIN
	IF
		! isnull( NEW.STime ) THEN
			CALL calculate_salary_per_month ( NEW.UID, NEW.ADate );
		
	END IF;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table bonus_info
-- ----------------------------
DROP TRIGGER IF EXISTS `calculate_salary_per_month_when_insert_bonus`;
delimiter ;;
CREATE TRIGGER `calculate_salary_per_month_when_insert_bonus` AFTER INSERT ON `bonus_info` FOR EACH ROW BEGIN
		CALL calculate_salary_per_month ( NEW.UID, NEW.BDate );
	
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table bonus_info
-- ----------------------------
DROP TRIGGER IF EXISTS `calculate_salary_per_month_when_update_bonus`;
delimiter ;;
CREATE TRIGGER `calculate_salary_per_month_when_update_bonus` AFTER UPDATE ON `bonus_info` FOR EACH ROW BEGIN
		CALL calculate_salary_per_month ( OLD.UID, OLD.BDate );
	IF
		OLD.BDate != NEW.BDate THEN
			CALL calculate_salary_per_month ( NEW.UID, OLD.BDate );
		
	END IF;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table bonus_info
-- ----------------------------
DROP TRIGGER IF EXISTS `calculate_salary_per_month_when_delete_bonus`;
delimiter ;;
CREATE TRIGGER `calculate_salary_per_month_when_delete_bonus` AFTER DELETE ON `bonus_info` FOR EACH ROW BEGIN
		CALL calculate_salary_per_month ( OLD.UID, OLD.BDate );
	
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table employee_info
-- ----------------------------
DROP TRIGGER IF EXISTS `add_new_log`;
delimiter ;;
CREATE TRIGGER `add_new_log` AFTER INSERT ON `employee_info` FOR EACH ROW BEGIN
		INSERT INTO log_info
	VALUES
	( new.UID, new.UID, 1 );
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table employee_info
-- ----------------------------
DROP TRIGGER IF EXISTS `department_people_num_plus`;
delimiter ;;
CREATE TRIGGER `department_people_num_plus` AFTER INSERT ON `employee_info` FOR EACH ROW BEGIN
		UPDATE department_info 
		SET Dnum = IFNULL( Dnum, 0 )+ 1 
	WHERE
	DID = new.DID;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table employee_info
-- ----------------------------
DROP TRIGGER IF EXISTS `department_people_num_update`;
delimiter ;;
CREATE TRIGGER `department_people_num_update` AFTER UPDATE ON `employee_info` FOR EACH ROW BEGIN
	IF
		( old.DID != new.DID ) THEN
			UPDATE department_info 
			SET Dnum = Dnum + 1 
		WHERE
			DID = new.DID;
		UPDATE department_info 
		SET Dnum = Dnum - 1 
		WHERE
			DID = old.DID;
		
	END IF;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table employee_info
-- ----------------------------
DROP TRIGGER IF EXISTS `del_old_log`;
delimiter ;;
CREATE TRIGGER `del_old_log` BEFORE DELETE ON `employee_info` FOR EACH ROW BEGIN
	DELETE FROM log_info where log_info.UID=OLD.UID;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table employee_info
-- ----------------------------
DROP TRIGGER IF EXISTS `department_people_num_minus`;
delimiter ;;
CREATE TRIGGER `department_people_num_minus` AFTER DELETE ON `employee_info` FOR EACH ROW BEGIN
		UPDATE department_info 
		SET Dnum = Dnum - 1 
	WHERE
	DID = old.DID;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
