#pragma once
#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H
/**
\file Constructors.h

This file creates template wrapper functions
for constructors to allow for taking function pointers
to constructors.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 10/12/2011

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	NO
Tested in the field	:	NO
*/

template<typename CLASS>
CLASS* construct(void)
{
	return new CLASS();
}

template<typename CLASS, typename ARG_1>
CLASS* construct(ARG_1 arg1)
{
	return new CLASS(arg1);
}

#endif//CONSTRUCTORS_H