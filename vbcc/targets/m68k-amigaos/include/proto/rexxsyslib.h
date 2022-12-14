#ifndef _PROTO_REXXSYSLIB_H
#define _PROTO_REXXSYSLIB_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_REXXSYSLIB_PROTOS_H) && !defined(__GNUC__)
#pragma stdargs-on
#include <clib/rexxsyslib_protos.h>
#pragma stdargs-off
#endif

#ifndef __NOLIBBASE__
extern struct RxsLib *RexxSysBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/rexxsyslib.h>
#else
#include <inline/rexxsyslib.h>
#endif
#elif defined(__VBCC__)
#ifndef _NO_INLINE
#include <inline/rexxsyslib_protos.h>
#endif
#else
#include <pragma/rexxsyslib_lib.h>
#endif

#endif	/*  _PROTO_REXXSYSLIB_H  */
