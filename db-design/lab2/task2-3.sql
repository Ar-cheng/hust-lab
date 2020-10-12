-- 1）查询确诊者“安娜”的在发病前14天内的乘车记录； 
select * from TakeTrainRecord 
	where PCardID in(
		select taketrainrecord.PCardID
		from taketrainrecord, diagnoserecord, passenger,train
		where taketrainrecord.PCardID = diagnoserecord.PCardID 
		and taketrainrecord.PCardID = passenger.PCardID
		and taketrainrecord.TID = train.TID
		and Pname = '安娜' 
		and DStatus = 1 
		and datediff(FDay,SDate) BETWEEN 0 AND 14 );

-- 2）查询所有从城市“武汉”出发的乘客乘列车所到达的城市名； 
select DISTINCT CityName from Station
	where SID in(
		select AStationID
		from Train left join Station on Train.SStationID = Station.SID
		where Station.CityName = '武汉');

-- 3）计算每位新冠患者从发病到确诊的时间间隔（天数）及患者身份信息，并将结果按照发病时间天数的降序排列；
select * from(
	select PCardID , datediff(DDay,FDay) as day_interval from DiagnoseRecord 
	where DStatus = 1 order by day_interval desc) as a
	natural join Passenger;
 

-- 4）查询“2020-01-22”从“武汉”发出的所有列车；
select * from Train
	where SStationID in (select SID from Station where CityName = '武汉')
		and SDate = '2020-01-22';


-- 5）查询“2020-01-22”途经“武汉”的所有列车；
select * from train
	whee TID in (
		select trainpass.TID from trainpass , train
		where trainpass.TID = train.TID 
		and SDate = '2020-1-22' and SID in (select SID from Station where CityName = '武汉') );

SELECT *
FROM TRAIN 
WHERE TID IN(
    SELECT TID 
    FROM TRAINPASS,STATION 
    WHERE STIME LIKE '2020-01-22%'
    AND TRAINPASS.SID=STATION.SID
    AND STATION.CityName='武汉'
);


-- 6）查询“2020-01-22”从武汉离开的所有乘客的身份证号、所到达的城市、到达日期； 
select PCardID,CityName,convert(STime,DATE) from taketrainrecord,station,trainpass
	where SStationID in (select SID from station where CityName = '武汉')
	and taketrainrecord.TID = trainpass.TID
	and taketrainrecord.AStationID = trainpass.SID
	and taketrainrecord.AStationID = station.SID
	and convert(STime,DATE) = '2020-01-22';


-- 7）统计“2020-01-22” 从武汉离开的所有乘客所到达的城市及达到各个城市的武汉人员数。
select CityName,count(CityName) from taketrainrecord,station,trainpass
	where SStationID in (select SID from station where CityName = '武汉')
	and taketrainrecord.TID = trainpass.TID
	and taketrainrecord.AStationID = trainpass.SID
	and taketrainrecord.AStationID = station.SID
	and convert(STime,DATE) = '2020-01-22'
	GROUP BY CityName

-- 8）查询2020年1月到达武汉的所有人员；
select * from
	(select PCardID
	from taketrainrecord, trainpass
	where taketrainrecord.AStationID in (select SID from station where CityName = '武汉')
	and taketrainrecord.TID = trainpass.TID
	and taketrainrecord.AStationID = trainpass.SID
	and	trainpass.STime like '2020-01%') as a
natural join passenger

-- 9）查询2020年1月乘车途径武汉的外地人员（身份证非“420”开头）；
select *  from
	(select PCardID
	from TakeTrainRecord,TrainPass
	where TrainPass.SID in (select SID from Station where CityName = '武汉')
	and TrainPass.TID= TakeTrainRecord.TID
	and TakeTrainRecord.SStatus = 1
	and TrainPass.STime like '2020-01%')
natural join Passenger
where not PCardID like '420%';

-- 考虑序号问题
select distinct
	passenger.* 
from
	trainpass t,
	taketrainrecord,
	passenger
where
	t.SID in ( select SID from station where CITYNAME = '武汉' )
	and t.TID = TakeTrainRecord.TID 
	and t.SNo <= ( select SNO from trainpass where taketrainrecord.ASTATIONID = trainpass.SID and taketrainrecord.TID = trainpass.TID ) 
	and t.SNo >= ( select SNO from trainpass where taketrainrecord.SSTATIONID = trainpass.SID and taketrainrecord.TID = trainpass.TID ) 
	and TakeTrainRecord.SSTATUS = 1 
	and t.STime like '2020-01%' 
	and passenger.PCardID = taketrainrecord.PCardID 
	and not passenger.PCardID like '420%';
	
-- 10）统计“2020-01-22”乘坐过‘G1007’号列车的新冠患者在火车上的密切接触乘客人数（每位新冠患者的同车厢人员都算同车密切接触）。
select diagnoserecord.PCardID,count(diagnoserecord.PCardID) as contactor_count
	from diagnoserecord, taketrainrecord t1, taketrainrecord t2 
	where diagnoserecord.PCardID = t1.PCardID
	and t1.PCardID <> t2.PCardID 
	and t1.TID = t2.TID
	and t1.CarrigeID = t2.CarrigeID
	and t1.TID in (select TID from train where SDate = '2020-01-22' and TName = 'G1007')
	group by diagnoserecord.PCardID;

-- 11）查询一趟列车的一节车厢中有3人及以上乘客被确认患上新冠的列车名、出发日期，车厢号； 
select TName, SDate, CarrigeID 
	from TakeTrainRecord, DiagnoseRecord, train 
	where DStatus = 1 
	and taketrainrecord.PCardID = diagnoserecord.PCardID
	and taketrainrecord.TID = train.TID
	group by TName,SDate,CarrigeID 
	having count(*) >= 3;


-- 12）查询没有感染任何周边乘客的新冠乘客的身份证号、姓名、乘车日期； 
select a1.PCardID,passenger.PName,train.SDate from
(select diagnoserecord.PCardID,COUNT(diagnoserecord.PCardID) as num
	from diagnoserecord, taketrainrecord t1, taketrainrecord t2 
	where diagnoserecord.PCardID = t1.PCardID
	and t1.TID = t2.TID
	and t1.PCardID <> t2.PCardID
	and t1.CarrigeID = t2.CarrigeID
group by diagnoserecord.PCardID ) as a1,
(select diagnoserecord.PCardID,COUNT(diagnoserecord.PCardID) as num
	from diagnoserecord, taketrainrecord t1, taketrainrecord t2 
	where diagnoserecord.PCardID = t1.PCardID
	and t1.TID = t2.TID
	and t1.PCardID <> t2.PCardID
	and t1.CarrigeID = t2.CarrigeID
	and t2.PCardID not in (select PCardID from diagnoserecord)
group by diagnoserecord.PCardID ) as a2 , taketrainrecord , passenger , train
where a1.PCardID = a2.PCardID
and a1.num = a2.num
and a1.PCardID = taketrainrecord.PCardID
and a1.PCardID = passenger.PCardID
and train.TID = taketrainrecord.TID

-- 13）查询到达 “北京”、或“上海”，或“广州”（即终点站）的列车名，要求where子句中除了连接条件只能有一个条件表达式；
select TName from  
Train  join Station on Train.AStationID = Station.SID 
where  CityName in ('北京','上海','广州');

-- 14）查询“2020-01-22”从“武汉站”出发，然后当天换乘另一趟车的乘客身份证号和首乘车次号，结果按照首乘车次号降序排列，同车次则按照乘客身份证号升序排列；
select PCardID,TName from
	(select *
	from taketrainrecord 
	where SStationID in (select SID from station where CityName = '武汉'))as t1
	join taketrainrecord t2 using(PCardID) join train on t1.TID = train.TID
	where t1.TID <> t2.TID
	and t1.TID in (select DISTINCT TID from trainpass where convert(atime,DATE) = '2020-01-22')
	order by TName desc, PCardID;

-- 15）查询所有新冠患者的身份证号，姓名及其2020年以来所乘坐过的列车名、发车日期，要求即使该患者未乘坐过任何列车也要列出来；
select diagnoserecord.PCardID,PName,TName,SDate
	from diagnoserecord natural left outer join
		(select PCardID,TName,SDate
		from taketrainrecord, train 
		where taketrainrecord.TID = train.TID
		) as a natural join passenger 
	where SDate like '2020%' or SDate is null;

-- 16）查询所有发病日期相同而且确诊日期相同的病患统计信息，包括：发病日期、确诊日期和患者人数，结果按照发病日期降序排列的前提下再按照确诊日期降序排列。
select FDay, DDay, count(*)as ill_num from DiagnoseRecord 
where DStatus = 1
group by DDay,FDay 
order by FDay desc, DDay desc;