#ifndef _CHMNGTMODELDLL_H_
#define _CHMNGTMODELDLL_H_

#ifdef _CHMNGT_DLL
	#define CHModelExport  _declspec(dllexport)
#else
    #define CHModelExport  _declspec(dllimport)
#endif //_CHMNGT_DLL

#endif //_CHMNGTMODELDLL_H_
