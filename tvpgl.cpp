// Copied tvpgl functions, because we can't rely on the core to have them.

#include "tvpgl.h"
#include "DivTable.h"

TVP_GL_FUNC_INLINE_DECL(tjs_uint32, TVPMulColor, (tjs_uint32 color, tjs_uint32 fac))
{
	return (((((color & 0x00ff00u) * fac) & 0x00ff0000u) +
			(((color & 0xff00ffu) * fac) & 0xff00ff00u) ) >> 8u);
}

TVP_GL_FUNC_INLINE_DECL(tjs_uint32, TVPAlphaAndColorToAdditiveAlpha, (tjs_uint32 alpha, tjs_uint32 color))
{
	return TVP_GL_FUNCNAME(TVPMulColor)(color, alpha) + (color & 0xff000000u);
}

TVP_GL_FUNC_INLINE_DECL(tjs_uint32, TVPAlphaToAdditiveAlpha, (tjs_uint32 a))
{
	return TVP_GL_FUNCNAME(TVPAlphaAndColorToAdditiveAlpha)(a >> 24u, a);
}

TVP_GL_FUNC_DECL(void, TVPConvertAlphaToAdditiveAlpha_c, (tjs_uint32 *buf, tjs_int len))
{
	{
		for(int ___index = 0; ___index < len; ___index++)
		{
			buf[___index] = TVP_GL_FUNCNAME(TVPAlphaToAdditiveAlpha)(buf[___index]);
		}
	}
}

TVP_GL_FUNC_DECL(void, TVPConvertAdditiveAlphaToAlpha_c, (tjs_uint32 *buf, tjs_int len))
{/*MAY LOOSE ADDITIVE STUFF*/
	tjs_uint32 tmp;
	const tjs_uint8 * t;
	for(int lu_n = 0; lu_n < len; lu_n++)
	{
		{
			tmp = *buf;
			t = ((tmp >> 16u) & 0xff00u) + TVPDivTable;
			*buf = (tmp & 0xff000000u) +
				(t[(tmp >> 16u) & 0xffu] << 16u) +
				(t[(tmp >>  8u) & 0xffu] <<  8u) +
				(t[ tmp        & 0xffu]      );
			buf++;
		}
	}
}
