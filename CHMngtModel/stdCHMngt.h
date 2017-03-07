#ifndef __STDCH_H_
#define __STDCH_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable:4516)

#include <afxwin.h>
#include <afxmt.h> 

#ifndef __RWCOLLECT_H__
#	include <rw/collect.h>
#endif // __RWCOLLECT_H__

#ifndef __RWCSTRING_H__
#	include <rw/cstring.h>
#endif // __RWCSTRING_H__

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

#ifndef __RWDB_DB_H__
#	include <rw/db/db.h>
#endif // __RWDB_DB_H__

#ifndef __RWDB_CONNECT_H__
#	include <rw/db/connect.h>
#endif //__RWDB_CONNECT_H__

#ifndef __RWDB_COLLECT_H__
#	include <rw/db/collect.h>
#endif // __RWDB_COLLECT_H__

#ifndef __RWDB_DBMGR_H__
#	include <rw/db/dbmgr.h>
#endif // __RWDB_DBMGR_H__

#ifndef __RWDB_DATETIME_H__
#	include <rw/db/datetime.h>
#endif // __RWDB_DATETIME_H__

#include <CORE/G/QBASE.h>
#include <CORE/G/UBASE.h>
#include "CHMemoryDataBase.h"


#endif //__STDCH_H__