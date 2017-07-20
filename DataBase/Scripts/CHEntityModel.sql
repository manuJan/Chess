
/****** Object:  Table dbo.ZCH564_MASTER_TYPE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZCH564_MASTER_TYPE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZCH564_MASTER_TYPE
GO

/****** Object:  Table dbo.ZCH064_MASTER_TYPE   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZCH064_MASTER_TYPE') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZCH064_MASTER_TYPE
GO

/****** Object:  Table dbo.ZCH568_TEAM_MATCH_CNFG   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZCH568_TEAM_MATCH_CNFG') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZCH568_TEAM_MATCH_CNFG
GO

/****** Object:  Table dbo.ZCH068_TEAM_MATCH_CNFG   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZCH068_TEAM_MATCH_CNFG') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZCH068_TEAM_MATCH_CNFG
GO

/****** Object:  Table dbo.ZCH062_RATING_DIF   ******/
if exists (select * from sysobjects where id = object_id('dbo.ZCH062_RATING_DIF') and OBJECTPROPERTY(id, 'IsUserTable') = 1)
	drop table dbo.ZCH062_RATING_DIF
GO


/****** Object:  Table dbo.ZZT004_DEFINITION    ******/
ALTER table dbo.ZZT004_DEFINITION add AUTO_PROG tinyint NULL CONSTRAINT DF_ZZT004_DEFINITION_AUTO_PROG DEFAULT (0)
GO

/****** Object:  Table dbo.ZZT010_REGISTER    ******/
ALTER table dbo.ZZT010_REGISTER add MASTER_TYPE smallint NULL CONSTRAINT DF_ZZT010_REGISTER_MASTER_TYPE DEFAULT (null)
GO

/****** Object:  Table dbo.ZZT011_EVENT    ******/
ALTER table dbo.ZZT011_EVENT add TWO_BRONCES smallint NULL CONSTRAINT DF_ZZT011_EVENT_TWO_BRONCES DEFAULT (0)
GO
ALTER table dbo.ZZT011_EVENT add TYPE_EVENT smallint NULL CONSTRAINT DF_ZZT011_EVENT_TYPE_EVENT DEFAULT (0)
GO
ALTER table dbo.ZZT011_EVENT add REQRANKORDER nvarchar (20) NULL CONSTRAINT DF_ZZT011_EVENT_REQRKORDER DEFAULT (null)
GO
ALTER table dbo.ZZT011_EVENT add TEAMCFG smallint NULL CONSTRAINT DF_ZZT011_EVENT_TEAMCFG DEFAULT (0)
GO
ALTER table dbo.ZZT011_EVENT add CONST_RATING float NULL CONSTRAINT DF_ZZT011_EVENT_CONST_RATING DEFAULT (null)
GO
ALTER table dbo.ZZT011_EVENT add POINTS_BYE float NULL CONSTRAINT DF_ZZT011_EVENT_POINTS_BYE DEFAULT (null)
GO
ALTER table dbo.ZZT011_EVENT add CODE_REPORTS varchar (10) NULL CONSTRAINT DF_ZZT011_EVENT_CODE_REPORTS DEFAULT (null)
GO

/****** Object:  Table dbo.ZZT012_PHASE_BASE   ******/
ALTER table dbo.ZZT012_PHASE_BASE add TYPEPHASE smallint NULL CONSTRAINT DF_ZZT012_PHASE_BASE_TYPEPHASE DEFAULT (0)
GO


/****** Object:  Table dbo.ZZT051_INSCRIPTION    ******/

ALTER table dbo.ZZT051_INSCRIPTION add SEED smallint NULL CONSTRAINT DF_ZZT051_INSCRIPTION_SEED DEFAULT (0)
GO
ALTER table dbo.ZZT051_INSCRIPTION add RATING int NULL CONSTRAINT DF_ZZT051_INSCRIPTION_RATING DEFAULT (0)
GO
ALTER table dbo.ZZT051_INSCRIPTION add KCONST smallint NULL CONSTRAINT DF_ZZT051_INSCRIPTION_KCONST DEFAULT (0)
GO

/****** Object:  Table dbo.ZZT052_MEMBER    ******/
ALTER table dbo.ZZT052_MEMBER add IDFUNCTION tinyint NOT NULL CONSTRAINT DF_ZZT052_MEMBER_IDFUNCTION DEFAULT (0)
GO
ALTER table dbo.ZZT052_MEMBER add RATING int NULL CONSTRAINT DF_ZZT052_MEMBER_RATING DEFAULT (0)
GO
ALTER table dbo.ZZT052_MEMBER add KCONST smallint NULL CONSTRAINT DF_ZZT052_MEMBER_KCONST DEFAULT (0)
GO


/****** Object:  Table dbo.ZZT053_PHASE    ******/
ALTER table dbo.ZZT053_PHASE add TYPEPHASE smallint NULL CONSTRAINT DF_ZZT053_PHASE_TYPEPHASE DEFAULT (0)
GO
ALTER table dbo.ZZT053_PHASE add TEAM_MATCH_CNFG smallint NULL CONSTRAINT DF_ZZT053_PHASE_TEAM_MATCH_CNFG DEFAULT (0)
GO


/****** Object:  Table dbo.ZTH008_MATCH    ******/

ALTER table dbo.ZTH008_MATCH add IDTYPE tinyint NOT NULL CONSTRAINT DF_ZTH008_MATCH_IDTYPE DEFAULT (-1)
GO
ALTER table dbo.ZTH008_MATCH add ROUND smallint NULL CONSTRAINT DF_ZTH008_MATCH_ROUND DEFAULT (null)
GO


/****** Object:  Table dbo.ZTH009_MATCH_RESULT    ******/

ALTER table dbo.ZTH009_MATCH_RESULT add POINTS_F float NULL CONSTRAINT DF_ZTH009_MATCH_RESULT_POINTS_F DEFAULT (null)
GO
ALTER table dbo.ZTH009_MATCH_RESULT add UPFLOATER tinyint NULL CONSTRAINT DF_ZTH009_MATCH_RESULT_UPFLOATER DEFAULT (0)
GO
ALTER table dbo.ZTH009_MATCH_RESULT add DOWNFLOATER tinyint NULL CONSTRAINT DF_ZTH009_MATCH_RESULT_DOWNFLOATER DEFAULT (0)
GO
ALTER table dbo.ZTH009_MATCH_RESULT add COLOR smallint NOT NULL CONSTRAINT DF_ZTH009_MATCH_RESULT_COLOR DEFAULT (0)
GO


/****** Object:  Table dbo.ZTH006_POOL_RESULT    ******/
ALTER table dbo.ZTH006_POOL_RESULT add	MATCHES_PLAYED smallint NULL CONSTRAINT DF_ZTH006_POOL_RESULT_MATCHES_PLAYED DEFAULT (0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	WON_GAMES smallint NULL CONSTRAINT DF_ZTH006_POOL_RESULT_WON_GAMES DEFAULT (0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	LOST_GAMES smallint NULL CONSTRAINT DF_ZTH006_POOL_RESULT_LOST_GAMES DEFAULT (0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	TIE_GAMES smallint NULL CONSTRAINT DF_ZTH006_POOL_RESULT_TIE_GAMES DEFAULT (0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	POINTS_F float NULL CONSTRAINT DF_ZTH006_POOL_RESULT_POINTS_F DEFAULT (0.0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	SOLKOFF float NULL CONSTRAINT DF_ZTH006_POOL_RESULT_SOLKOFF DEFAULT (0.0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	MEDIAN_SOLKOFF float NULL CONSTRAINT DF_ZTH006_POOL_RESULT_MEDIANSOLKOFF DEFAULT (0.0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	SONNEBERGER float NULL CONSTRAINT DF_ZTH006_POOL_RESULT_SONNEBERGER DEFAULT (0.0)
GO
ALTER table dbo.ZTH006_POOL_RESULT add	PROGRESSIVE_SCORE float NULL CONSTRAINT DF_ZTH006_POOL_RESULT_PROGRESSIVE_SCORE DEFAULT (0.0)
GO


/****** Object:  Table dbo.ZZT020_EVENTRESULT    ******/
ALTER table dbo.ZZT020_EVENTRESULT add RATING int NULL CONSTRAINT DF_ZZT020_EVENTRESULT_RATING DEFAULT (0)
GO



/****** Object:  Table dbo.ZCH564_MASTER_TYPE    ******/
CREATE TABLE dbo.ZCH564_MASTER_TYPE (
	MASTER_TYPE smallint NOT NULL,
	IDLANGUAGE char (3) NOT NULL ,
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZCH564_MASTER_TYPE_LDESCRIPTION DEFAULT (null),
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZCH564_MASTER_TYPE_SDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZCH564_MASTER_TYPE PRIMARY KEY CLUSTERED 
	(
		MASTER_TYPE,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
) 
GO

/****** Object:  Table dbo.ZCH064_MASTER_TYPE    ******/
CREATE TABLE dbo.ZCH064_MASTER_TYPE (
	MASTER_TYPE smallint NOT NULL,
	NORDER smallint NULL CONSTRAINT DF_ZCT064_MASTER_TYPE_NORDER DEFAULT (0),
	CONSTRAINT PK_ZCH064_MASTER_TYPE PRIMARY KEY CLUSTERED 
	(
		MASTER_TYPE
	) WITH  FILLFACTOR = 90
) 
GO

/****** Object:  Table dbo.ZCH568_TEAM_MATCH_CNFG    ******/
CREATE TABLE dbo.ZCH568_TEAM_MATCH_CNFG(
	TEAMCFG smallint NOT NULL ,
	IDLANGUAGE char (3) NOT NULL ,
	SDESCRIPTION nvarchar (20) NULL CONSTRAINT DF_ZCH568_TEAM_MATCH_CNFG_SDESCRIPTION DEFAULT (null),
	LDESCRIPTION nvarchar (35) NULL CONSTRAINT DF_ZCH568_TEAM_MATCH_CNFG_LDESCRIPTION DEFAULT (null),
	CONSTRAINT PK_ZCH568_TEAM_MATCH_CNFG PRIMARY KEY  CLUSTERED 
	(
		TEAMCFG,
		IDLANGUAGE
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.ZCH068_TEAM_MATCH_CNFG    ******/
CREATE TABLE dbo.ZCH068_TEAM_MATCH_CNFG(
	TEAMCFG smallint NOT NULL ,
	NCOMPETITORS smallint NULL ,
	NMATCHES smallint NULL ,
	NMATCHES_ELIM smallint NULL ,
	NMATCHESTYPE varchar (30) NULL , 
	NMATCHESTYPE_ELIM varchar (30) NULL , 
	COMPMATCHESDISTRIBUTION varchar (60) NULL ,
	COMPMATCHESDISTRIBUTION_ELIM varchar (60) NULL ,
	FAWAYC char (1) NULL ,
	CONSTRAINT PK_ZCH068_TEAM_MATCH_CNFG PRIMARY KEY  CLUSTERED 
	(
		TEAMCFG
	) WITH  FILLFACTOR = 90
)
GO
/****** Object:  Table dbo.ZCH062_RATING_DIF    ******/
CREATE TABLE dbo.ZCH062_RATING_DIF (
	CODE_RAT smallint NOT NULL,
	PROBABILITY smallint NULL CONSTRAINT DF_ZCH062_RATING_DIF_PROBABILITY DEFAULT (0),
	DIFFERENCE smallint NULL CONSTRAINT DF_ZCH062_RATING_DIF_DIFFERENCE DEFAULT (0),
	CONSTRAINT PK_ZCH062_RATING_DIF PRIMARY KEY CLUSTERED 
	(
		CODE_RAT
	) WITH  FILLFACTOR = 90
) 
GO
























