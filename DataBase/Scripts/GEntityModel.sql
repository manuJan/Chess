


if exists (select * from sysobjects where id = object_id('dbo.NUMBERING') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.NUMBERING
GO


/****** Object:  Table dbo.ZZT501_DISCIPLINE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT501_DISCIPLINE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT501_DISCIPLINE
GO

/****** Object:  Table dbo.ZZT001_DISCIPLINE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT001_DISCIPLINE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT001_DISCIPLINE
GO

/****** Object:  Table dbo.ZZT502_SEX   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT502_SEX') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT502_SEX
GO

/****** Object:  Table dbo.ZZT002_SEX   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT002_SEX') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT002_SEX
GO

/****** Object:  Table dbo.ZZT503_COUNTRY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT503_COUNTRY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT503_COUNTRY
GO

/****** Object:  Table dbo.ZZT003_COUNTRY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT003_COUNTRY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT003_COUNTRY
GO

/****** Object:  Table dbo.ZZT504_CLUB   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT504_CLUB') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT504_CLUB
GO

/****** Object:  Table dbo.ZZT004_CLUB   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT004_CLUB') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT004_CLUB
GO

/****** Object:  Table dbo.ZZT027_MEDICAL_CLASS   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT027_MEDICAL_CLASS') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT027_MEDICAL_CLASS
GO

/****** Object:  Table dbo.ZZT505_FEDERATION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT505_FEDERATION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT505_FEDERATION
GO

/****** Object:  Table dbo.ZZT005_FEDERATION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT005_FEDERATION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT005_FEDERATION
GO

/****** Object:  Table dbo.ZZT506_VENUE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT506_VENUE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT506_VENUE
GO

/****** Object:  Table dbo.ZZT006_VENUE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT006_VENUE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT006_VENUE
GO

/****** Object:  Table dbo.ZZT507_CATEGORY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT507_CATEGORY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT507_CATEGORY
GO

/****** Object:  Table dbo.ZZT007_CATEGORY   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT007_CATEGORY') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT007_CATEGORY
GO

/****** Object:  Table dbo.ZZT508_CHAMPIONSHIP   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT508_CHAMPIONSHIP') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT508_CHAMPIONSHIP
GO

/****** Object:  Table dbo.ZZT008_CHAMPIONSHIP   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT008_CHAMPIONSHIP') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT008_CHAMPIONSHIP
GO

/****** Object:  Table dbo.ZZT513_FUNCTION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT513_FUNCTION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT513_FUNCTION
GO

/****** Object:  Table dbo.ZZT514_POSITION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT514_POSITION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT514_POSITION
GO

/****** Object:  Table dbo.ZZT014_POSITION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT014_POSITION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT014_POSITION
GO

/****** Object:  Table dbo.ZZT013_FUNCTION   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT013_FUNCTION') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT013_FUNCTION
GO

/****** Object:  Table dbo.ZZT515_STATUS   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT515_STATUS') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT515_STATUS
GO

/****** Object:  Table dbo.ZZT015_STATUS   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT015_STATUS') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT015_STATUS
GO

/****** Object:  Table dbo.ZZT517_MEDAL   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT517_MEDAL') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT517_MEDAL
GO

/****** Object:  Table dbo.ZZT017_MEDAL   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT017_MEDAL') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT017_MEDAL
GO

/****** Object:  Table dbo.ZZT519_REGTYPE ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT519_REGTYPE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT519_REGTYPE
GO

/****** Object:  Table dbo.ZZT019_REGTYPE ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT019_REGTYPE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT019_REGTYPE
GO

/****** Object:  Table dbo.ZZT526_WEATHER   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT526_WEATHER') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT526_WEATHER
GO

/****** Object:  Table dbo.ZZT026_WEATHER   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT026_WEATHER') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT026_WEATHER
GO

/****** Object:  Table dbo.ZZT000_LANGUAGE  ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT000_LANGUAGE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT000_LANGUAGE 
GO

/****** Object:  Table dbo.NUMBERING ******/
if exists (select * from sysobjects where id = object_id('dbo.NUMBERING') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.NUMBERING
GO

/****** Object:  Table dbo.NUMBERING    ******/
CREATE TABLE dbo.NUMBERING (
	LAST_NUMBER int NOT NULL CONSTRAINT DF_NUMBERING_LAST_NUMBER DEFAULT (0),
	CONSTRAINT PK_NUMBERING PRIMARY KEY  CLUSTERED 
	(
		LAST_NUMBER
	) WITH  FILLFACTOR = 50
)
GO

/****** Object:  Table dbo.ZZT000_LANGUAGE     ******/
CREATE TABLE dbo.ZZT000_LANGUAGE (
	IDLANGUAGE char (3) NOT NULL ,
	DESCRIPTION nvarchar (30) NOT NULL ,
	FNAMES char (1) NOT NULL CONSTRAINT DF_ZZT000_LANGUAGE_FNAMES DEFAULT ('Y'),
	FACTIVE char (1) NOT NULL CONSTRAINT DF_ZZT000_LANGUAGE_FACTIVE DEFAULT ('Y'),
	NORDER tinyint NULL,
	CPAGE varchar (30) NOT NULL CONSTRAINT DF_ZZT000_LANGUAGE_CPAGE DEFAULT ('.1252'),
	CONSTRAINT PK_ZZT000_LANGUAGE PRIMARY KEY  CLUSTERED 
	(
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT001_DISCIPLINE     ******/
CREATE TABLE dbo.ZZT001_DISCIPLINE (
	DISCIPLINE char (2) NOT NULL ,
	CONSTRAINT PK_ZZT001_DISCIPLINE PRIMARY KEY  CLUSTERED 
	(
		DISCIPLINE
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT501_DISCIPLINE     ******/
CREATE TABLE dbo.ZZT501_DISCIPLINE (
	DISCIPLINE char (2) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT501_DISCIPLINE_LDSECRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT501_DISCIPLINE_SDSECRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT501_DISCIPLINE PRIMARY KEY  CLUSTERED 
	(
		DISCIPLINE,
		IDLANGUAGE 

	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT002_SEX     ******/
CREATE TABLE dbo.ZZT002_SEX (
	SEX char (1) NOT NULL ,
	CONSTRAINT PK_ZZT002_SEX PRIMARY KEY  CLUSTERED 
	(
		SEX
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT502_SEX     ******/
CREATE TABLE dbo.ZZT502_SEX (
	SEX char (1) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT502_SEX_LDSECRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT502_SEX_SDSECRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT502_SEX PRIMARY KEY  CLUSTERED 
	(
		SEX,
		IDLANGUAGE 

	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT003_COUNTRY     ******/
CREATE TABLE dbo.ZZT003_COUNTRY (
	COUNTRY char (3) NOT NULL ,
	FLG_VALID tinyint NULL,
	ISO_CODE varchar (6) NOT NULL CONSTRAINT DF_ZZT003_COUNTRY_ISO_CODE DEFAULT(' '),
	CONSTRAINT PK_ZZT003_CCOUNTRY PRIMARY KEY  CLUSTERED 
	(
		COUNTRY
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT503_COUNTRY    ******/
CREATE TABLE dbo.ZZT503_COUNTRY (
	COUNTRY char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT503_COUNTRY_LDSECRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT503_COUNTRY_SDSECRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT503_COUNTRY PRIMARY KEY  CLUSTERED 
	(
		COUNTRY,
		IDLANGUAGE 

	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT004_CLUB     ******/
CREATE TABLE dbo.ZZT004_CLUB (
	CLUB char (3) NOT NULL ,
	CONSTRAINT PK_ZZT004_CLUB PRIMARY KEY  CLUSTERED 
	(
		CLUB
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT504_CLUB    ******/
CREATE TABLE dbo.ZZT504_CLUB (
	CLUB char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT504_CLUB_LDSECRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT504_CLUB_SDSECRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT504_CLUB PRIMARY KEY  CLUSTERED 
	(
		CLUB,
		IDLANGUAGE 

	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT005_FEDERATION     ******/
CREATE TABLE dbo.ZZT005_FEDERATION (
	FEDERATION char (3) NOT NULL ,
	CONSTRAINT PK_ZZT005_FEDERATION PRIMARY KEY  CLUSTERED 
	(
		FEDERATION
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT505_FEDERATION    ******/
CREATE TABLE dbo.ZZT505_FEDERATION (
	FEDERATION char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT505_FEDE_LDSECRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT505_FEDE_SDSECRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT505_FEDERATION PRIMARY KEY  CLUSTERED 
	(
		FEDERATION,
		IDLANGUAGE 

	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT006_VENUE     ******/
CREATE TABLE dbo.ZZT006_VENUE (
	VENUE char (3) NOT NULL ,
	CONSTRAINT PK_ZZT006_VENUE PRIMARY KEY  CLUSTERED 
	(
		VENUE
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT506_VENUE     ******/
CREATE TABLE dbo.ZZT506_VENUE (
	VENUE char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT506_VENUE_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT506_VENUE_SDESCRIPTION DEFAULT (null),
	LLOCATION nvarchar (35) NULL CONSTRAINT DF_ZZT506_VENUE_LLOCATION DEFAULT (null),
	SLOCATION nvarchar (20) NULL CONSTRAINT DF_ZZT506_VENUE_SLOCATION DEFAULT (null),
	COUNTRY char(3) NULL CONSTRAINT DF_ZZT506_VENUE_COUNTRY DEFAULT (null),
	CONSTRAINT PK_ZZT506_VENUE PRIMARY KEY  CLUSTERED 
	(
		VENUE,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT007_CATEGORY    ******/
CREATE TABLE dbo.ZZT007_CATEGORY (
	CATEGORY char(1) NOT NULL ,
	NORDER tinyint NOT NULL CONSTRAINT DF_ZZT007_CATEGORY_ORDER_N DEFAULT (0),
	CONSTRAINT PK_ZZT007_CATEGORY PRIMARY KEY  CLUSTERED 
	(
		CATEGORY
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT507_CATEGORY     ******/
CREATE TABLE dbo.ZZT507_CATEGORY (
	CATEGORY char(1) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT507_CATE_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT507_CATE_SDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT507_CATEGORY PRIMARY KEY  CLUSTERED 
	(
		CATEGORY,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT008_CHAMPIONSHIP    ******/
CREATE TABLE dbo.ZZT008_CHAMPIONSHIP (
	CHAMP char (3) NOT NULL ,
	RLEVEL tinyint NOT NULL CONSTRAINT DF_ZZT008_CHAMPIONSHIP_RLEVEL DEFAULT (5),
	HEADER_ORD smallint NULL CONSTRAINT DF_ZZT008_CHAMPIONSHIP_HEADER_ORD DEFAULT (0),
	CONSTRAINT PK_ZZT008_CHAMPIONSHIP PRIMARY KEY  CLUSTERED 
	(
		CHAMP
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT508_CHAMPIONSHIP   ******/
CREATE TABLE dbo.ZZT508_CHAMPIONSHIP (
	CHAMP char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT508_CHAM_LDESDRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT508_CHAM_SDESCRIPTION DEFAULT (null),
	RLDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT508_CHAM_RLDESCRIPTION DEFAULT (null),
	RSDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT508_CHAM_RSDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT508_CHAMPIONSHIP PRIMARY KEY  CLUSTERED 
	(
		CHAMP,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO


/****** Object:  Table dbo.ZZT013_FUNCTION    ******/
CREATE TABLE dbo.ZZT013_FUNCTION (
	IDFUNCTION tinyint NOT NULL ,
	REG_TYPE tinyint NOT NULL CONSTRAINT DF_ZZT013_FUNCTION_REG_TYPE DEFAULT (0),
	CONSTRAINT PK_ZZT013_FUNCTION PRIMARY KEY  CLUSTERED 
	(
		IDFUNCTION
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT513_FUNCTION    ******/
CREATE TABLE dbo.ZZT513_FUNCTION (
	IDFUNCTION tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT513_FUNCTION_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT513_FUNCTION_SDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT513_FUNCTION PRIMARY KEY  CLUSTERED 
	(
		IDFUNCTION,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT014_POSITION    ******/
CREATE TABLE dbo.ZZT014_POSITION (
	IDPOSITION tinyint NOT NULL , 	
	IDFUNCTION tinyint NULL CONSTRAINT DF_ZZT014_POSITION_IDFUNCTION DEFAULT (null),
	CONSTRAINT PK_ZZT014_POSITION PRIMARY KEY  CLUSTERED 
	(
		IDPOSITION
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT514_POSITION    ******/
CREATE TABLE dbo.ZZT514_POSITION (
	IDPOSITION tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT514_POSITION_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT514_POSITION_SDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT514_POSITION PRIMARY KEY  CLUSTERED 
	(
		IDPOSITION,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT015_STATUS     ******/
CREATE TABLE dbo.ZZT015_STATUS (
	STATUS tinyint NOT NULL ,
	CONSTRAINT PK_ZZT015_STATUS PRIMARY KEY  CLUSTERED 
	(
		STATUS
	) WITH  FILLFACTOR = 90
)

/****** Object:  Table dbo.ZZT515_STATUS   ******/
CREATE TABLE dbo.ZZT515_STATUS (
	STATUS tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT515_STATUS_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT515_STATUS_SDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT515_STATUS PRIMARY KEY  CLUSTERED 
	(
		STATUS,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT017_MEDAL     ******/
CREATE TABLE dbo.ZZT017_MEDAL (
	MEDAL tinyint NOT NULL ,
	CONSTRAINT PK_ZZT017_MEDAL PRIMARY KEY  CLUSTERED 
	(
		MEDAL
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT517_MEDAL    ******/
CREATE TABLE dbo.ZZT517_MEDAL (
	MEDAL tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL ,
	SDESCRIPTION nvarchar (20) NULL ,
	CONSTRAINT PK_ZZT517_MEDAL PRIMARY KEY  CLUSTERED 
	(
		MEDAL,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT019_REGTYPE     ******/
CREATE TABLE dbo.ZZT019_REGTYPE (
	TYPE tinyint NOT NULL ,
	CONSTRAINT PK_ZZT019_REGTYPE PRIMARY KEY  CLUSTERED 
	(
		TYPE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT519_REGTYPE    ******/
CREATE TABLE dbo.ZZT519_REGTYPE (
	TYPE tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL ,
	SDESCRIPTION nvarchar (20) NULL ,
	CONSTRAINT PK_ZZT519_REGTYPE PRIMARY KEY  CLUSTERED 
	(
		TYPE,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT026_WEATHER     ******/
CREATE TABLE dbo.ZZT026_WEATHER (
	IDWEATHER tinyint NOT NULL ,
	IDXML varchar(10) NULL ,
	CONSTRAINT PK_ZZT026_WEATHER PRIMARY KEY  CLUSTERED 
	(
		IDWEATHER
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT526_WEATHER    ******/
CREATE TABLE dbo.ZZT526_WEATHER (
	IDWEATHER tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL ,
	SDESCRIPTION nvarchar (20) NULL ,
	CONSTRAINT PK_ZZT526_WEATHER PRIMARY KEY  CLUSTERED 
	(
		IDWEATHER,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT027_MEDICAL_CLASS     ******/
CREATE TABLE dbo.ZZT027_MEDICAL_CLASS (
	IDCODE smallint NOT NULL ,
	IDLEVEL smallint NOT NULL ,
	MEDICAL_CLASS varchar(15) NOT NULL ,
	FEDERATION char (3) NULL CONSTRAINT DF_ZZT027_MEDICAL_CLASS_FEDERATION DEFAULT (null),
	CONSTRAINT PK_ZZT027_MEDICAL_CLASS PRIMARY KEY  CLUSTERED 
	(
		IDCODE
	) WITH  FILLFACTOR = 90
)
GO
