INSERT INTO train.train
VALUES
	( 1, '2020-5-1', 'exp1', '100', '10', '2020-5-1 01:53:55', '2020-5-1 11:53:55' ),
	( 2, '2020-5-2', 'exp2', '200', '20', '2020-5-2 02:53:55', '2020-5-2 12:53:55' ),
	( 3, '2020-5-3', 'exp3', '300', '30', '2020-5-3 03:53:55', '2020-5-3 13:53:55' ),
	( 4, '2020-5-4', 'exp4', '400', '40', '2020-5-4 04:53:55', '2020-5-4 14:53:55' ),
	( 5, '2020-5-5', 'exp5', '500', '50', '2020-5-5 05:53:55', '2020-5-5 15:53:55' );


DELETE FROM train.train WHERE TID = 5;

UPDATE train.train set SStationID = 1000 WHERE TID = 4;



CREATE TABLE R(
	A int,
	B int);


INSERT INTO train.R
VALUES
	( 1, 2 ),
	( 1, 2 ),
	( 1, 2 );


-- 视图生成
create view diagnoserecord_info as
select diagnoserecord.PCardID,passenger.PName,passenger.Age,train.TName, train.SDate, taketrainrecord.CarrigeID,taketrainrecord.SeatRow,taketrainrecord.SeatNo
from diagnoserecord,passenger,taketrainrecord,train
where diagnoserecord.PCardID = passenger.PCardID
and diagnoserecord.PCardID = taketrainrecord.PCardID
and taketrainrecord.TID = train.TID;


-- 触发器
-- 1) 当新增一个确诊患者时，若该患者在发病前14天内有乘车记录，则将其同排及前后排乘客自动加入“乘客紧密接触者表”，其中：接触日期为乘车日期。
-- 2) 当一个紧密接触者被确诊为新冠时，从“乘客紧密接触者表”中修改他的状态为“1”。
--
CREATE TRIGGER trigger_add_diagnose AFTER INSERT ON diagnoserecord FOR EACH ROW
BEGIN
	IF
		(
			new.DStatus = 1 
			AND new.PCardID IN (
			SELECT
				taketrainrecord.PCardID 
			FROM
				taketrainrecord,
				train 
			WHERE
				taketrainrecord.PCardID = new.PCardID 
				AND taketrainrecord.TID = train.TID 
				AND taketrainrecord.SStatus = 1 
				AND datediff( new.FDay, train.SDate ) BETWEEN 0 
				AND 14 
			) 
			) THEN
			INSERT IGNORE INTO traincontactor SELECT
			train.SDate AS CDate,
			t2.PCardID AS CCardID,
			2 AS DStatus,
			new.PCardID AS PCardID 
		FROM
			train,
			taketrainrecord t1,
			taketrainrecord t2 
		WHERE
			new.PCardID = t1.PCardID 
			AND t1.TID = train.TID 
			AND t1.sstatus = 1 
			AND datediff( new.FDay, train.SDate ) BETWEEN 0 
			AND 14 
			AND t1.TID = t2.TID 
			AND t1.CarrigeID = t2.CarrigeID 
			AND new.PCardID <> t2.PCardID 
			AND abs( t1.SeatRow - t2.SeatRow )<= 1 
			AND t2.sstatus = 1;	
	END IF;
END


CREATE TRIGGER trigger_update_diagnose AFTER UPDATE ON diagnoserecord FOR EACH ROW
BEGIN
	IF
		new.DStatus = 1 THEN
			UPDATE traincontactor 
			SET DStatus = 1 
		WHERE
			CCardID = new.PCardID;
		END IF;
END