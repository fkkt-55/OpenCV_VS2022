#pragma once

#include "CoreMacros.h"
#include <afx.h>

class CoreStringConvert
{
public:
	CoreStringConvert() = delete;

public:
	static String CString2String(const CString& cstring);
	static CString String2CString(const String& string);
};

