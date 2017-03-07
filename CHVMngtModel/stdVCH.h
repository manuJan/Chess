#ifndef __STDVCH_H__
#define __STDVCH_H__	1

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxwin.h>
#include <afxmt.h> 

#pragma warning( disable : 4516 )

#ifndef __RWCOLLECT_H__
#	include <rw/collect.h>
#endif // __RWCOLLECT_H__

#ifndef __RWCSTRING_H__
#	include <rw/cstring.h>
#endif // __RWCSTRING_H__

#ifndef __RWCOLLSTR_H__
#	include <rw/collstr.h>
#endif // __RWCOLLSTR_H__

#ifndef __RWCOLCLASS_H__
#	include <rw/colclass.h>
#endif // __RWCOLCLASS_H__

#ifndef __RWSET_H__
#	include <rw/rwset.h>
#endif // __RWSET_H__

#ifndef __RWORDCLTN_H__
#	include <rw/ordcltn.h>
#endif // __RWORDCLTN_H__

#ifndef __RWSORTVEC_H__
#	include <rw/sortvec.h>
#endif // __RWSORTVEC_H__

#include <core/G/GModelView.h>
#include <Sports/CH/Data/CHMemoryDatabase.h>
#include <Reports/V/ReportView.h>
#include <Reports/V/ReportTemplate.h>
#include <Reports/V/ReportManager.h>
#include <Reports/V/ReportConfig.h>

#endif // __STDVCH_H__
