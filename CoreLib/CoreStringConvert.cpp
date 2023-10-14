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
