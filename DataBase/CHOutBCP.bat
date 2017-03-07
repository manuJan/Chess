
BCP %4.DBO.ZCH009_QUALITATIVE out %1\ExportData\ZCH009_QUALITATIVE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH509_QUALITATIVE out %1\ExportData\ZCH509_QUALITATIVE.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH009_QUALITATIVE out %1\ExportData\ZCH009_QUALITATIVE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH509_QUALITATIVE out %1\ExportData\ZCH509_QUALITATIVE.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZZT016_AREA out %1\ExportData\ZZT016_AREA.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT516_AREA out %1\ExportData\ZZT516_AREA.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZZT004_CLUB out %1\ExportData\ZZT004_CLUB.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT504_CLUB out %1\ExportData\ZZT504_CLUB.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH011_EVENT out %1\ExportData\ZCH011_EVENT.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH511_EVENT out %1\ExportData\ZCH511_EVENT.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH012_PHASE out %1\ExportData\ZCH012_PHASE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH512_PHASE out %1\ExportData\ZCH512_PHASE.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.CHT068_TEAM_MATCH_CNFG out %1\ExportData\CHT068_TEAM_MATCH_CNFG.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.CHT568_TEAM_MATCH_CNFG out %1\ExportData\CHT568_TEAM_MATCH_CNFG.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.CHT064_MASTER_TYPE out %1\ExportData\CHT064_MASTER_TYPE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.CHT564_MASTER_TYPE out %1\ExportData\CHT564_MASTER_TYPE.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.CHT062_RATING_DIF out %1\ExportData\CHT062_RATING_DIF.txt  /n /c /U sa /P %3 /S %2


@rem QUITAR LOS CUATRO REM SIGUIENTES PARA TENER INSCRIPCIONES EN LA BASE DE DATOS
@rem PONER LOS CUATRO REM SIGUIENTES PARA NO TENER INSCRIPCIONES EN LA BASE DE DATOS
BCP %4.DBO.ZCH010_REGISTER out %1\ExportData\ZCH010_REGISTER.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH510_REGISTER out %1\ExportData\ZCH510_REGISTER.txt  /n /c /w /U sa /P %3 /S %2
BCP %4.DBO.ZCH013_JUDGE out %1\ExportData\ZCH013_JUDGE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.CHT001_INSCRIPTION out %1\ExportData\CHT001_INSCRIPTION.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.CHT020_EVENTRESULT out %1\ExportData\CHT020_EVENTRESULT.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.CHT002_MEMBER out %1\ExportData\CHT002_MEMBER.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.ZCH023_MODALITY_PHASE out %1\ExportData\ZCH023_MODALITY_PHASE.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH028_PROG_POOL_POSITION out %1\ExportData\ZCH028_PROG_POOL_POSITION.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZCH029_PROG_MATCH_POSITION out %1\ExportData\ZCH029_PROG_MATCH_POSITION.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.ZZT027_MEDICAL_CLASS out %1\ExportData\ZZT027_MEDICAL_CLASS.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.ZZT037_STATISTIC out %1\ExportData\ZZT037_STATISTIC.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT040_ECPLAY out %1\ExportData\ZZT040_ECPLAY.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT041_ECPLAYDATA out %1\ExportData\ZZT041_ECPLAYDATA.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT042_ECEVENT out %1\ExportData\ZZT042_ECEVENT.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT043_ECSTATISTIC out %1\ExportData\ZZT043_ECSTATISTIC.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT044_ECRELATION out %1\ExportData\ZZT044_ECRELATION.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.CHT000_DEFINITION out %1\ExportData\CHT000_DEFINITION.txt  /n /c /U sa /P %3 /S %2


rem  **** GTH GTH GTH GTH GTH GTH GTH GTH ****
rem  **** GTH GTH GTH GTH GTH GTH GTH GTH ****
rem  **** GTH GTH GTH GTH GTH GTH GTH GTH ****

BCP %4.DBO.ZZT021_COLOR out %1\ExportData\ZZT021_COLOR.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT521_COLOR out %1\ExportData\ZZT521_COLOR.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZZT025_UNIFORM out %1\ExportData\ZZT025_UNIFORM.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.ZZT022_MODALITY out %1\ExportData\ZZT022_MODALITY.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT522_MODALITY out %1\ExportData\ZZT522_MODALITY.txt  /n /c /w /U sa /P %3 /S %2

BCP %4.DBO.ZZT530_OVERALL_DESCRIPTION out %1\ExportData\ZZT530_OVERALL_DESCRIPTION.txt  /n /c /w /U sa /P %3 /S %2

rem  **** G G G G G G G G G G G G G G ****
rem  **** G G G G G G G G G G G G G G ****
rem  **** G G G G G G G G G G G G G G ****

BCP %4.DBO.ZZT000_LANGUAGE out %1\ExportData\ZZT000_LANGUAGE.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT001_DISCIPLINE out %1\ExportData\ZZT001_DISCIPLINE.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT501_DISCIPLINE out %1\ExportData\ZZT501_DISCIPLINE.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT002_SEX out %1\ExportData\ZZT002_SEX.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT502_SEX out %1\ExportData\ZZT502_SEX.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT003_COUNTRY out %1\ExportData\ZZT003_COUNTRY.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT503_COUNTRY out %1\ExportData\ZZT503_COUNTRY.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT006_VENUE out %1\ExportData\ZZT006_VENUE.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT506_VENUE out %1\ExportData\ZZT506_VENUE.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT007_CATEGORY out %1\ExportData\ZZT007_CATEGORY.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT507_CATEGORY out %1\ExportData\ZZT507_CATEGORY.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT008_CHAMPIONSHIP out %1\ExportData\ZZT008_CHAMPIONSHIP.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT508_CHAMPIONSHIP out %1\ExportData\ZZT508_CHAMPIONSHIP.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT013_FUNCTION out %1\ExportData\ZZT013_FUNCTION.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT513_FUNCTION out %1\ExportData\ZZT513_FUNCTION.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT014_POSITION out %1\ExportData\ZZT014_POSITION.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT514_POSITION out %1\ExportData\ZZT514_POSITION.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT015_STATUS out %1\ExportData\ZZT015_STATUS.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT515_STATUS out %1\ExportData\ZZT515_STATUS.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT017_MEDAL out %1\ExportData\ZZT017_MEDAL.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT517_MEDAL out %1\ExportData\ZZT517_MEDAL.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT019_REGTYPE out %1\ExportData\ZZT019_REGTYPE.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZZT519_REGTYPE out %1\ExportData\ZZT519_REGTYPE.txt  /n /c /w /C ACP /U sa /P %3 /S %2

BCP %4.DBO.NUMBERING out %1\ExportData\NUMBERING.txt  /n /c /C ACP /U sa /P %3 /S %2
