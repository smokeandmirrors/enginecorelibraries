#pragma once
#ifndef NUMERICALFUNCTIONS_H
#define NUMERICALFUNCTIONS_H

#include <math.h>
#include <float.h>

#include "Build.h"
#include "Numbers.h"
/**
\file NumbericalFunctions.h

This file is intended to allow for easier cross platorm, cross compiler
development.

\todo make this a templated class:  Math<T>
with all static functions

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO

*/

namespace math
{

template<typename T> inline T abs(T number);
template<typename T> inline T acos(T number);
template<typename T> inline T asin(T number);
template<typename T> inline T atan(T number);
template<typename T> inline T atan2(T x_coordinate, T y_coordinate);
template<typename T> inline T ceil(T number);
template<typename T> inline T cos(T number);
template<typename T> inline T cosh(T number);
template<typename T> inline T exp(T exponent);
template<typename T> inline T floor(T exponent);
template<typename T> inline bool isFinite(T number);
template<typename T> inline bool isNaN(T number);
template<typename T> inline bool isValid(T number);	
template<typename T> inline T ldexp(T number, sint base_2_exponent);
template<typename T> inline T ln(T number);
template<typename T> inline T log10(T number);
template<typename T> inline T mod(T numerator, T denominator);
template<typename T> inline T pow(T base, T exponent);
template<typename T> inline T rexp(T number, sint& exponent);
template<typename T> inline T sin(T number);
template<typename T> inline T sinh(T number);
template<typename T> inline T sqrt(T square);
template<typename T> inline T tan(T number);
template<typename T> inline T tanh(T number);

} // namespace math

template<> inline sint math::abs<sint>(sint number)
{
	return ::abs(number);
}

template<> inline slong math::abs<slong>(slong number)
{
	return static_cast<sint>( ::abs( static_cast<sint>(number) ) );
}

template<> inline sreal math::abs<sreal>(sreal number)
{
	return fabs(number);
}

template<> inline dreal math::abs<dreal>(dreal number)
{
	return fabs(number);
}

template<> inline sreal math::acos<sreal>(sreal number)
{
	return ::acos(number);
}

template<> inline dreal math::acos<dreal>(dreal number)
{
	return ::acos(number);
}

template<> inline sreal math::asin<sreal>(sreal number)
{
	return ::asin(number);
}

template<> inline dreal math::asin<dreal>(dreal number)
{
	return ::asin(number);
}

template<> inline sreal math::atan<sreal>(sreal number)
{
	return ::atan(number);
}

template<> inline dreal math::atan<dreal>(dreal number)
{
	return ::atan(number);
}

template<> inline sreal math::atan2<sreal>(sreal x_coordinate, sreal y_coordinate)
{
	return ::atan2(x_coordinate, y_coordinate);
}

template<> inline dreal math::atan2<dreal>(dreal x_coordinate, dreal y_coordinate)
{
	return ::atan2(x_coordinate, y_coordinate);
}

template<> inline sreal math::ceil<sreal>(sreal number)
{
	return ::ceil(number);
}

template<> inline dreal math::ceil<dreal>(dreal number)
{
	return ::ceil(number);
}

template<> inline sreal math::cos<sreal>(sreal number)
{
	return ::cos(number);
}

template<> inline dreal math::cos<dreal>(dreal number)
{
	return ::cos(number);
}

template<> inline sreal math::cosh<sreal>(sreal number)
{
	return ::cosh(number);
}

template<> inline dreal math::cosh<dreal>(dreal number)
{
	return ::cosh(number);
}

template<> inline sreal math::exp<sreal>(sreal exponent)
{
	return ::exp(exponent);
}

template<> inline dreal math::exp<dreal>(dreal exponent)
{
	return ::exp(exponent);
}

template<> inline sreal math::floor<sreal>(sreal exponent)
{
	return ::floor(exponent);
}

template<> inline dreal math::floor<dreal>(dreal exponent)
{
	return ::floor(exponent);
}

template<> inline bool math::isFinite<sreal>(sreal number) 
{ 
	return _finite(number) != 0; 
}

template<> inline bool math::isFinite<dreal>(dreal number) 
{ 
	return _finite(number) != 0;
}

template<> inline bool math::isNaN<sreal>(sreal number)		
{ 
	return _isnan(number) != 0; 
}

template<> inline bool math::isNaN<dreal>(dreal number) 
{ 
	return _isnan(number) != 0; 
}

template<> inline bool math::isValid<sreal>(sreal number)
{
	return _finite(number) != 0; 
}

template<> inline bool math::isValid<dreal>(dreal number) 
{ 
	return _finite(number) != 0; 
}

template<> inline sreal math::ldexp<sreal>(sreal number, sint base_2_exponent)
{
	return ::ldexp(number, base_2_exponent);
}

template<> inline dreal math::ldexp<dreal>(dreal number, sint base_2_exponent)
{
	return ::ldexp(number, base_2_exponent);
}

template<> inline sreal math::ln<sreal>(sreal number)
{
	return log(number);
}

template<> inline dreal math::ln<dreal>(dreal number)
{
	return log(number);
}

template<> inline sreal math::log10<sreal>(sreal number)
{
	return ::log10(number);
}

template<> inline dreal math::log10<dreal>(dreal number)
{
	return ::log10(number);
}

template<> inline sreal math::mod<sreal>(sreal numerator, sreal denominator)
{
	return fmod(numerator, denominator);
}

template<> inline dreal math::mod<dreal>(dreal numerator, dreal denominator)
{
	return fmod(numerator, denominator);
}

template<> inline sreal math::pow<sreal>(sreal base, sreal exponent)
{
	return ::pow(base, exponent);
}

template<> inline dreal math::pow<dreal>(dreal base, dreal exponent)
{
	return ::pow(base, exponent);
}

template<> inline sreal math::rexp<sreal>(sreal number, sint& exponent)
{
	return frexp(number, &exponent);
}

template<> inline dreal math::rexp<dreal>(dreal number, sint& exponent)
{
	return frexp(number, &exponent);
}

template<> inline sreal math::sin<sreal>(sreal number)
{
	return ::sin(number);
}

template<> inline dreal math::sin<dreal>(dreal number)
{
	return ::sin(number);
}

template<> inline sreal math::sinh<sreal>(sreal number)
{
	return ::sinh(number);
}

template<> inline dreal math::sinh<dreal>(dreal number)
{
	return ::sinh(number);
}

template<> inline sreal math::sqrt<sreal>(sreal square)
{
	return ::sqrt(square);
}

template<> inline dreal math::sqrt<dreal>(dreal square)
{
	return ::sqrt(square);
}

template<> inline sreal math::tan<sreal>(sreal number)
{
	return ::tan(number);
}

template<> inline dreal math::tan<dreal>(dreal number)
{
	return ::tan(number);
}

template<> inline sreal math::tanh<sreal>(sreal number)
{
	return ::tanh(number);
}

template<> inline dreal math::tanh<dreal>(dreal number)
{
	return ::tanh(number);
}

#endif//NUMERICALFUNCTIONS_H