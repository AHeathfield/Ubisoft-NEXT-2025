// Utils.cpp

#include "stdafx.h"
#include "Utils.h"

float Utils::clamp(float value, float minValue, float maxValue)
{
    if (value < minValue)
    {
        return minValue;
    }
    else if (value > maxValue)
    {
        return maxValue;
    }
    return value;
}

// Method to compare two floats
bool Utils::compareFloats(float a, float b, float epsilon)
{
    return std::fabs(a - b) < epsilon;
}