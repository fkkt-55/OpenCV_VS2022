#include "pch.h"
#include "CoreFileUtility.h"

File_Utility::File_Utility()
{
}

File_Utility::~File_Utility()
{
}

File_Utility& File_Utility::getInstance()
{
    static File_Utility instance;
    return instance;
}

bool File_Utility::fileExists(const String& filePath)
{
    if (filePath.empty())
    {
        return false;
    }
    std::ifstream file(filePath);
    return file.good();
}