if exists (select * from sysobjects where id = object_id('dbo.ZZT521_COLOR') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT521_COLOR
GO

/****** Object:  Table dbo.ZZT021_COLOR   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT021_COLOR') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT021_COLOR
GO

/****** Object:  Table dbo.ZZT524_ROUND   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT524_ROUND') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT524_ROUND
GO

/****** Object:  Table dbo.ZZT024_ROUND   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT024_ROUND') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT024_ROUND
GO

/****** Object:  Table dbo.ZZT522_MODALITY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT522_MODALITY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT522_MODALITY
GO

/****** Object:  Table dbo.ZZT022_MODALITY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT022_MODALITY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT022_MODALITY
GO

/****** Object:  Table dbo.ZZT025_UNIFORM   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT025_UNIFORM') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT025_UNIFORM
GO

/****** Object:  Table dbo.ZZT530_OVERALL_DESCRIPTION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT530_OVERALL_DESCRIPTION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT530_OVERALL_DESCRIPTION
GO

/****** Object:  Table dbo.ZZT044_ECRELATION	******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT044_ECRELATION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT044_ECRELATION
GO

/****** Object:  Table dbo.ZZT043_ECSTATISTIC	******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT043_ECSTATISTIC') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT043_ECSTATISTIC
GO

/****** Object:  Table dbo.ZZT042_ECEVENT	******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT042_ECEVENT') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT042_ECEVENT
GO

/****** Object:  Table dbo.ZZT041_ECPLAYDATA	******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT041_ECPLAYDATA') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT041_ECPLAYDATA
GO

/****** Object:  Table dbo.ZZT040_ECPLAY	******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT040_ECPLAY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT040_ECPLAY
GO

/****** Object:  Table dbo.ZZT037_STATISTIC   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT037_STATISTIC') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT037_STATISTIC
GO


/****** Object:  Table dbo.ZZT022_MODALITY    ******/
CREATE TABLE dbo.ZZT022_MODALITY (
	MODALITY smallint NOT NULL 
	CONSTRAINT PK_ZZT022_MODALITY PRIMARY KEY  CLUSTERED 
	(
		MODALITY
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT522_MODALITY     ******/
CREATE TABLE dbo.ZZT522_MODALITY (
	MODALITY smallint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT522_MODALITY_LDES DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT522_MODALITY_SDES DEFAULT (null),
	CONSTRAINT PK_ZZT522_MODALITY PRIMARY KEY  CLUSTERED 
	(
		MODALITY,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT021_COLOR    ******/
CREATE TABLE dbo.ZZT021_COLOR (
	COLOR tinyint NOT NULL 
	CONSTRAINT PK_ZZT021_COLOR PRIMARY KEY  CLUSTERED 
	(
		COLOR
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT521_COLOR     ******/
CREATE TABLE dbo.ZZT521_COLOR (
	COLOR tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT521_COLOR_LDES DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT521_COLOR_SDES DEFAULT (null),
	CONSTRAINT PK_ZZT521_COLOR PRIMARY KEY  CLUSTERED 
	(
		COLOR,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT024_ROUND    ******/
CREATE TABLE  dbo.ZZT024_ROUND (
	ROUND char(1) NOT NULL,
	NORDER tinyint NULL, 
	CONSTRAINT PK_ZZT024_ROUND PRIMARY KEY  CLUSTERED 
	(
		ROUND
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT524_ROUND     ******/
CREATE TABLE dbo.ZZT524_ROUND (
	ROUND char(1) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT524_ROUND_LDES DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT524_ROUND_SDES DEFAULT (null),
	CONSTRAINT PK_ZZT524_ROUND PRIMARY KEY  CLUSTERED 
	(
		ROUND,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT025_UNIFORM    ******/
CREATE TABLE  dbo.ZZT025_UNIFORM (
	SEX char(1) NOT NULL,
	EVENT char(3) NOT NULL,
	REGISTER int NOT NULL,
	UNIFORM smallint NOT NULL,
	NORDER smallint NULL,
	DIFFERENT  tinyint NULL,
	SHIRT	int NULL,
	SHORTS	int NULL,
	SOCKS	int NULL,
	CONSTRAINT PK_ZZT025_UNIFORM PRIMARY KEY  CLUSTERED 
	(
		SEX,
		EVENT,
		REGISTER,
		UNIFORM
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT530_OVERALL_DESCRIPTION  ******/
CREATE TABLE dbo.ZZT530_OVERALL_DESCRIPTION (
	IDLANGUAGE char (3) NOT NULL ,
	POOL_LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT530_POOL_LDES DEFAULT (null),
	POOL_SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT530_POOL_SDES DEFAULT (null),
	MATCH_LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT530_MATCH_LDES DEFAULT (null),
	MATCH_SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT530_MATCH_SDES DEFAULT (null),
	SPLIT_LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT530_SPLIT_LDES DEFAULT (null),
	SPLIT_SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT530_SPLIT_SDES DEFAULT (null),
	CONSTRAINT PK_ZZT530_OVERALL_DESCRIPTION PRIMARY KEY  CLUSTERED 
	(
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT040_ECPLAY  ******/
CREATE TABLE dbo.ZZT040_ECPLAY (
	ID int NOT NULL ,
	DESCRIPTION varchar (20) NULL ,
	CONSTRAINT PK_ZZT040_ECPLAY PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT041_ECPLAYDATA  ******/
CREATE TABLE dbo.ZZT041_ECPLAYDATA (
	ID int NOT NULL ,
	DESCRIPTION varchar (20) NULL ,
	NEEDTYPE int NOT NULL,
	DATATYPE int NOT NULL,
	CONSTRAINT PK_ZZT041_ECPLAYDATA PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT042_ECEVENT	******/
CREATE TABLE dbo.ZZT042_ECEVENT	(
	ID int NOT NULL ,
	DESCRIPTION varchar (20) NULL ,
	EVENTTYPE int NOT NULL,
	VALUE1	int NOT NULL,
	VALUE2	int NOT NULL,
	IDPREV	int NOT NULL,
	CONSTRAINT PK_ZZT042_ECEVENT	PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT043_ECSTATISTIC	******/
CREATE TABLE dbo.ZZT043_ECSTATISTIC (
	ID int NOT NULL ,
	DESCRIPTION varchar (20) NULL ,
	IDREAL  int NOT NULL,
	AFFECTED int NOT NULL,
	OPERATION int NOT NULL,
	OPVALUE	int NOT NULL,
	CONSTRAINT PK_ZZT043_ECSTATISTIC PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT044_ECRELATION ******/
CREATE TABLE dbo.ZZT044_ECRELATION (
	ID int NOT NULL ,
	RELATION int NOT NULL,
	SOURCE  int NOT NULL,
	TARGET	int NOT NULL,
	CONSTRAINT PK_ZZT044_ECRELATION PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT037_STATISTIC  ******/
CREATE TABLE dbo.ZZT037_STATISTIC (
	ID int NOT NULL ,
	LDESCRIPTION varchar (35) NULL ,
	INITIALS varchar (10) NULL ,
	S_OFFSET smallint NULL CONSTRAINT DF_ZZT037_STATISTIC_OFFSET DEFAULT (0),
	S_LENGTH smallint NULL CONSTRAINT DF_ZZT037_STATISTIC_LENGHT DEFAULT (0),
	CONSTRAINT PK_ZZT037_STATISTIC PRIMARY KEY  CLUSTERED 
	(
		ID
	) WITH  FILLFACTOR = 90
)
GO
