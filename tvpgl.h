
#pragma once

#include "tjsCommHead.h"

#define TVPConvertAlphaToAdditiveAlpha TVPConvertAlphaToAdditiveAlpha_c
#define TVPConvertAdditiveAlphaToAlpha TVPConvertAdditiveAlphaToAlpha_c

#define TVP_INLINE_FUNC inline
#define TVP_GL_FUNCNAME(funcname) funcname
#define TVP_GL_FUNC_DECL(rettype, funcname, arg)  rettype TVP_GL_FUNCNAME(funcname) arg
#define TVP_GL_FUNC_STATIC_DECL(rettype, funcname, arg)  static rettype TVP_GL_FUNCNAME(funcname) arg
#define TVP_GL_FUNC_INLINE_DECL(rettype, funcname, arg)  static rettype TVP_INLINE_FUNC TVP_GL_FUNCNAME(funcname) arg
#define TVP_GL_FUNC_EXTERN_DECL(rettype, funcname, arg)  extern rettype TVP_GL_FUNCNAME(funcname) arg
#define TVP_GL_FUNC_PTR_EXTERN_DECL TVP_GL_FUNC_EXTERN_DECL

TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConvertAlphaToAdditiveAlpha,  (tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConvertAdditiveAlphaToAlpha,  (tjs_uint32 *buf, tjs_int len));
