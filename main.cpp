/////////////////////////////////////////////
//                                         //
//    Copyright (C) 2021-2021 Julian Uy    //
//  https://sites.google.com/site/awertyb  //
//                                         //
//   See details of license at "LICENSE"   //
//                                         //
/////////////////////////////////////////////

#include "ncbind/ncbind.hpp"
#include "LayerBitmapIntf.h"
#include "LayerBitmapUtility.h"
#include "LayerBitmapConvertAddAlphaToAlpha.h"
#include "LayerBitmapConvertAlphaToAddAlpha.h"
#include <string.h>
#include <stdio.h>

static void PreRegistCallback()
{
	iTJSDispatch2 *global = TVPGetScriptDispatch();
	if (global)
	{
		tTJSVariant layer_val;
		static ttstr Layer_name(TJS_W("Layer"));
		global->PropGet(0, Layer_name.c_str(), Layer_name.GetHint(), &layer_val, global);
		tTJSVariantClosure layer_valclosure = layer_val.AsObjectClosureNoAddRef();
		if (layer_valclosure.Object)
		{
			layer_valclosure.DeleteMember(TJS_IGNOREPROP, TJS_W("convertType"), 0, NULL);
		}
	}
}

NCB_PRE_REGIST_CALLBACK(PreRegistCallback);

class LayerLayerExConvertLayerType
{
public:
	static tjs_error TJS_INTF_METHOD convertType(
		tTJSVariant	*result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if(numparams < 1) return TJS_E_BADPARAMCOUNT;
	
		tTVPDrawFace fromtype = (tTVPDrawFace)(tjs_int)*param[0];

		if(objthis == NULL) TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		// Now get information (this will independ the bitmap)
		tjs_int bmpwidth = 0;
		tjs_int bmpheight = 0;
		tjs_int bmppitch = 0;
		tjs_uint8* bmpdata = NULL;
		GetBitmapInformationFromObject(bmpobject_clo, true, &bmpwidth, &bmpheight, &bmppitch, &bmpdata);
		if(!bmpdata) return TJS_S_OK; // don't throw error, just return
		tTVPBaseBitmap bmpinfo(bmpwidth, bmpheight, bmppitch, bmpdata);

		tTVPDrawFace Face = dfAuto; // (outward) current drawing layer face
		tTVPLayerType DisplayType = ltOpaque; // actual Type

		GetLayerInformationFromLayerObject(bmpobject_clo, &Face, &DisplayType, NULL, NULL, NULL, NULL, NULL);

		tTVPDrawFace DrawFace = GetDrawFace(Face, DisplayType); // (actual) current drawing layer face

		if(DrawFace == dfAddAlpha && fromtype == dfAlpha)
		{
			// alpha -> additive alpha
			ConvertAlphaToAddAlpha(&bmpinfo);
		}
		else if(DrawFace == dfAlpha && fromtype == dfAddAlpha)
		{
			// additive alpha -> alpha
			// this may loose additive stuff
			ConvertAddAlphaToAlpha(&bmpinfo);
		}
		else
		{
			// throw an error
			TVPThrowExceptionMessage(TJS_W("Cannot convert layer type using given direction"));
		}
		UpdateWholeLayerWithLayerObject(bmpobject_clo);
		return TJS_S_OK;
	}
};

NCB_ATTACH_CLASS(LayerLayerExConvertLayerType, Layer)
{
	RawCallback("convertType", &Class::convertType, 0);
};
