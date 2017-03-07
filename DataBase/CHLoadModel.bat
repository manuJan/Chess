@REM de TXT a DATABASE

@rem parametro 1:	ruta	 (usualmente .)
@rem parametro 2:	servidor (usualmente srv_dbase1)
@rem parametro 3:	clave	 (usualmente msl)
@rem parametro 4:	deporte	 (usualmente chess)

BCP %4.DBO.CHT000_DEFINITION          	in %1\data\CHT000_DEFINITION.txt          /n /c /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZCH010_REGISTER           	in %1\data\ZCH010_REGISTER.txt            /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH510_REGISTER            	in %1\data\ZCH510_REGISTER.txt            /n /c /C ACP /w /U sa /P %3 /S %2
BCP %4.DBO.CHT001_INSCRIPTION         	in %1\data\CHT001_INSCRIPTION.txt         /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.CHT002_MEMBER              	in %1\data\CHT002_MEMBER.txt              /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.CHT020_EVENTRESULT         	in %1\data\CHT020_EVENTRESULT.txt         /n /c /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZCH009_QUALITATIVE         	in %1\data\ZCH009_QUALITATIVE.txt         /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH509_QUALITATIVE         	in %1\data\ZCH509_QUALITATIVE.txt         /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH011_EVENT               	in %1\data\ZCH011_EVENT.txt               /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH511_EVENT               	in %1\data\ZCH511_EVENT.txt               /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH012_PHASE               	in %1\data\ZCH012_PHASE.txt               /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH512_PHASE               	in %1\data\ZCH512_PHASE.txt               /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.ZCH031_COURT               	in %1\data\ZCH031_COURT.txt               /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH531_COURT               	in %1\data\ZCH531_COURT.txt               /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.CHT068_TEAM_MATCH_CNFG     	in %1\data\CHT068_TEAM_MATCH_CNFG.txt     /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.CHT568_TEAM_MATCH_CNFG     	in %1\data\CHT568_TEAM_MATCH_CNFG.txt     /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.CHT064_MASTER_TYPE     	in %1\data\CHT064_MASTER_TYPE.txt     /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.CHT564_MASTER_TYPE     	in %1\data\CHT564_MASTER_TYPE.txt     /n /c /C ACP /w /U sa /P %3 /S %2

BCP %4.DBO.CHT062_RATING_DIF     	in %1\data\CHT062_RATING_DIF.txt     /n /c /C ACP /U sa /P %3 /S %2


BCP %4.DBO.ZCH023_MODALITY_PHASE      	in %1\data\ZCH023_MODALITY_PHASE.txt      /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH024_ROUND               	in %1\data\ZCH024_ROUND.txt               /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH028_PROG_POOL_POSITION  	in %1\data\ZCH028_PROG_POOL_POSITION.txt  /n /c /C ACP /U sa /P %3 /S %2
BCP %4.DBO.ZCH029_PROG_MATCH_POSITION 	in %1\data\ZCH029_PROG_MATCH_POSITION.txt /n /c /C ACP /U sa /P %3 /S %2

BCP %4.DBO.ZZT037_STATISTIC 		in %1\Data\ZZT037_STATISTIC.txt /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT040_ECPLAY 		in %1\data\ZZT040_ECPLAY.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT041_ECPLAYDATA 		in %1\data\ZZT041_ECPLAYDATA.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT042_ECEVENT 		in %1\data\ZZT042_ECEVENT.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT043_ECSTATISTIC 		in %1\data\ZZT043_ECSTATISTIC.txt  /n /c /U sa /P %3 /S %2
BCP %4.DBO.ZZT044_ECRELATION 		in %1\data\ZZT044_ECRELATION.txt  /n /c /U sa /P %3 /S %2

BCP %4.DBO.ZZT027_MEDICAL_CLASS       	in %1\data\ZZT027_MEDICAL_CLASS.txt /n /c /C ACP /U sa /P %3 /S %2
