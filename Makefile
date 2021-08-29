
SOURCES += main.cpp
SOURCES += LayerBitmapConvertAddAlphaToAlpha.cpp
SOURCES += LayerBitmapConvertAlphaToAddAlpha.cpp
SOURCES += LayerBitmapUtility.cpp
PROJECT_BASENAME = layerExConvertLayerType

RC_LEGALCOPYRIGHT ?= Copyright (C) 2021-2021 Julian Uy; See details of license at license.txt, or the source code location.

include external/ncbind/Rules.lib.make
