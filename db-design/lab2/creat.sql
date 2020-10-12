create table Station(
	SID int primary key,
	SName char(20) not null,
	CityName char(30)
	);
				
create table Train(
	TID int primary key,
	SDate date not null,
	TName char(20) not null,
	SStationID int ,
	AStationID int ,
	Stime datetime ,
	ATime datetime ,
	foreign key(SStationID) references Station(SID),
	foreign key(AStationID) references Station(SID),
	unique(SDate,TName)
	);


create table TrainPass(
	TID int not null,
	SNo smallint not null,
	SID int ,
	STime datetime ,
	ATime datetime ,
	primary key(TID,SNo),
	foreign key(SID) references Station(SID),
	foreign key(TID) references Train(TID)
	);

create table Passenger(
	PCardID char(18) not null primary key,
	PName char(20),
	Sex bit,
	Age smallint
);
	
create table TakeTrainRecord(
	RID int not null primary key,
	PCardID char(18) , 
	TID int,
	-- SDate date,
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

create table DiagnoseRecord(
	DID int not null primary key,
	PCardID char(18),
	DDay date,
	DStatus smallint check(DStatus between 1 and 3),
	FDay date,
	foreign key(PCardID) references Passenger(PCardID)
	);

create table Traincontactor(
	CDate date,
	CCardID char(18) references Passenger(PCardID),
	DStatus smallint not null check(DStatus between 1 and 3),
	PCardID char(18) not null,
	primary key(CDate,CCardID,DStatus,PCardID),
	foreign key(CCardID) references Passenger(PCardID),
	foreign key(PCardID) references Passenger(PCardID)
	)