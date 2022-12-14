#ifndef _PROTO_DRAWLIST_H
#define _PROTO_DRAWLIST_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_DRAWLIST_PROTOS_H) && !defined(__GNUC__)
#pragma stdargs-on
#include <clib/drawlist_protos.h>
#pragma stdargs-off
#endif

#ifndef __NOLIBBASE__
extern struct Library *DrawListBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/drawlist.h>
#else
#include <inline/drawlist.h>
#endif
#elif defined(__VBCC__)
#ifndef _NO_INLINE
#include <inline/drawlist_protos.h>
#endif
#else
#include <pragma/drawlist_lib.h>
#endif

#endif	/*  _PROTO_DRAWLIST_H  */
