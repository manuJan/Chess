rem SaveAllModel <.> <servidor> <password> <base de datos> <carpeta>

@echo off
cls
if "%1%2%3%4%5" == "" goto params

MKDIR %1\%5

ECHO 1
BCP %4.DBO.NUMBERING 			    out %1\%5\NUMBERING.txt                     /n /c /w /C /U sa /P %3 /S %2
rem PAUSE

ECHO 2
BCP %4.DBO.ZCH062_RATING_DIF                out %1\%5\ZCH062_RATING_DIF.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 3
BCP %4.DBO.ZCH064_MASTER_TYPE               out %1\%5\ZCH064_MASTER_TYPE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 4
BCP %4.DBO.ZCH564_MASTER_TYPE               out %1\%5\ZCH564_MASTER_TYPE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 5
BCP %4.DBO.ZCH068_TEAM_MATCH_CNFG           out %1\%5\ZCH068_TEAM_MATCH_CNFG.txt        /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 6
BCP %4.DBO.ZCH568_TEAM_MATCH_CNFG           out %1\%5\ZCH568_TEAM_MATCH_CNFG.txt        /n /c /w /C /U sa /P %3 /S %2
rem PAUSE

ECHO 7
BCP %4.DBO.ZTH005_POOL                      out %1\%5\ZTH005_POOL.txt                   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 8
BCP %4.DBO.ZTH006_POOL_RESULT               out %1\%5\ZTH006_POOL_RESULT.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 9
BCP %4.DBO.ZTH007_SPLIT_POOL_RESULT         out %1\%5\ZTH007_SPLIT_POOL_RESULT.txt      /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 10
BCP %4.DBO.ZTH008_MATCH                     out %1\%5\ZTH008_MATCH.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 11
BCP %4.DBO.ZTH009_MATCH_RESULT              out %1\%5\ZTH009_MATCH_RESULT.txt           /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 12
BCP %4.DBO.ZTH010_SPLIT_MATCH_RESULT        out %1\%5\ZTH010_SPLIT_MATCH_RESULT.txt     /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 13
BCP %4.DBO.ZTH011_SPLIT_MATCH               out %1\%5\ZTH011_SPLIT_MATCH.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 14
BCP %4.DBO.ZTH012_MATCH_MEMBER              out %1\%5\ZTH012_MATCH_MEMBER.txt           /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 15
BCP %4.DBO.ZTH013_MATCH_JUDGE               out %1\%5\ZTH013_MATCH_JUDGE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 16
BCP %4.DBO.ZTH014_SPLIT_PHASE               out %1\%5\ZTH014_SPLIT_PHASE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 17
BCP %4.DBO.ZTH015_ROUND                     out %1\%5\ZTH015_ROUND.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 18
BCP %4.DBO.ZTH021_COLOR                     out %1\%5\ZTH021_COLOR.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 19
BCP %4.DBO.ZTH022_MODALITY                  out %1\%5\ZTH022_MODALITY.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 20
BCP %4.DBO.ZTH023_MODALITY_PHASE            out %1\%5\ZTH023_MODALITY_PHASE.txt         /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 21
BCP %4.DBO.ZTH024_MODALITY_SPLIT_PHASE      out %1\%5\ZTH024_MODALITY_SPLIT_PHASE.txt   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 22
BCP %4.DBO.ZTH025_MODALITY_POOL             out %1\%5\ZTH025_MODALITY_POOL.txt          /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 23
BCP %4.DBO.ZTH026_PROG_POOL_POSITION        out %1\%5\ZTH026_PROG_POOL_POSITION.txt     /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 24
BCP %4.DBO.ZTH027_PROG_MATCH_POSITION       out %1\%5\ZTH027_PROG_MATCH_POSITION.txt    /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 25
BCP %4.DBO.ZTH028_ROUND_BASE                out %1\%5\ZTH028_ROUND_BASE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 26
BCP %4.DBO.ZTH029_UNIFORM                   out %1\%5\ZTH029_UNIFORM.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 27
BCP %4.DBO.ZTH030_STATISTIC                 out %1\%5\ZTH030_STATISTIC.txt              /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 28
BCP %4.DBO.ZTH040_ECPLAY                    out %1\%5\ZTH040_ECPLAY.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 29
BCP %4.DBO.ZTH041_ECPLAYDATA                out %1\%5\ZTH041_ECPLAYDATA.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 30
BCP %4.DBO.ZTH042_ECEVENT                   out %1\%5\ZTH042_ECEVENT.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 31
BCP %4.DBO.ZTH043_ECSTATISTIC               out %1\%5\ZTH043_ECSTATISTIC.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 32
BCP %4.DBO.ZTH044_ECRELATION                out %1\%5\ZTH044_ECRELATION.txt             /n /c /w /C /U sa /P %3 /S %2

ECHO 33
BCP %4.DBO.ZTH521_COLOR                     out %1\%5\ZTH521_COLOR.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 34
BCP %4.DBO.ZTH528_ROUND_BASE                out %1\%5\ZTH528_ROUND_BASE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 35
BCP %4.DBO.ZTH545_OVERALL_DESCRIPTION       out %1\%5\ZTH545_OVERALL_DESCRIPTION.txt    /n /c /w /C /U sa /P %3 /S %2
rem PAUSE

ECHO 36
BCP %4.DBO.ZZT000_LANGUAGE                  out %1\%5\ZZT000_LANGUAGE.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE

ECHO 37
BCP %4.DBO.ZZT001_DISCIPLINE                out %1\%5\ZZT001_DISCIPLINE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 38
BCP %4.DBO.ZZT002_GENDER                    out %1\%5\ZZT002_GENDER.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 39
BCP %4.DBO.ZZT003_COUNTRY                   out %1\%5\ZZT003_COUNTRY.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 40
BCP %4.DBO.ZZT005_EVENT_UNIT_BASE           out %1\%5\ZZT005_EVENT_UNIT_BASE.txt        /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 41
BCP %4.DBO.ZZT006_VENUE                     out %1\%5\ZZT006_VENUE.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 42
BCP %4.DBO.ZZT007_CATEGORY                  out %1\%5\ZZT007_CATEGORY.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 43
BCP %4.DBO.ZZT009_QUALITATIVE               out %1\%5\ZZT009_QUALITATIVE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 44
BCP %4.DBO.ZZT010_REGISTER                  out %1\%5\ZZT010_REGISTER.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 45
BCP %4.DBO.ZZT011_EVENT                     out %1\%5\ZZT011_EVENT.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 46
BCP %4.DBO.ZZT012_PHASE_BASE                out %1\%5\ZZT012_PHASE_BASE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 47
BCP %4.DBO.ZZT013_FUNCTION                  out %1\%5\ZZT013_FUNCTION.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 48
BCP %4.DBO.ZZT014_POSITION                  out %1\%5\ZZT014_POSITION.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 49
BCP %4.DBO.ZZT015_STATUS                    out %1\%5\ZZT015_STATUS.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 50
BCP %4.DBO.ZZT016_AREA                      out %1\%5\ZZT016_AREA.txt                   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 51
BCP %4.DBO.ZZT017_MEDAL                     out %1\%5\ZZT017_MEDAL.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 52
BCP %4.DBO.ZZT018_MEDALLIST                 out %1\%5\ZZT018_MEDALLIST.txt              /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 53
BCP %4.DBO.ZZT019_REGTYPE                   out %1\%5\ZZT019_REGTYPE.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 54
BCP %4.DBO.ZZT020_EVENTRESULT               out %1\%5\ZZT020_EVENTRESULT.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 55
BCP %4.DBO.ZZT021_OFFICIAL                  out %1\%5\ZZT021_OFFICIAL.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 56
BCP %4.DBO.ZZT026_WEATHER_BASE              out %1\%5\ZZT026_WEATHER_BASE.txt           /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 57
BCP %4.DBO.ZZT027_MEDICAL_CLASS             out %1\%5\ZZT027_MEDICAL_CLASS.txt          /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 58
BCP %4.DBO.ZZT028_WEATHER                   out %1\%5\ZZT028_WEATHER.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 59
BCP %4.DBO.ZZT029_CLUB                      out %1\%5\ZZT029_CLUB.txt                   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 60
BCP %4.DBO.ZZT030_FEDERATION                out %1\%5\ZZT030_FEDERATION.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 61
BCP %4.DBO.ZZT031_COURT                     out %1\%5\ZZT031_COURT.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 62
BCP %4.DBO.ZZT032_SESSION                   out %1\%5\ZZT032_SESSION.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 63
BCP %4.DBO.ZZT040_RECORD                    out %1\%5\ZZT040_RECORD.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 64
BCP %4.DBO.ZZT041_TOP                       out %1\%5\ZZT041_TOP.txt                    /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 65
BCP %4.DBO.ZZT044_SPLIT_RECORD              out %1\%5\ZZT044_SPLIT_RECORD.txt           /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 66
BCP %4.DBO.ZZT045_TYPE_RECORD               out %1\%5\ZZT045_TYPE_RECORD.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 67
BCP %4.DBO.ZZT046_TYPE_TOP                  out %1\%5\ZZT046_TYPE_TOP.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 68
BCP %4.DBO.ZZT051_INSCRIPTION               out %1\%5\ZZT051_INSCRIPTION.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 69
BCP %4.DBO.ZZT052_MEMBER                    out %1\%5\ZZT052_MEMBER.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 70
BCP %4.DBO.ZZT053_PHASE                     out %1\%5\ZZT053_PHASE.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 71
BCP %4.DBO.ZZT055_EVENT_UNIT                out %1\%5\ZZT055_EVENT_UNIT.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 72
BCP %4.DBO.ZZT065_CODE_TRANSLATION          out %1\%5\ZZT065_CODE_TRANSLATION.txt       /n /c /w /C /U sa /S %3 /P %2
rem PAUSE

ECHO 73
BCP %4.DBO.ZZT004_DEFINITION                out %1\%5\ZZT004_DEFINITION.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 74
BCP %4.DBO.ZZT501_DISCIPLINE                out %1\%5\ZZT501_DISCIPLINE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 75
BCP %4.DBO.ZZT502_GENDER                    out %1\%5\ZZT502_GENDER.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 76
BCP %4.DBO.ZZT503_COUNTRY                   out %1\%5\ZZT503_COUNTRY.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 77
BCP %4.DBO.ZZT505_EVENT_UNIT_BASE           out %1\%5\ZZT505_EVENT_UNIT_BASE.txt        /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 78
BCP %4.DBO.ZZT506_VENUE                     out %1\%5\ZZT506_VENUE.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 79
BCP %4.DBO.ZZT507_CATEGORY                  out %1\%5\ZZT507_CATEGORY.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 80
BCP %4.DBO.ZZT509_QUALITATIVE               out %1\%5\ZZT509_QUALITATIVE.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 81
BCP %4.DBO.ZZT510_REGISTER                  out %1\%5\ZZT510_REGISTER.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 82
BCP %4.DBO.ZZT511_EVENT                     out %1\%5\ZZT511_EVENT.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 83
BCP %4.DBO.ZZT512_PHASE_BASE                out %1\%5\ZZT512_PHASE_BASE.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 84
BCP %4.DBO.ZZT513_FUNCTION                  out %1\%5\ZZT513_FUNCTION.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 85
BCP %4.DBO.ZZT514_POSITION                  out %1\%5\ZZT514_POSITION.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 86
BCP %4.DBO.ZZT515_STATUS                    out %1\%5\ZZT515_STATUS.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 87
BCP %4.DBO.ZZT516_AREA                      out %1\%5\ZZT516_AREA.txt                   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 88
BCP %4.DBO.ZZT517_MEDAL                     out %1\%5\ZZT517_MEDAL.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 89
BCP %4.DBO.ZZT519_REGTYPE                   out %1\%5\ZZT519_REGTYPE.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 90
BCP %4.DBO.ZZT526_WEATHER_BASE              out %1\%5\ZZT526_WEATHER_BASE.txt           /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 91
BCP %4.DBO.ZZT527_MEDICAL_CLASS             out %1\%5\ZZT527_MEDICAL_CLASS.txt          /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 92
BCP %4.DBO.ZZT529_CLUB                      out %1\%5\ZZT529_CLUB.txt                   /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 93
BCP %4.DBO.ZZT530_FEDERATION                out %1\%5\ZZT530_FEDERATION.txt             /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 94
BCP %4.DBO.ZZT531_COURT                     out %1\%5\ZZT531_COURT.txt                  /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 95
BCP %4.DBO.ZZT532_SESSION                   out %1\%5\ZZT532_SESSION.txt                /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 96
BCP %4.DBO.ZZT540_RECORD                    out %1\%5\ZZT540_RECORD.txt                 /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 97
BCP %4.DBO.ZZT541_TOP                       out %1\%5\ZZT541_TOP.txt                    /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 98
BCP %4.DBO.ZZT545_TYPE_RECORD               out %1\%5\ZZT545_TYPE_RECORD.txt            /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 99
BCP %4.DBO.ZZT546_TYPE_TOP                  out %1\%5\ZZT546_TYPE_TOP.txt               /n /c /w /C /U sa /P %3 /S %2
rem PAUSE
ECHO 100
BCP %4.DBO.ZZT565_CODE_TRANSLATION          out %1\%5\ZZT565_CODE_TRANSLATION.txt       /n /c /w /C /U sa /S %3 /P %2
rem PAUSE

