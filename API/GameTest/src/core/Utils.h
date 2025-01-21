// Utils.h
#pragma once

#include "stdafx.h"

class Utils
{
public:
	static float clamp(float value, float minValue, float maxValue);
	static bool compareFloats(float a, float b, float epsilon = 1e-6f);
};