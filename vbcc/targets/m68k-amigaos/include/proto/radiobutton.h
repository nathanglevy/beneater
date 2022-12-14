#ifndef _PROTO_RADIOBUTTON_H
#define _PROTO_RADIOBUTTON_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_RADIOBUTTON_PROTOS_H) && !defined(__GNUC__)
#pragma stdargs-on
#include <clib/radiobutton_protos.h>
#pragma stdargs-off
#endif

#ifndef __NOLIBBASE__
extern struct Library *RadioButtonBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/radiobutton.h>
#else
#include <inline/radiobutton.h>
#endif
#elif defined(__VBCC__)
#ifndef _NO_INLINE
#include <inline/radiobutton_protos.h>
#endif
#else
#include <pragma/radiobutton_lib.h>
#endif

#endif	/*  _PROTO_RADIOBUTTON_H  */
