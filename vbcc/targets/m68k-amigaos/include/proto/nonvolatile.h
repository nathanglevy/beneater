#ifndef _PROTO_NONVOLATILE_H
#define _PROTO_NONVOLATILE_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_NONVOLATILE_PROTOS_H) && !defined(__GNUC__)
#pragma stdargs-on
#include <clib/nonvolatile_protos.h>
#pragma stdargs-off
#endif

#ifndef __NOLIBBASE__
extern struct Library *NVBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/nonvolatile.h>
#else
#include <inline/nonvolatile.h>
#endif
#elif defined(__VBCC__)
#ifndef _NO_INLINE
#include <inline/nonvolatile_protos.h>
#endif
#else
#include <pragma/nonvolatile_lib.h>
#endif

#endif	/*  _PROTO_NONVOLATILE_H  */
