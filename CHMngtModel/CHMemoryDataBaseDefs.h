#ifndef _CHMEMORYDATABASEDEFS_H__
#define _CHMEMORYDATABASEDEFS_H__	1

#include <OVR/CORE/TH/GTHMemoryDataBaseDefs.h>


#ifdef CHMNGTMODEL_EXPORTS
#	define CHMngtModelExport  _declspec(dllexport)
#else
#	define CHMngtModelExport  _declspec(dllimport)
#endif //CHMNGTMODEL_EXPORTS

// 
// Identificadores de clases (isA)
//

#define __CHDEFINITION			__GTHDEFINITION
#define __CHEVENT				__GTHEVENT
#define __CHPHASE				__GTHPHASE
#define __CHPHASEBASE			__GTHPHASEBASE
#define __CHSPLITPHASE			__GTHSPLITPHASE
#define __CHPOOL				__GTHPOOL
#define __CHMATCH				__GTHMATCH
#define __CHMATCHRESULT			__GTHMATCHRESULT
#define __CHSPLITMATCH			__GTHSPLITMATCH
#define __CHSPLITMATCHRESULT	__GTHSPLITMATCHRESULT
#define __CHEVENTRESULT			__GEVENTRESULT
#define __CHPOOLRESULT			__GTHPOOLRESULT
#define __CHREGISTER			__GREGISTER
#define __CHINSCRIPTION			__GTHINSCRIPTION
#define __CHMEMBER				__GMEMBER
#define __CHMODALITYPHASE		__GTHMODALITYPHASE
#define __CHMODALITYSPLITPHASE	__GTHMODALITYSPLITPHASE
#define __CHMODALITY			__GTHMODALITY
#define __CHCOURT				__GCOURT

#define	__CHMASTERTYPE				2000
#define	__CHTEAMMATCHSCNFG			2001
#define	__CHRATINGDIF				2002

// 
// Chess Database Tables
//

#define CHT_MASTER_TYPE				"ZCH064_MASTER_TYPE"
#define CHT_MASTER_TYPEL			"ZCH564_MASTER_TYPE"
#define CHT_RATING_DIF				"ZCH062_RATING_DIF"
#define CHT_TEAM_MATCH_CNFG			"ZCH068_TEAM_MATCH_CNFG"
#define CHT_TEAM_MATCH_CNFGL		"ZCH568_TEAM_MATCH_CNFG"

// Qualitatives
#define	DSQ							"d"
#define	FO							"f"
#define	RET							"r"
#define OK							"0"

// Phase Codes
#define SWISS_ROUND					"9"
#define SEMIFINAL					"2"
#define GOLD_MEDAL					"1"
#define BRONZE_MEDAL				"B"

// Points 
#define WIN_POINTS					1
#define DRAW_POINTS					0.5
#define LOST_POINTS					0

#define WIN_POINTS_MEMBER			2
#define DRAW_POINTS_MEMBER			1
#define LOST_POINTS_MEMBER			0

//Aplicaciones
#define APP_CIS			500
#define APP_TV			501
#define APP_IDS			502
#define APP_SCB			503
#define APP_MNG			504
#define APP_ALL			505
#define APP_GDF			506
#define APP_CRS			507


////////////////////////////////////////////////////////////
//lo pasare al memoryDB?????
//del RSC traducido la parte que se quiere
#define RSC_ALL				0	
#define	RSC_GENDER			1
#define RSC_SEX				2	
#define RSC_EVENT			3	
#define RSC_PHASE			4
#define RSC_POOL			5
#define RSC_UNIT			6


#endif