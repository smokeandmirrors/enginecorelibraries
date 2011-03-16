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

\todo C99 functions:
http://en.wikipedia.org/wiki/Math.h
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
template<typename T> inline T ldexp(T number, sint4 base_2_exponent);
template<typename T> inline T ln(T number);
template<typename T> inline T log10(T number);
template<typename T> inline T mod(T numerator, T denominator);
template<typename T> inline T pow(T base, T exponent);
template<typename T> inline T rexp(T number, sint4& exponent);
template<typename T> inline T sin(T number);
template<typename T> inline T sinh(T number);
template<typename T> inline T sqrt(T square);
template<typename T> inline T tan(T number);
template<typename T> inline T tanh(T number);

} // namespace math

template<> inline sint4 math::abs<sint4>(sint4 number)
{
	return ::abs(number);
}

template<> inline sint8 math::abs<sint8>(sint8 number)
{
	return static_cast<sint4>( ::abs( static_cast<sint4>(number) ) );
}

template<> inline real4 math::abs<real4>(real4 number)
{
	return fabs(number);
}

template<> inline real8 math::abs<real8>(real8 number)
{
	return fabs(number);
}

template<> inline real4 math::acos<real4>(real4 number)
{
	return ::acos(number);
}

template<> inline real8 math::acos<real8>(real8 number)
{
	return ::acos(number);
}

template<> inline real4 math::asin<real4>(real4 number)
{
	return ::asin(number);
}

template<> inline real8 math::asin<real8>(real8 number)
{
	return ::asin(number);
}

template<> inline real4 math::atan<real4>(real4 number)
{
	return ::atan(number);
}

template<> inline real8 math::atan<real8>(real8 number)
{
	return ::atan(number);
}

template<> inline real4 math::atan2<real4>(real4 x_coordinate, real4 y_coordinate)
{
	return ::atan2(x_coordinate, y_coordinate);
}

template<> inline real8 math::atan2<real8>(real8 x_coordinate, real8 y_coordinate)
{
	return ::atan2(x_coordinate, y_coordinate);
}

template<> inline real4 math::ceil<real4>(real4 number)
{
	return ::ceil(number);
}

template<> inline real8 math::ceil<real8>(real8 number)
{
	return ::ceil(number);
}

template<> inline real4 math::cos<real4>(real4 number)
{
	return ::cos(number);
}

template<> inline real8 math::cos<real8>(real8 number)
{
	return ::cos(number);
}

template<> inline real4 math::cosh<real4>(real4 number)
{
	return ::cosh(number);
}

template<> inline real8 math::cosh<real8>(real8 number)
{
	return ::cosh(number);
}

template<> inline real4 math::exp<real4>(real4 exponent)
{
	return ::exp(exponent);
}

template<> inline real8 math::exp<real8>(real8 exponent)
{
	return ::exp(exponent);
}

template<> inline real4 math::floor<real4>(real4 exponent)
{
	return ::floor(exponent);
}

template<> inline real8 math::floor<real8>(real8 exponent)
{
	return ::floor(exponent);
}

template<> inline bool math::isFinite<real4>(real4 number) 
{ 
	return _finite(number) != 0; 
}

template<> inline bool math::isFinite<real8>(real8 number) 
{ 
	return _finite(number) != 0;
}

template<> inline bool math::isNaN<real4>(real4 number)		
{ 
	return _isnan(number) != 0; 
}

template<> inline bool math::isNaN<real8>(real8 number) 
{ 
	return _isnan(number) != 0; 
}

template<> inline bool math::isValid<real4>(real4 number)
{
	return _finite(number) != 0; 
}

template<> inline bool math::isValid<real8>(real8 number) 
{ 
	return _finite(number) != 0; 
}

template<> inline real4 math::ldexp<real4>(real4 number, sint4 base_2_exponent)
{
	return ::ldexp(number, base_2_exponent);
}

template<> inline real8 math::ldexp<real8>(real8 number, sint4 base_2_exponent)
{
	return ::ldexp(number, base_2_exponent);
}

template<> inline real4 math::ln<real4>(real4 number)
{
	return log(number);
}

template<> inline real8 math::ln<real8>(real8 number)
{
	return log(number);
}

template<> inline real4 math::log10<real4>(real4 number)
{
	return ::log10(number);
}

template<> inline real8 math::log10<real8>(real8 number)
{
	return ::log10(number);
}

template<> inline real4 math::mod<real4>(real4 numerator, real4 denominator)
{
	return fmod(numerator, denominator);
}

template<> inline real8 math::mod<real8>(real8 numerator, real8 denominator)
{
	return fmod(numerator, denominator);
}

template<> inline real4 math::pow<real4>(real4 base, real4 exponent)
{
	return ::pow(base, exponent);
}

template<> inline real8 math::pow<real8>(real8 base, real8 exponent)
{
	return ::pow(base, exponent);
}

template<> inline real4 math::rexp<real4>(real4 number, sint4& exponent)
{
	return frexp(number, &exponent);
}

template<> inline real8 math::rexp<real8>(real8 number, sint4& exponent)
{
	return frexp(number, &exponent);
}

template<> inline real4 math::sin<real4>(real4 number)
{
	return ::sin(number);
}

template<> inline real8 math::sin<real8>(real8 number)
{
	return ::sin(number);
}

template<> inline real4 math::sinh<real4>(real4 number)
{
	return ::sinh(number);
}

template<> inline real8 math::sinh<real8>(real8 number)
{
	return ::sinh(number);
}

template<> inline real4 math::sqrt<real4>(real4 square)
{
	return ::sqrt(square);
}

template<> inline real8 math::sqrt<real8>(real8 square)
{
	return ::sqrt(square);
}

template<> inline real4 math::tan<real4>(real4 number)
{
	return ::tan(number);
}

template<> inline real8 math::tan<real8>(real8 number)
{
	return ::tan(number);
}

template<> inline real4 math::tanh<real4>(real4 number)
{
	return ::tanh(number);
}

template<> inline real8 math::tanh<real8>(real8 number)
{
	return ::tanh(number);
}

#endif//NUMERICALFUNCTIONS_H