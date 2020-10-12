-- train表生成
INSERT INTO train SELECT
TID,
@date := DATE_ADD( "2020-01-01", INTERVAL FLOOR( rand()* 30 ) DAY ) AS SDate,
TName,
s1.SID AS SStationID,
s2.SID AS AStationID,
CONCAT( @date, ' ', STime ) AS STime,
CONCAT( @date, ' ', ATime ) AS ATime 
FROM
	train_temp,
	station s1,
	station s2 
WHERE
	SStationName = s1.SName 
	AND AStationName = s2.SName 
ORDER BY
	TID;

-- trainpass表生成
INSERT INTO trainpass SELECT
TID,
SNo,
SID,
CONCAT( SDate, ' ', trainpass_temp.STime ) AS STime,
CONCAT( SDate, ' ', trainpass_temp.ATime ) AS ATime 
FROM
	trainpass_temp,
	train,
	station 
WHERE
	trainpass_temp.TName = train.TName 
	AND trainpass_temp.SName = station.SName 
ORDER BY
	TID,
	SNo;

-- WH_TakeTrainRecord表生成
create table WH_TakeTrainRecord(
	RID int not null primary key,
	PCardID char(18) , 
	TID int,
	SStationID int ,
	AStationID int ,
	CarrigeID smallint, 
	SeatRow smallint,
	SeatNo char(1) check(SeatNo='A' or SeatNo='B' or SeatNo='C' or SeatNo='D' or SeatNo='E' or SeatNo is null),
	SStatus int check(SStatus between 0 and 2),
	foreign key(PCardID) references Passenger(PCardID),
	foreign key(TID) references Train(TID),
	foreign key(SStationID) references Station(SID),
	foreign key(AStationID) references Station(SID)
	);
	
insert into WH_TakeTrainRecord
SELECT * from taketrainrecord
where SStationID in (SELECT SID FROM station WHERE CityName = '武汉')

