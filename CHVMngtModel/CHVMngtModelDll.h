
#ifndef _CHVMNGTDLL_H
#define _CHVMNGTDLL_H	1

#ifdef _CHVMNGT_DLL
#	define CHVMngtExport _declspec(dllexport)
#else
#	define CHVMngtExport _declspec(dllimport)
#endif //_CHVMNGT_DLL

#endif //_CHVMNGTDLL_H
