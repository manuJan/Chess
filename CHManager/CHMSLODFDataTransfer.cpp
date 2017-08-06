#include "StdAfx.h"
#include "CHMSLODFDataTransfer.h"
#include "CHODFLoadRegister.h"
#include "CHODFLoadInscription.h"

CHMSLODFDataTransfer::CHMSLODFDataTransfer(long id)
:MSLIPCTHDataTransferModule(id)
{
}


CHMSLODFDataTransfer::~CHMSLODFDataTransfer(void)
{
}

ODFLoadRegister* CHMSLODFDataTransfer::onNewODFLoadRegister(GRegister* pRegister)
{
	return new CHODFLoadRegister(pRegister, this);
}

ODFLoadInscription*	CHMSLODFDataTransfer::onNewODFLoadInscription(GInscription* pInscription)
{
	return new CHODFLoadInscription(pInscription, this);
}

void CHMSLODFDataTransfer::onCreateInscription(GInscription* pInscription)
{
	MSLIPCTHDataTransferModule::onCreateInscription(pInscription);
}

void CHMSLODFDataTransfer::onCreateEventResult(GEventResult * pEvResult)
{
	MSLIPCTHDataTransferModule::onCreateEventResult(pEvResult);

	pEvResult->setQualitative(OK);
}