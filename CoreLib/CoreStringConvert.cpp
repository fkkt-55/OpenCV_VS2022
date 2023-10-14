#include "pch.h"
#include "CoreStringConvert.h"

String CoreStringConvert::CString2String(const CString& cstring)
{
	if (cstring)
	{
		CT2CA str(cstring);
		return String(str);
	}
	return String();
}

CString CoreStringConvert::String2CString(const String& string)
{
	if (!string.empty())
	{
		CString cstring;
		cstring.Format(_T("%s"), string);
		return cstring;
	}
	return CString();
}
