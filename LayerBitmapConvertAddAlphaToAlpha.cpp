
#include "tjsCommHead.h"
#include "LayerBitmapIntf.h"
#include "LayerBitmapConvertAddAlphaToAlpha.h"

void ConvertAddAlphaToAlpha(tTVPBaseBitmap *destbmp)
{
	// convert additive alpha representation to alpha representation

#if 0
	if(!Is32BPP()) TVPThrowExceptionMessage(TVPInvalidOperationFor8BPP);
#endif

	tjs_int w = destbmp->GetWidth();
	tjs_int h = destbmp->GetHeight();
	tjs_int pitch = destbmp->GetPitchBytes();
	tjs_uint8 * line = (tjs_uint8*)destbmp->GetScanLineForWrite(0);

	while(h--)
	{
		TVPConvertAdditiveAlphaToAlpha((tjs_uint32*)line, w);
		line += pitch;
	}
}
