#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "CoreMacros.h"

class File_Utility
{
public:
    // Private destructor to prevent external deletion
    virtual ~File_Utility();
    
    // Static method to get the singleton instance
    static File_Utility& getInstance();

public:
    // Static method to check if a file exists
    static bool fileExists(const String& filePath);

private:
    // Private constructor to prevent external instantiation
    File_Utility();
    File_Utility &operator=(const File_Utility &) = delete;

};
