#ifndef _PROTO_CGXVIDEO_H
#define _PROTO_CGXVIDEO_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_CGXVIDEO_PROTOS_H) && !defined(__GNUC__)
#pragma stdargs-on
#include <clib/cgxvideo_protos.h>
#pragma stdargs-off
#endif

#ifndef __NOLIBBASE__
extern struct Library *CGXVideoBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/cgxvideo.h>
#else
#include <inline/cgxvideo.h>
#endif
#elif defined(__VBCC__)
#ifndef _NO_INLINE
#include <inline/cgxvideo_protos.h>
#endif
#else
#include <pragma/cgxvideo_lib.h>
#endif

#endif	/*  _PROTO_CGXVIDEO_H  */
