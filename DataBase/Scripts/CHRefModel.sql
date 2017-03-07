
/****** Object:  Table dbo.ZCH018_MEDALLIST ******/
ALTER TABLE  dbo.ZCH018_MEDALLIST 
	ADD
	CONSTRAINT FK_CHT001_INSC_ZCH018_MEDAL FOREIGN KEY 
	(
		SEX,
		EVENT,
		REGISTER
	) REFERENCES  dbo.CHT001_INSCRIPTION (
		SEX,
		EVENT,
		REGISTER
	)
GO

/****** Object:  Table dbo.ZCH509_QUALITATIVE   ******/
ALTER TABLE  dbo.ZCH509_QUALITATIVE 
	ADD
	CONSTRAINT FK_ZCH509_QUAL_ZCH009_QUAL FOREIGN KEY 
	(
		QUALITATIVE
	) REFERENCES  dbo.ZCH009_QUALITATIVE (
		QUALITATIVE
	),
	CONSTRAINT FK_ZCH509_QUAL_ZZT000_LANG FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES  dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)

GO

ALTER TABLE dbo.ZCH510_REGISTER ADD 
	CONSTRAINT FK_ZCH510_REGI_ZCH010_REGI FOREIGN KEY 
	(
		NUMBER
	) REFERENCES dbo.ZCH010_REGISTER (
		NUMBER
	)
GO


/****** Object:  Table dbo.CHT000_DEFINITION    ******/
ALTER TABLE dbo.CHT000_DEFINITION 
	ADD 
	CONSTRAINT FK_CHT000_DEFINITION_ZZT001_DISCIPLINE FOREIGN KEY 
	(
		DISCIPLINE
	) REFERENCES dbo.ZZT001_DISCIPLINE (
		DISCIPLINE
	),
	CONSTRAINT FK_CHT000_DEFINITION_ZZT008_CHAMPIONSHIP FOREIGN KEY 
	(
		CHAMP
	) REFERENCES dbo.ZZT008_CHAMPIONSHIP (
		CHAMP
	)
GO

/****** Object:  Table dbo.CHT001_INSCRIPTION    ******/
ALTER TABLE dbo.CHT001_INSCRIPTION 
	ADD 
	CONSTRAINT FK_CHT001_INSC_ZCH010_REGI FOREIGN KEY 
	(
		REGISTER
	) REFERENCES dbo.ZCH010_REGISTER (
		NUMBER
	),
	CONSTRAINT FK_CHT001_INSC_ZCH011_EVEN FOREIGN KEY 
	(
		SEX,
		EVENT
	) REFERENCES dbo.ZCH011_EVENT (
		SEX,
		EVENT
	)
GO

/****** Object:  Table dbo.CHT002_MEMBER    ********/
ALTER TABLE dbo.CHT002_MEMBER 
	ADD 
	CONSTRAINT FK_CHT002_MEMBER_CHT001_INSCRIPTION FOREIGN KEY 
	(
		SEX,
		EVENT,
		REGISTER
	) REFERENCES dbo.CHT001_INSCRIPTION (
		SEX,
		EVENT,
		REGISTER
	)
GO

/****** Object:  Table dbo.CHT003_PHASE    ********/
ALTER TABLE dbo.CHT003_PHASE 
	ADD 
	CONSTRAINT FK_CHT003_PHASE_ZCH011_EVENT FOREIGN KEY 
	(
		SEX,
		EVENT
	) REFERENCES dbo.ZCH011_EVENT (
		SEX,
		EVENT
	)
GO

/****** Object:  Table dbo.CHT005_POOL    ********/
ALTER TABLE dbo.CHT005_POOL 
	ADD 
	CONSTRAINT FK_CHT005_POOL_CHT003_PHASE FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE
	) REFERENCES dbo.CHT003_PHASE (
		SEX,
		EVENT,
		PHASE
	)
GO

/****** Object:  Table dbo.CHT006_POOL_RESULT    ********/
ALTER TABLE dbo.CHT006_POOL_RESULT ADD 
	CONSTRAINT FK_CHT006_POOL_RESULT_CHT005_POOL FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE,
		POOL
	) REFERENCES dbo.CHT005_POOL (
		SEX,
		EVENT,
		PHASE,
		POOL
	),

	CONSTRAINT FK_CHT009_POOL_RESULT_ZCH010_REGISTER FOREIGN KEY 
	(
        	NUMBER
	) REFERENCES dbo.ZCH010_REGISTER (
        	NUMBER
	)

GO

/****** Object:  Table dbo.CHT007_SPLIT_POOL_RESULT    ******/
ALTER TABLE dbo.CHT007_SPLIT_POOL_RESULT 
	ADD 
	CONSTRAINT FK_CHT007_SPLIT_POOL_CHT006_POOL_RESULT FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE,
		POOL,
		POOL_RESULT
		
	) REFERENCES dbo.CHT006_POOL_RESULT (
		SEX,
		EVENT,
		PHASE,
		POOL,
		IDPOSITION
	)
GO

/****** Object:  Table dbo.CHT008_MATCH    ******/
ALTER TABLE dbo.CHT008_MATCH 
	ADD 
	CONSTRAINT FK_CHT008_MATCH_CHT005_POOL FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE,
		POOL
	) REFERENCES dbo.CHT005_POOL (
		SEX,
		EVENT,
		PHASE,
		POOL
	)
GO

/****** Object:  Table dbo.CHT009_MATCH_RESULT    ******/
ALTER TABLE dbo.CHT009_MATCH_RESULT 
	ADD 
	CONSTRAINT FK_CHT009_MATCH_RESULT_CHT008_MATCH FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE,
		POOL,
		IDMATCH
	) REFERENCES dbo.CHT008_MATCH (
		SEX,
		EVENT,
		PHASE,
		POOL,
		IDMATCH
	),
	CONSTRAINT FK_CHT009_MATCH_RESULT_ZCH010_REGISTER FOREIGN KEY 
	(
        	NUMBER
	) REFERENCES dbo.ZCH010_REGISTER (
        	NUMBER
	)

GO

/****** Object:  Table dbo.CHT010_SPLIT_MATCH_RESULT    ******/
ALTER TABLE dbo.CHT010_SPLIT_MATCH_RESULT 
	ADD 
	CONSTRAINT FK_CHT010_SPLIT_MATCH_CHT008_MATCH_RESULT FOREIGN KEY 
	(
		SEX,
		EVENT,
		PHASE,
		POOL,
		IDMATCH,
		MATCH_RESULT
		
	) REFERENCES dbo.CHT009_MATCH_RESULT (
		SEX,
		EVENT,
		PHASE,
		POOL,
		IDMATCH,
		IDPOSITION
	)
GO

/****** Object:  Table dbo.ZCH010_REGISTER    ******/
ALTER TABLE dbo.ZCH010_REGISTER 
	ADD 
	CONSTRAINT FK_ZCH010_REGISTER_ZZT002_SEX FOREIGN KEY 
	(
		SEX
	) REFERENCES dbo.ZZT002_SEX (
		SEX
	),
	CONSTRAINT FK_ZCH010_REGISTER_ZZT019_REGTYPE FOREIGN KEY 
	(
		TYPE
	) REFERENCES dbo.ZZT019_REGTYPE (
		TYPE
	),
	CONSTRAINT FK_ZCH010_REGISTER_ZZT003_COUNTRY FOREIGN KEY 
	(
		COUNTRY
	) REFERENCES dbo.ZZT003_COUNTRY (
		COUNTRY
	),
	CONSTRAINT FK_ZCH010_REGISTER_ZZT004_CLUB FOREIGN KEY 
	(
		CLUB
	) REFERENCES dbo.ZZT004_CLUB (
		CLUB
	),
	CONSTRAINT FK_ZCH010_REGISTER_ZZT005_FEDERATION FOREIGN KEY 
	(
		FEDERATION
	) REFERENCES dbo.ZZT005_FEDERATION (
		FEDERATION
	),
	CONSTRAINT FK_ZCH010_REGISTER_ZZT007_CATEGORY FOREIGN KEY 
	(
		CATEGORY
	) REFERENCES dbo.ZZT007_CATEGORY (
		CATEGORY
	)	
GO

/****** Object:  Table dbo.ZCH510_REGISTER    ******/
ALTER TABLE dbo.ZCH510_REGISTER 
	ADD 
	CONSTRAINT FK_ZCH510_REGISTER_ZCH010_REGISTER FOREIGN KEY 
	(
		NUMBER
	) REFERENCES dbo.ZCH010_REGISTER (
		NUMBER
	),
	CONSTRAINT FK_ZCH510_REGISTER_ZZT000_LANGUAGE FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)
GO

/****** Object:  Table dbo.ZCH511_EVENT    ******/
ALTER TABLE dbo.ZCH511_EVENT
	ADD 
	CONSTRAINT FK_ZCH511_EVENT_ZCH011_EVENT FOREIGN KEY 
	(
		SEX,
		EVENT
	) REFERENCES dbo.ZCH011_EVENT (
		SEX,
		EVENT
	),
	CONSTRAINT FK_ZCH511_EVENT_ZZT000_LANGUAGE FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)
GO

/****** Object:  Table dbo.ZCH512_PHASE    ******/
ALTER TABLE dbo.ZCH512_PHASE
	ADD 
	CONSTRAINT FK_ZCH512_PHASE_ZCH012_PHASE FOREIGN KEY 
	(
		PHASE
	) REFERENCES dbo.ZCH012_PHASE (
		PHASE
	),
	CONSTRAINT FK_ZCH512_PHASE_ZZT000_LANGUAGE FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)
GO
/****** Object:  Table dbo.ZCH023_MODALITY_PHASE    ******/
ALTER  TABLE  dbo.ZCH023_MODALITY_PHASE 
	ADD
	CONSTRAINT FK_ZCH023_MODA_PHASE_ZZT022_MODALITY FOREIGN KEY 
	(
		MODALITY
	) REFERENCES  dbo.ZZT022_MODALITY (
		MODALITY
	)
GO

/****** Object:  Table dbo.CHT564_MASTER_TYPE    ******/
ALTER TABLE dbo.CHT564_MASTER_TYPE
	ADD 
	CONSTRAINT FK_CHT564_MASTER_TYPECHT064_MASTER_TYPE FOREIGN KEY 
	(
		MASTER_TYPE
	) REFERENCES dbo.CHT064_MASTER_TYPE (
		MASTER_TYPE
	),
	CONSTRAINT FK_CHT564_MASTER_TYPE_LANGUAGE FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)
GO

/****** Object:  Table dbo.CHT568_TEAM_MATCH_CNFG    ******/
ALTER TABLE dbo.CHT568_TEAM_MATCH_CNFG 
	ADD 
	CONSTRAINT FK_CHT568_TEAM_MATCH_CNFG_CHT068_TEAM_MATCH_CNFG FOREIGN KEY 
	(
		TEAMCFG
	) REFERENCES dbo.CHT068_TEAM_MATCH_CNFG (
		TEAMCFG
	),
	CONSTRAINT FK_CHT568_TEAM_MATCH_CNFG_LANGUAGE FOREIGN KEY 
	(
		IDLANGUAGE
	) REFERENCES dbo.ZZT000_LANGUAGE (
		IDLANGUAGE
	)
GO