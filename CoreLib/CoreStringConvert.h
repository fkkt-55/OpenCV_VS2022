#pragma once

#include <atlstr.h>
#include "CoreMacros.h"

class CoreStringConvert
{
public:
	CoreStringConvert() = delete;

public:
	static String CString2String(const CString& cstring);
};

