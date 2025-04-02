DROP TABLE PlayerNemesis;
DROP TABLE CarParticipatesRace;
DROP TABLE CarAttachedSticker;
DROP TABLE Sticker;
DROP TABLE Race;
DROP TABLE Tournament;
DROP TABLE Car;
DROP TABLE Player;

CREATE TABLE Player (
	player_id INTEGER NOT NULL,
	nickname VARCHAR(255) NOT NULL,
	elo_score INTEGER NOT NULL,
	credits DECIMAL(10,2) NOT NULL,
	PRIMARY KEY (player_id)
);
CREATE TABLE Car (
	car_name VARCHAR2(255) NOT NULL,
	player_id INTEGER NOT NULL,
	brand VARCHAR2(60) NOT NULL,
	model VARCHAR2(30) NOT NULL,
	clas VARCHAR2(15) NOT NULL,
	price INTEGER NOT NULL,
	color VARCHAR2(15) NOT NULL,
	PRIMARY KEY (player_id,car_name),
	CONSTRAINT fk_player_id FOREIGN KEY (player_id) REFERENCES Player(player_id)
);
CREATE TABLE Tournament(
	tournament_id INTEGER NOT NULL,
	sizes INTEGER NOT NULL,
	winner INTEGER NOT NULL,
	PRIMARY KEY(tournament_id),
	CONSTRAINT fk_winner FOREIGN KEY (winner) REFERENCES Player(player_id)
);
CREATE TABLE Race (
	race_id INTEGER NOT NULL,
	laps INTEGER NOT NULL,
	maps VARCHAR2(255) NOT NULL,
	weather VARCHAR2(60) NOT NULL,
	tournament_id INTEGER NOT NULL,
	PRIMARY KEY (race_id),
	CONSTRAINT fk_tournament_id FOREIGN KEY (tournament_id) REFERENCES Tournament(tournament_id)
);
CREATE TABLE Sticker (
	cosmatic_id INTEGER NOT NULL,
	rarity VARCHAR2(30) NOT NULL,
	price DECIMAL(8,2) NOT NULL,
	wear_float DECIMAL(12,9) NOT NULL,
	PRIMARY KEY(cosmatic_id)
);
CREATE TABLE CarAttachedSticker (
	player_id INTEGER NOT NULL,
	car_name VARCHAR2(255) NOT NULL,
	cosmatic_id INTEGER NOT NULL,
	PRIMARY KEY (player_id,car_name,cosmatic_id),
	CONSTRAINT fk_car_name FOREIGN KEY (car_name,player_id) REFERENCES Car (car_name,player_id),
	CONSTRAINT fk_cosmatic_id FOREIGN KEY (cosmatic_id) REFERENCES Sticker(cosmatic_id)
);
CREATE TABLE CarParticipatesRace (
	race_id INTEGER NOT NULL,
	player_id INTEGER NOT NULL,
	car_name VARCHAR2(255) NOT NULL,
	duration DECIMAL(3,2) NOT NULL,
	position INTEGER NOT NULL,
	PRIMARY KEY (race_id,player_id,car_name),
	CONSTRAINT fk_race_id FOREIGN KEY (race_id) REFERENCES Race (race_id),
	CONSTRAINT fk_car_name2 FOREIGN KEY (car_name,player_id) REFERENCES Car (car_name,player_id)
);
CREATE TABLE PlayerNemesis (
	player1 INTEGER NOT NULL,
	player2 INTEGER NOT NULL,
	dates DATE NOT NULL,
	PRIMARY KEY (player1,player2),
	CONSTRAINT fk_player1 FOREIGN KEY (player1) REFERENCES Player(player_id),
	CONSTRAINT fk_player2 FOREIGN KEY (player2) REFERENCES Player(player_id)
);

INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(2981,'snakeserdar',1321,630.08);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(1351,'TylerDurden',1169,18594.54);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(5252,'kharphaz',959,6326.47);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(3459,'LadyDeath',803,7742.57);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(2424,'DominicToretto',1520,9910.53);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(3153,'SametBaba',1046,2420.29);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(7045,'xKralTR',1091,17009.64);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(4019,'yesilady',1167,11174.42);
INSERT INTO Player(player_id,nickname,elo_score,credits) VALUES(2147,'Sp33d4dd1ct',1428,3704.63);

INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('lokmata',2981,'Anadol','A5','Daily',1024,'White');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('SoapMachine',1351,'Chevrolet','Camaro','Super',3018,'Graphite');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('doNotT4lk',1351,'Suzuki','Swift RS','Daily',6812,'Green');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('McQueen',5252,'Chevrolet','Corvette','Super',9999,'Red');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('scubaRacer',5252,'BMW','X1','Daily',6000,'Red');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('McQueen',3459,'Subaru','BRZ','Super',5498,'Red');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('FamilyFirst',2424,'Dodge','Charger','Muscle',7131,'Black');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('kolpha',3153,'Tesla','Roadster','Electric',6811,'Blue');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('bootlegC5',3153,'Honda','SNX','Super',2141,'Orange');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('DocHudson',3153,'Hudson','Hornet','Muscle',1841,'Blue');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('Kha-Rhambhol',7045,'Audi','R8','Super',3421,'White');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('Cardinality',4019,'Mazda','Miata','Super',1245,'Violet');
INSERT INTO Car(car_name,player_id,brand,model,clas,price,color) VALUES('GottaGoF4st',2147,'Bugatti','Tourbillon','Super',9999,'Cyan');

INSERT INTO Tournament(tournament_id,sizes,winner) VALUES(101,5,2981);
INSERT INTO Tournament(tournament_id,sizes,winner) VALUES(102,5,1351);
INSERT INTO Tournament(tournament_id,sizes,winner) VALUES(103,6,5252);
INSERT INTO Tournament(tournament_id,sizes,winner) VALUES(104,6,2424);
INSERT INTO Tournament(tournament_id,sizes,winner) VALUES(105,7,2424);


INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(848,2,'Monaco Circuit ','Rainy',101);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(573,2,'Tokyo Driftways ','Sunny',101);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(681,3,'Death Valley Run ','Sunny',102);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(431,2,'Sahara Speedway','Cloudy',103);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(216,1,'Alpine Ascent','Rainy',103);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(106,3,'Rio Rally','Night',103);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(880,3,'Mount Fuji Sprint','Sunny',104);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(986,2,'Outback Trail','Cloudy',104);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(482,3,'Istanbul Interchange','Sunny',105);
INSERT INTO Race(race_id,laps,maps,weather,tournament_id) VALUES(526,3,'Arctic Edge','Night',105);


INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(848,1351,'SoapMachine',4.14,2);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(848,7045,'Kha-Rhambhol',5.14,4);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(573,2981,'lokmata',4.32,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(681,4019,'Cardinality',4.27,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(431,2147,'GottaGoF4st',5.13,8);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(431,2424,'FamilyFirst',4.12,2);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(482,5252,'scubaRacer',5.3,4);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(482,3153,'DocHudson',5.01,3);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(482,1351,'doNotT4lk',4.57,2);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(482,2981,'lokmata',4.56,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(526,3459,'McQueen',3.58,7);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(526,1351,'SoapMachine',3.12,3);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(526,2424,'FamilyFirst',0.55,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(216,2981,'lokmata',5.31,5);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(216,3153,'kolpha',5.18,3);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(216,5252,'McQueen',4.57,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(106,3459,'McQueen',4.49,3);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(106,3153,'kolpha',4.38,1);
INSERT INTO CarParticipatesRace(race_id,player_id,car_name,duration,position) VALUES(106,4019,'Cardinality',4.47,2);


INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(20218,'Common',436.67,0.85250753);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(80448,'Common',826.36,0.99902498);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(12151,'Uncommon',818.40,0.60649828);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(14300,'Rare',866.07,0.59703003);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(83906,'Common',760.82,0.52035604);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(45878,'Rare',784.19,0.72414567);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(97072,'Rare',721.08,0.44387873);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(95143,'Rare',444.91,0.55397895);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(61006,'Uncommon',148.57,0.45067458);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(86428,'Common',472.52,0.88365737);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(49205,'Uncommon',251.37,0.91284671);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(48190,'Common',316.38,0.99185678);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(56980,'Common',848.79,0.47302672);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(59143,'Uncommon',617.99,0.57720924);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(71338,'Rare',762.87,0.56155572);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(31263,'Common',483.62,0.57990074);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(56897,'Common',436.88,0.89199914);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(31393,'Uncommon',561.36,0.43543028);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(42844,'Common',249.94,0.70574814);
INSERT INTO Sticker(cosmatic_id,rarity,price,wear_float) VALUES(87014,'Common',530.33,0.60695136);

INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(2981,'lokmata',20218);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(1351,'doNotT4lk',12151);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(5252,'McQueen',14300);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(2424,'FamilyFirst',83906);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(3153,'bootlegC5',45878);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(7045,'Kha-Rhambhol',97072);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(2147,'GottaGoF4st',61006);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(2424,'FamilyFirst',71338);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(1351,'SoapMachine',49205);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(4019,'Cardinality',48190);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(5252,'scubaRacer',56980);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(3459,'McQueen',59143);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(3153,'kolpha',71338);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(3153,'DocHudson',31263);
INSERT INTO CarAttachedSticker(player_id,car_name,cosmatic_id) VALUES(2147,'GottaGoF4st',56897);




INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(2981,3153,TO_DATE('2025-05-09', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(1351,2981,TO_DATE('2025-01-10', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(1351,7045,TO_DATE('2025-03-20', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(7045,3153,TO_DATE('2025-03-06', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(3459,7045,TO_DATE('2025-03-29', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(5252,3153,TO_DATE('2025-09-24', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(2424,4019,TO_DATE('2024-12-26', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(5252,1351,TO_DATE('2024-12-14', 'YYYY-MM-DD'));
INSERT INTO PlayerNemesis(player1,player2,dates) VALUES(2147,1351,TO_DATE('2025-01-14', 'YYYY-MM-DD'));

