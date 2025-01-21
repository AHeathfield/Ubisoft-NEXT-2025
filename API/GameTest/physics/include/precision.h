// precision.h
#pragma once
namespace physics
{
	/*
	 *	Defines a real number precision. It will be useful if we need to quickly switch the number
	 *	precision.
	 */
	typedef float real;

	// Defines the precision of the sqaure root operator.
#define real_sqrt sqrtf

// Defines the precision of the power operator.
#define real_pow powf
}