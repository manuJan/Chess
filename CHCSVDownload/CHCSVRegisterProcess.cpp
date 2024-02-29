#include "StdAfx.h"
#include "CHCSVRegisterProcess.h"
#include <OVR/GUI/CSVDownLoad/CSVRegister.h>

int orderMemberBySex(const MSLItem** a, const MSLItem** b)
{
	GMember * pA = (GMember *)(*a);
	GMember * pB = (GMember *)(*b);

	//para dobles mixto se pone primero al hombre y despues a la mujer
	int order = _stricoll(pA->getSex(),pB->getSex());
	if ( order )
		return order;

	order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if ( order )
		return order;

	return pA->getRegCode() - pB->getRegCode();
}

int orderMemberByName(const MSLItem** a, const MSLItem** b)
{
	GMember * pA = (GMember *)(*a);
	GMember * pB = (GMember *)(*b);

	//para el resto de los eventos es por orden alfabatico de apellido
	int order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if ( order )
		return order;

	return pA->getRegCode() - pB->getRegCode();
}

//para buscar el campo

#define BIB			L"CH_SHIRT_NUMBER"		

CHCSVRegisterProcess::CHCSVRegisterProcess()
:CSVRegisterProcess()
{
}

CHCSVRegisterProcess::~CHCSVRegisterProcess()
{
}

MSLString CHCSVRegisterProcess::getDiscipline()
{
	return CHDefinition::getCode();
}

MSLString CHCSVRegisterProcess::getMedical(CSVRegister *pRegisterCSV)
{
/*	MSLString medical = pRegisterCSV->getValue("EVENT_CATEGORY",ATHLETE).toAscii();
	
	MSLString rem = medical, oMedical, medicalClass;
	//ITT1 Seated, ITT2 Seated, ITT3 Seated, ITT4 Standing, ITT5 Standing, ITT6 Standing,  ITT7 Standing
	//por ;
	while (rem.tok(";",oMedical,rem))
	{
		//por ' '
		MSLString remM = oMedical;
		while (remM.tok(" ",medicalClass,remM))
		{
			if (medicalClass.length()>=3 || medicalClass.length()<=4)
				return medicalClass;
		}
	}
*/
	return CSVRegisterProcess::getMedical(pRegisterCSV);
}

MSLString CHCSVRegisterProcess::getEventGender(MSLWString ic_sport, MSLWString ic_eventCode, MSLWString ic_genderCode)
{
/*	MSLString eventGenderCode = CSVRegisterProcess::getEventGender(ic_sport,ic_eventCode,ic_genderCode);
	if (ic_eventCode=="401")
		eventGenderCode = "X";

	return eventGenderCode;*/
	return CSVRegisterProcess::getEventGender(ic_sport,ic_eventCode,ic_genderCode);
}

void CHCSVRegisterProcess::onCreateTeam(CSVRegister *pRegisterCSV,GRegister *pRegister)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pRegister);
}

GInscription *CHCSVRegisterProcess::createDoubleInscription(CSVRegister *pRegisterCSV,GRegister * pRegister,GEvent * pEvent)
{
/*	GInscription * pNewInscription=0;
		
	if(pEvent)
	{
		GRegister * pDoublesRegister= getDoubleRegister(pEvent,getNOC(pRegisterCSV,ATHLETE));	
		if(!pDoublesRegister)
			pDoublesRegister=createDouble(pRegisterCSV);

		onCreateDouble(pRegisterCSV,pDoublesRegister);

		if(!pDoublesRegister)
			return 0;

		bool fromMember = getCreateTeamsAndMembers(); //true si pRegisterCSV es el de un Member, no el del Team
		if (/*fromMember && *//*pDoublesRegister->getSex() != pEvent->getSex()) //si estamos creando el register del Team a partir de un pRegisterCSV de member y el evento es mixto hay que cambiar el gender del Team register
			pDoublesRegister->setSex(pEvent->getSex());


		pNewInscription=GMemoryDataBase::findInscription(pDoublesRegister,pEvent);
		//Si tengo un evento con el mismo numero de miembros creo otro
		if(!pNewInscription || pNewInscription->getMembers().entries()==pEvent->getTeamMembers())
		{
			GInscription * pInscription=(GInscription*)APP::mem()->onNew(__GINSCRIPTION);
			if(pInscription)
			{
				pInscription->setEvent(pEvent);
				pInscription->setRegister(pDoublesRegister);

				pNewInscription=(GInscription*)APP::mem()->set(*pInscription);

				delete pInscription;

				checkAccreditation(pDoublesRegister,pEvent); //para poner el evento en el que participa el equipo en la accreditation

				onCreateDoubleInscription(pRegisterCSV,pNewInscription);

				//EventResult
				createEventResult(pRegisterCSV,pNewInscription);
			}
		}

		//member
		createMember(pRegisterCSV,pRegister,pDoublesRegister);
		//tengo que ordenar y tengo que poner el nombre compuesto en el registro
		if (pDoublesRegister && pDoublesRegister->getMembers().entries()==pEvent->getTeamMembers())
		{
			MSLSortedVector vMembers;
			if ( (pDoublesRegister->getType() == CHRegister::doubles || pDoublesRegister->getType() == CHRegister::team) &&
				pDoublesRegister->getSex() != MIXED )
				pDoublesRegister->getMembersVector(vMembers,orderMemberByName);
			else if ( (pDoublesRegister->getType() == CHRegister::doubles || pDoublesRegister->getType() == CHRegister::team) &&
				pDoublesRegister->getSex() == MIXED )
				pDoublesRegister->getMembersVector(vMembers,orderMemberBySex);

			int nMember=1;
			int nTeamMember=50;

			CHMember * pMember=0;
			for(int i=0; i<vMembers.entries() ; i++)
			{
				pMember=(CHMember*)vMembers[i];

				if(pMember->getType()==GRegister::teamOfficial)
					pMember->setOrder(short(nTeamMember++));
				else
					pMember->setOrder(short(nMember++));
			}

			MSLSetIterator it(CHMemoryDataBase::getCol(__GLANGUAGE));
			GLanguage *pLanguage = 0;
			while( ( pLanguage = (GLanguage *)it() ) != 0 )
			{
//				if ( pLanguage->getNamesFlag() )
//					composeDoublesName((CHRegister *)pDoublesRegister,pLanguage->get().data());
			}
		}
	}

	return pNewInscription;*/
	return CSVRegisterProcess::createDoubleInscription(pRegisterCSV,pRegister,pEvent);
}

void CHCSVRegisterProcess::onCreateDouble(CSVRegister *pRegisterCSV,GRegister *pRegister)
{
/*	if (!pRegisterCSV || !pRegister)
		return;

	//Meto las clases médicas en el registro del equipo
	MSLString medicalClassTeam(NULLSTRING);
	MSLString medicalClassCSV = getMedical(pRegisterCSV);
	MSLString medicalClassT = pRegister->getMedicalClass();
	int index = medicalClassT.index(medicalClassCSV);
	if (index<0)
	{
		if (medicalClassT.length()>0)
			medicalClassTeam = medicalClassT + "," + medicalClassCSV;
		else
			medicalClassTeam = medicalClassCSV;

		pRegister->setMedicalClass(medicalClassTeam.data());
	}*/

	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pRegister);
}

void CHCSVRegisterProcess::onCreateAthlete(CSVRegister *pRegisterCSV,GRegister *pRegister)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pRegister);
}

void CHCSVRegisterProcess::onCreateMember(CSVRegister *pRegisterCSV,GMember *pMember)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pMember);
}

void CHCSVRegisterProcess::onCreateReferee(CSVRegister *pRegisterCSV,GRegister *pRegister)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pRegister);
}

void CHCSVRegisterProcess::onCreateOfficial(CSVRegister *pRegisterCSV,GOfficial *pOfficial)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pOfficial);
}

void CHCSVRegisterProcess::onCreateTeamOfficial(CSVRegister *pRegisterCSV,GRegister *pRegister)
{
	UNREFERENCED_PARAMETER(pRegisterCSV);
	UNREFERENCED_PARAMETER(pRegister);
}

GEvent *CHCSVRegisterProcess::getEventInscription(CSVRegister *pRegisterCSV,MSLWString columnEventName,MSLWString columnGenderName,MSLWString eventCategory)
{
	//buscamos en el dictionary LinkDataCommonCodes:
	//1º-Discipline Code + Gender Code + Event Code									3,CTRMPURSUIT-----------,014,CTR-4000m IND PURSUIT MEN
	//2º-Si no lo encontramos lo buscamos sin gender								3,CTRPURSUIT-----------,014,CTR-4000m IND PURSUIT MEN	
	//3º-Si no lo encontramos lo buscamos sin disciplina y con gender				3,MPURSUIT-----------,014,CTR-4000m IND PURSUIT MEN
	//4º-Si no lo encontramos lo buscamos sin disciplina y sin gender				3,PURSUIT-----------,014,CTR-4000m IND PURSUIT MEN	

	//sport codes
	MSLWString ic_sport =  getDiscipline(); //codigo interno de deporte TR
	MSLWString cc_sport =  pRegisterCSV->getCommonCode(DISCPLINE,ic_sport); //common code del deporte TRI
	//gender codes
	MSLWString cc_genderCode = pRegisterCSV->getValue(columnGenderName,ATHLETE); //common code del gender 
	MSLWString cc_genderCodeFromColumn = cc_genderCode; //hacemos una copia por si luego tenemos que sacar un error en el log
	if (cc_genderCode == NULLSTRING) //si el evento no tiene columna gender asociada miramos el gender del propio athleta
		cc_genderCode = pRegisterCSV->getValue(GENDER,ATHLETE);
	MSLWString ic_genderCode = pRegisterCSV->getInternalCode(GENDERTYPE,cc_genderCode); //internal code que corresponde al common code del gender
	if (ic_genderCode == NULLSTRING) //si no lo encontramos en el dictionary suponemos que no hay que traducirlo
		ic_genderCode = cc_genderCode;
	//en eventCategory tenemos mixed y el sexo del evento que tenemos no es mixto
	MSLWString ec = eventCategory;
	ec.toUpper();
	if (ec.index("MIXED")>=0 && ic_genderCode!=MIXED)
		ic_genderCode = MIXED;

	//event codes
	//MSLWString cc_eventCode = pRegisterCSV->getValue("EVENT_CATEGORY",ATHLETE); //Invictus
	MSLWString cc_eventCode = eventCategory;
	cc_eventCode += pRegisterCSV->getValue(columnEventName,ATHLETE);
	
	MSLWString ic_eventCode = pRegisterCSV->getInternalCode(EVENT,cc_sport + cc_genderCode + cc_eventCode); 
	//si no encontramos lo buscamos con disciplina y sin gender
	if (ic_eventCode == NULLSTRING)
		ic_eventCode = pRegisterCSV->getInternalCode(EVENT,cc_sport + cc_eventCode);
	//si no encontramos lo buscamos sin disciplina y con gender
	if (ic_eventCode == NULLSTRING)
		ic_eventCode = pRegisterCSV->getInternalCode(EVENT,cc_genderCode + cc_eventCode);
	//si no encontramos lo buscamos solo con el event 
	if (ic_eventCode == NULLSTRING)
		ic_eventCode = pRegisterCSV->getInternalCode(EVENT,cc_eventCode);
	
	//buscamos un evento con el event code y el gender code que acabamos de encontrar
	MSLString gender = getEventGender(ic_sport, ic_eventCode, ic_genderCode);
//	MSLString gender = ic_genderCode.toAscii();
//	if((ic_sport == "AT" && ic_eventCode=="4X14X1") || (ic_sport == "SW" && ic_eventCode=="911") || (ic_sport == "TT" && ic_eventCode=="203") || (ic_sport == "TT" && ic_eventCode=="207") || ic_sport == "WY" || ic_sport == "BK" || ic_sport == "VO")
//		gender = "X";

	GEvent *pEvent=(GEvent*)GMemoryDataBase::findEvent(ic_eventCode.toAscii(), gender);
	
	//si seguimos sin encontrar el codigo interno de evento puede ser porque estemos buscando un evento mixto?
	//if (!pEvent && getCreateTeamsAndMembers()) //si estamos creando nosotros los teams y los members y no encontramos event con el gender del registro csv puede ser que sea porque el evento es mixto
	//	pEvent=(GEvent*)GMemoryDataBase::findEvent(ic_eventCode.toAscii(),MIXED);

	if (!pEvent)
	{
		if (cc_genderCodeFromColumn != "" && cc_eventCode != "") //vienen las 2 columnas del evento rellenas en el excel: event code y gender event code
		{
			if (cc_sport == "")
				::logW(LOG_DOWN_LOAD,L"Sport code not found for internal code (" + MSLWString(ic_sport) + L") PeopleID: " + pRegisterCSV->getValue(ACREDITATION,ATHLETE) + L" " +  pRegisterCSV->getValue(NAME,ATHLETE) + L" " + pRegisterCSV->getValue(SURNAME,ATHLETE) + L" from " + pRegisterCSV->getValue(NOC_CODE,ATHLETE));
			if (ic_genderCode == "") //si no hemos podido traducir el gender del evento
				::logW(LOG_DOWN_LOAD,L"Invalid event gender code (" + MSLWString(cc_genderCode) + L") PeopleID: " + pRegisterCSV->getValue(ACREDITATION,ATHLETE) + L" " +  pRegisterCSV->getValue(NAME,ATHLETE) + L" " + pRegisterCSV->getValue(SURNAME,ATHLETE) + L" from " + pRegisterCSV->getValue(NOC_CODE,ATHLETE));
			if (ic_eventCode = "") //si no hemos podido traducir el codigo del evento
				::logW(LOG_DOWN_LOAD,L"Invalid event code (" + MSLWString(cc_eventCode) + L") PeopleID: " + pRegisterCSV->getValue(ACREDITATION,ATHLETE) + L" " +  pRegisterCSV->getValue(NAME,ATHLETE) + L" " + pRegisterCSV->getValue(SURNAME,ATHLETE) + L" from " + pRegisterCSV->getValue(NOC_CODE,ATHLETE));
		}
		else if (cc_genderCodeFromColumn != "" && cc_eventCode == "") //el event code esta vacio
			::logW(LOG_DOWN_LOAD,L"Empty event code for (" + MSLWString(columnEventName) + L") PeopleID: " + pRegisterCSV->getValue(ACREDITATION,ATHLETE) + L" " +  pRegisterCSV->getValue(NAME,ATHLETE) + L" " + pRegisterCSV->getValue(SURNAME,ATHLETE) + L" from " + pRegisterCSV->getValue(NOC_CODE,ATHLETE));
		else if (cc_genderCodeFromColumn == "" && cc_eventCode != "") //el gender evento code esta vacio
			::logW(LOG_DOWN_LOAD,L"Empty gender event code for (" + MSLWString(columnGenderName) + L") PeopleID: " + pRegisterCSV->getValue(ACREDITATION,ATHLETE) + L" " +  pRegisterCSV->getValue(NAME,ATHLETE) + L" " + pRegisterCSV->getValue(SURNAME,ATHLETE) + L" from " + pRegisterCSV->getValue(NOC_CODE,ATHLETE));
	}

	return pEvent;
//	return CSVRegisterProcess::getEventInscription(pRegisterCSV,columnEventName,columnGenderName,eventCategory);
}

GRegister *CHCSVRegisterProcess::getDoubleRegister(GEvent *pEvent,const char *NOC)
{
/*	if(pEvent)
	{
		MSLSetIterator iter(GMemoryDataBase::getCol(__GINSCRIPTION));

		GInscription * pInscription=0;
		while((pInscription=(GInscription*)iter())!=0)
		{
			if(pInscription->getEvent()==pEvent && pInscription->getGroup()==NOC && 
				pInscription->getRegister()->getMembers().entries()<pEvent->getTeamMembers())
				return pInscription->getRegister();
		}
	}

	return 0;*/
	return CSVRegisterProcess::getDoubleRegister(pEvent,NOC);
}

void CHCSVRegisterProcess::composeDoublesName(CHRegister *pDoublesRegister,const char *language/* = 0*/,bool erase/* = false*/)
{
	if( !pDoublesRegister )
		return;

	if( pDoublesRegister->getType() != GRegister::doubles )
		return;

	MSLSortedVector vMember;
	pDoublesRegister->getMembersVector(vMember);

	MSLWString blank=L" ";
	MSLWString slash=L"/";
  	MSLWString auxText1;
  	MSLWString auxTextLong1;
  	MSLWString auxTextLong2;
	MSLWString auxTextTVLName;
	
	for( size_t i = 0 ; i < size_t(vMember.entries()); i++ )
	{
		CHMember * pMember =(CHMember*) vMember[i];
		if( pMember )
		{
			CHRegister * pRegister = (CHRegister*)pMember->getRegister();
			if( pRegister && pRegister->getType() == GRegister::individual )
			{
				if( i != 0 )
				{
					auxText1 += slash;
					auxTextLong1 += slash;
					auxTextLong2 += slash;
					auxTextTVLName += slash;
				}

				if ( MSLString(language) != "CHN" )
				{
					auxText1 += pMember->getName2(language);
					MSLWString aux1 = pMember->getName2(language);
					aux1.toUpper();
					auxTextLong1 += aux1;
					auxTextLong1 += blank;
					auxTextLong1 +=(pMember->getName1(language)(0,1) + L".");
					int posBlank = aux1.index(blank,0);
					auxTextLong2 += (posBlank>0)?aux1.after(blank,posBlank):aux1;
					auxTextLong2 += blank;
					auxTextLong2 += (pMember->getName1(language)(0,1) + L".");

					// Limite de 21 caracteres Paris 2024 => Defecto 282259 Cracovia
					auxTextTVLName += pMember->getName2(language)(0,10);
					auxTextTVLName.toUpper();
				}
				else
				{
//					auxText1 += pMember->getName2(language);
//					MSLWString aux1 = pMember->getName2(language);
//					aux1.toUpper();
//					auxTextLong1 += aux1;
//					auxTextLong1 += blank;
//					auxTextLong1 += pMember->getName1(language);
//					auxTextLong2 += aux1;
//					auxTextLong2 += blank;
//					auxTextLong2 += pMember->getName1(language);
					auxText1 += pMember->getName2(language);
					MSLWString aux1 = pMember->getName2(language);
					aux1.toUpper();
					auxTextLong1 += aux1;
					auxTextLong2 += aux1;

					// Limite de 21 caracteres Paris 2024 => Defecto 282259 Cracovia
					auxTextTVLName += pMember->getName2(language)(0,10);
					auxTextTVLName.toUpper();
				}
			}
		}
		auxText1.toUpper();
	}
	// Limite de 35 caracteres
	MSLWString auxTextLong = (auxTextLong1.length() > 35) ? auxTextLong2(0,35) : auxTextLong1;

//	TTRegister *pReg = (TTRegister *)pInscription->getRegister();
	
	GDescription newDesc;
	newDesc.set(language/*GUtils::getAppLang()*/);
	newDesc.set(_NAME   ,L"");
	newDesc.set(_SURNAME,L"");
	newDesc.set(_LMC    ,L"");
	newDesc.set(_LPRN   ,L"");
	newDesc.set(_SPRN   ,L"");
	newDesc.set(_LSCB   ,L"");
	newDesc.set(_SSCB   ,L"");
	newDesc.set(_LTV    ,L"");
	newDesc.set(_STV    ,L"");
	//Si borramos o los miembors son dos o menos
	if ( erase || vMember.entries()!= 2 )
		newDesc.set(_SURNAME,pDoublesRegister->getGroupLDescription(language));
	else
		newDesc.set(_SURNAME,auxTextLong);

	GUtils::namesCalculate(newDesc,language/*pInscription->getGroup()*/);

	// Limite de 21 caracteres Paris 2024 => Defecto 282259 Cracovia
	newDesc.set(_LTV,auxTextTVLName(0,21));

	GDescription desc = pDoublesRegister->getDescriptions()[language/*0*/];
	//salvo a base de datos y repinto el arbol y los datos
	if ( desc != newDesc )
	{
		pDoublesRegister->setDescription(newDesc);
	}
}
