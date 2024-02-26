#pragma once
#include <OVR/GUI/CSVDownLoad/CSVRegisterProcess.h>

class CHCSVRegisterProcess : public CSVRegisterProcess
{
public:
	CHCSVRegisterProcess();
	virtual ~CHCSVRegisterProcess();

	GInscription *createDoubleInscription(CSVRegister *pRegisterCSV,GRegister *pRegister,GEvent *pEvent);

	void onCreateTeam(CSVRegister *pRegisterCSV,GRegister *pRegister);
	void onCreateDouble(CSVRegister *pRegisterCSV,GRegister *pRegister);
	void onCreateAthlete(CSVRegister *pRegisterCSV,GRegister *pRegister);
	void onCreateMember(CSVRegister *pRegisterCSV,GMember *pMember);
	void onCreateReferee(CSVRegister *pRegisterCSV,GRegister *pRegister);
	void onCreateOfficial(CSVRegister *pRegisterCSV,GOfficial *pOfficial);
	void onCreateTeamOfficial(CSVRegister *pRegisterCSV,GRegister *pRegister);

	//discipline code
	MSLString getDiscipline();
	MSLString getMedical(CSVRegister *pRegisterCSV);
	MSLString getEventGender(MSLWString ic_sport, MSLWString ic_eventCode, MSLWString ic_genderCode);

	GRegister *getDoubleRegister(GEvent *pEvent,const char *NOC);			//Sport

	void composeDoublesName(CHRegister *pRegister,const char *language = 0,bool erase = false);
};

