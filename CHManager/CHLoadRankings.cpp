#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHLoadRankings.h"

#include <ovr\core\th\GTHMsgDefines.h>
#include <ovr/gui/guimanager/GFileDialog.h>
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"


CHLoadRankings::CHLoadRankings(CHPool* pPool)
:m_pPool(pPool)
{
	m_elems = pPool->getPoolResults();
}


CHLoadRankings::~CHLoadRankings(void)
{
}

MSLString	CHLoadRankings::processFile(MSLWString path)
{
	MSLString info;

	// Leo el fichero
	MSLFile readfile(path);
	if (!readfile.openR())
	{
		return "Can't open the file";
	}

	MSLBinary bin = readfile.read();
	MSLString content = bin.buffer();
	MSLString line; MSLString tab = "\n";
	short idx = 1;
	while ( content.tok(tab,line,content) )
	{
		if (!processLine(line, idx))
			info += "Error on line " + TOSTRING(idx) + "\n";
		idx++;
	}
	doOut();
	if (info=="")
		info = "file processed OK!";
	return info;
}
void		CHLoadRankings::doOut()
{
	MSLSetIterator it(m_elems);
	GData* pData;
	while ((pData = (GData*) it())!=0 )
	{
		APP_CH::out(*pData);
	}
	APP_CH::out(TRN_SET_POOLRESULT);
}

	
bool		CHLoadRankings::processLine(MSLString& line, short rkPo)
{
	// TAB file
	//rk1,seed2,categ3,name4,NOC5,irtg6,pts7,RES8,BH9,BH10,vict11,SB12
	MSLString field; MSLString tab = "\t";
	short count = 1;
	CHPoolResult* pRes = 0;
	short rank;
	double buchholtz1, buchholtz2,sonneborn;
	while ( line.tok(tab,field,line) )
	{
		switch (count)
		{
		case 1: // ranking
			{
				if (field=="")
					rank = m_lastRk;
				else
				{
					rank = (short) atoi(field);
					m_lastRk = rank;
				}
				break;
			}
		case 2: // seed
			{
				short seed = (short) atoi(field);
				pRes = findResult(seed,true);
				break;
			}
		case 6:
			{
				if (!pRes)
					pRes = findResult((short)atoi(field),false);
				if (!pRes)
					return false;
				break;
			}
		case 5:
			{
				if (pRes->getGroup()!=field)
					return false;
				break;
			}
		case 8: // direct encounter
			{
				break;
			}
		case 9: //buch-holtz 1
			{
				buchholtz1 = atof(field);
				break;
			}
		case 10: //buch-holtz 2
			{
				buchholtz2 = atof(field);
				break;
			}
		case 11: //victories
			{
				break;
			}
		case 12: // Sonneborn-Berger
			{
				sonneborn = atof(field);
				break;
			}
		}
		count++;
	}
	if (pRes)
	{
		pRes->setRank(rank);
		pRes->setRankPo(rkPo);
	}
	return pRes!=0;
}

CHPoolResult*	CHLoadRankings::findResult(short value, bool isSeed)
{
	MSLSetIterator it(m_elems);
	CHPoolResult* pRes = 0;
	while ( (pRes = (CHPoolResult*) it())!=0 )
	{
		CHInscription* pInsc =  (CHInscription*) pRes->getInscription();
		if (pInsc)
		{
			if (isSeed && pInsc->getSeed()==value)
				return pRes;
			if (!isSeed && pInsc->getRating()==value)
				return pRes;
		}			
	}
	return pRes;
}

void		CHLoadRankings::browseFile			(HWND handle)
{
	GFileDialog aFileDlg(handle,L"csv",L"*.csv",L"CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0\0" );
	int rc = aFileDlg.DoModal(GFileDialog::eRead);
	if( rc != 1 )
		return;

	MSLString info = processFile(aFileDlg.getFileName());
	MSLMsgBox(handle, info, GUI_ICO_INFORMATION, GUI_MB_OK);	
}
