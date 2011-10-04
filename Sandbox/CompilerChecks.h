#pragma once
#ifndef COMPILERCHECKS_H
#define COMPILERCHECKS_H
/** 
<DEVELOPMENT STATUS>
Current Draft		:	N/A
Current Phase		:   N/A
Purpose				:	Experiments
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/
namespace compilerChecks 
{

	template <typename REAL>
	class Math
	{
	public:
		static const REAL ZERO_TOLERANCE;
	};

	/** \todo templated properties **/

	const int Math<int>::ZERO_TOLERANCE = 5;
	const float Math<float>::ZERO_TOLERANCE = 0.0f;

	void check(void);

} // namespace compilerChecks




#endif//COMPILERCHECKS_H