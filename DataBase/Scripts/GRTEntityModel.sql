
/****** Object:  Table dbo.ZZT516_AREA   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT516_AREA') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT516_AREA
GO

/****** Object:  Table dbo.ZZT016_AREA   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT016_AREA') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT016_AREA
GO

/****** Object:  Table dbo.ZZT520_TYPE_TOP   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT520_TYPE_TOP') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT520_TYPE_TOP
GO

/****** Object:  Table dbo.ZZT020_TYPE_TOP   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZZT020_TYPE_TOP') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZZT020_TYPE_TOP
GO

/****** Object:  Table dbo.ZZT020_TYPE_TOP    ******/
CREATE TABLE dbo.ZZT020_TYPE_TOP (
	TYPE tinyint NOT NULL ,
	CONSTRAINT PK_ZZT020_TYPE_TOP PRIMARY KEY  CLUSTERED 
	(
		TYPE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT520_TYPE_TOP   ******/
CREATE TABLE dbo.ZZT520_TYPE_TOP (
	TYPE tinyint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL ,
	SDESCRIPTION nvarchar (20) NULL ,
	CONSTRAINT PK_ZZT521_TYPE_TOP PRIMARY KEY  CLUSTERED 
	(
		TYPE,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT016_AREA    ******/
CREATE TABLE dbo.ZZT016_AREA (
	AREA char (3) NOT NULL ,
	PARENT char (3) NULL ,
	RLEVEL tinyint NOT NULL ,
	HEADER_ORD smallint NULL CONSTRAINT DF_ZZT016_AREA_HEADER_ORD DEFAULT (0),
	CONSTRAINT PK_ZZT016_AREA PRIMARY KEY  CLUSTERED 
	(
		AREA
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZZT516_AREA    ******/
CREATE TABLE dbo.ZZT516_AREA (
	AREA char (3) NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT516_AREA_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT516_AREA_SDESCRIPTION DEFAULT (null),
	RLDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZZT516_AREA_RLDESCRIPTION DEFAULT (null) ,
	RSDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZZT516_AREA_RSDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZZT516_AREA PRIMARY KEY  CLUSTERED 
	(
		AREA,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO
