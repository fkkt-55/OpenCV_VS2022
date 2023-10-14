#pragma once

#include <opencv2/opencv.hpp>
#include <core.h>

class FaceDector
{
public:
    virtual ~FaceDector();
    // Get the singleton instance
    static FaceDector& getInstance(const String& faceCascadePath);

public:
    // Detect face, then show it with dc
    bool detect(const String& imagePath, CPaintDC& dc);

private:
    FaceDector(const String& faceCascadeFile);

private:
    String faceCascadeFilePath;
};
