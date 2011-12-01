#pragma once
#ifndef TEMPLATEARGUMENTS_H
#define TEMPLATEARGUMENTS_H
/**
\file TemplateArguments

Macros to help assist auto-writing template functions/classes.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 3/22/2011

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/

/** template arguments */
// fill in the template arguments in the declaration
#define CW_TEMPLATE_ARGS_RETS_0_ARGS_1 typename ARG_1
#define CW_TEMPLATE_ARGS_RETS_0_ARGS_2 typename ARG_1, typename ARG_2 
#define CW_TEMPLATE_ARGS_RETS_0_ARGS_3 typename ARG_1, typename ARG_2, typename ARG_3
#define CW_TEMPLATE_ARGS_RETS_0_ARGS_4 typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_0_ARGS_5 typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

#define CW_TEMPLATE_ARGS_RETS_1_ARGS_0 typename RET_1 
#define CW_TEMPLATE_ARGS_RETS_1_ARGS_1 typename RET_1, typename ARG_1
#define CW_TEMPLATE_ARGS_RETS_1_ARGS_2 typename RET_1, typename ARG_1, typename ARG_2
#define CW_TEMPLATE_ARGS_RETS_1_ARGS_3 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3
#define CW_TEMPLATE_ARGS_RETS_1_ARGS_4 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_1_ARGS_5 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

#define CW_TEMPLATE_ARGS_RETS_2_ARGS_0 typename RET_1, typename RET_2
#define CW_TEMPLATE_ARGS_RETS_2_ARGS_1 typename RET_1, typename RET_2, typename ARG_1
#define CW_TEMPLATE_ARGS_RETS_2_ARGS_2 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2
#define CW_TEMPLATE_ARGS_RETS_2_ARGS_3 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3 
#define CW_TEMPLATE_ARGS_RETS_2_ARGS_4 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_2_ARGS_5 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

#define CW_TEMPLATE_ARGS_RETS_3_ARGS_0 typename RET_1, typename RET_2, typename RET_3
#define CW_TEMPLATE_ARGS_RETS_3_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename ARG_1 
#define CW_TEMPLATE_ARGS_RETS_3_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2
#define CW_TEMPLATE_ARGS_RETS_3_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3
#define CW_TEMPLATE_ARGS_RETS_3_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_3_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

#define CW_TEMPLATE_ARGS_RETS_4_ARGS_0 typename RET_1, typename RET_2, typename RET_3, typename RET_4
#define CW_TEMPLATE_ARGS_RETS_4_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1
#define CW_TEMPLATE_ARGS_RETS_4_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2
#define CW_TEMPLATE_ARGS_RETS_4_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3
#define CW_TEMPLATE_ARGS_RETS_4_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_4_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

#define CW_TEMPLATE_ARGS_RETS_5_ARGS_0 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5
#define CW_TEMPLATE_ARGS_RETS_5_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1 
#define CW_TEMPLATE_ARGS_RETS_5_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2
#define CW_TEMPLATE_ARGS_RETS_5_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3 
#define CW_TEMPLATE_ARGS_RETS_5_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4
#define CW_TEMPLATE_ARGS_RETS_5_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5

// fill in the template arguments in the template function for a 
// function that returns the first return value with the return statement
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_0 void
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_1 RET_1
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_2 RET_1
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_3 RET_1
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_4 RET_1
#define CW_TEMPLATE_RETURN_SIGNATURE_RETS_5 RET_1

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_2 ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_3 ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_0 void
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_1 ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_2 ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_3 ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_0 RET_2&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_1 RET_2&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_2 RET_2&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_3 RET_2&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_4 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_5 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_0 RET_2&, RET_3&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_1 RET_2&, RET_3&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_2 RET_2&, RET_3&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_3 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_4 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_5 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_0 RET_2&, RET_3&, RET_4&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_1 RET_2&, RET_3&, RET_4&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_2 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_3 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_4 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_5 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_0 RET_2&, RET_3&, RET_4&, RET_5&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_1 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_2 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_3 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_4 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_5 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

// fill in the template arguments in the template function for a 
// function that returns the first return by reference parameter
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_2 ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_3 ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_0 void
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_1 ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_2 ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_3 ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_0 RET_2&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_1 RET_2&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_2 RET_2&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_3 RET_2&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_4 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_5 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_0 RET_2&, RET_3&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_1 RET_2&, RET_3&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_2 RET_2&, RET_3&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_3 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_4 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_5 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_0 RET_2&, RET_3&, RET_4&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_1 RET_2&, RET_3&, RET_4&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_2 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_3 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_4 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_5 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_0 RET_2&, RET_3&, RET_4&, RET_5&
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_1 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_2 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_3 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_4 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4
#define CW_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_5 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

/** function implementation */
// declare the function signature
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_0 
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_1 ARG_1 arg1
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_2 ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_3 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_4 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_RETS_0_ARGS_5 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_RETS_1_ARGS_0 
#define CW_DECLARE_FUNCTION_RETS_1_ARGS_1 ARG_1 arg1
#define CW_DECLARE_FUNCTION_RETS_1_ARGS_2 ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_RETS_1_ARGS_3 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_RETS_1_ARGS_4 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_RETS_1_ARGS_5 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_RETS_2_ARGS_0 RET_2& ret2,
#define CW_DECLARE_FUNCTION_RETS_2_ARGS_1 RET_2& ret2, ARG_1 arg1
#define CW_DECLARE_FUNCTION_RETS_2_ARGS_2 RET_2& ret2, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_RETS_2_ARGS_3 RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_RETS_2_ARGS_4 RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_RETS_2_ARGS_5 RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

// for a signature that returns all return values by reference
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_0 
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_1 ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_2 ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_3 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_4 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_0_ARGS_5 ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_0 RET_1& ret1
#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_1 RET_1& ret1, ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_2 RET_1& ret1, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_3 RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_4 RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_1_ARGS_5 RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_0 RET_1& ret1, RET_2& ret2
#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_1 RET_1& ret1, RET_2& ret2, ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_2 RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_3 RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_4 RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_2_ARGS_5 RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_0 RET_1& ret1, RET_2& ret2, RET_3& ret3
#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_1 RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_2 RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_3 RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_4 RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_3_ARGS_5 RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_0 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4
#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_1 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_2 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_3 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_4 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_4_ARGS_5 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_0 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5
#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_1 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1
#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_2 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2
#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_3 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3
#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_4 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4
#define CW_DECLARE_FUNCTION_REF_RETS_5_ARGS_5 RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5

// declare the return values that get passed by reference into the function
#define CW_DECLARE_RETS_0 ;
#define CW_DECLARE_RETS_1 ;	
#define CW_DECLARE_RETS_2 RET_2 ret2;
#define CW_DECLARE_RETS_3 RET_2 ret2; RET_3 ret3;
#define CW_DECLARE_RETS_4 RET_2 ret2; RET_3 ret3; RET_4 ret4;
#define CW_DECLARE_RETS_5 RET_2 ret2; RET_3 ret3; RET_4 ret4; RET_5 ret5;

// assign the value of the function, declare the first return value
#define CW_DECLARE_1_ASSIGN_RETS_0
#define CW_DECLARE_1_ASSIGN_RETS_1 RET_1 ret1 = 
#define CW_DECLARE_1_ASSIGN_RETS_2 RET_1 ret1 = 
#define CW_DECLARE_1_ASSIGN_RETS_3 RET_1 ret1 = 
#define CW_DECLARE_1_ASSIGN_RETS_4 RET_1 ret1 = 
#define CW_DECLARE_1_ASSIGN_RETS_5 RET_1 ret1 = 

// assign the value of the function
#define CW_ASSIGN_RETS_0
#define CW_ASSIGN_RETS_1 ret1 = 
#define CW_ASSIGN_RETS_2 ret1 = 
#define CW_ASSIGN_RETS_3 ret1 = 
#define CW_ASSIGN_RETS_4 ret1 = 
#define CW_ASSIGN_RETS_5 ret1 = 

// pass in the arguments to the function
#define CW_CALL_RETS_0_ARGS_0 
#define CW_CALL_RETS_0_ARGS_1 arg1
#define CW_CALL_RETS_0_ARGS_2 arg1, arg2
#define CW_CALL_RETS_0_ARGS_3 arg1, arg2, arg3
#define CW_CALL_RETS_0_ARGS_4 arg1, arg2, arg3, arg4
#define CW_CALL_RETS_0_ARGS_5 arg1, arg2, arg3, arg4, arg5

#define CW_CALL_RETS_1_ARGS_0 
#define CW_CALL_RETS_1_ARGS_1 arg1
#define CW_CALL_RETS_1_ARGS_2 arg1, arg2
#define CW_CALL_RETS_1_ARGS_3 arg1, arg2, arg3
#define CW_CALL_RETS_1_ARGS_4 arg1, arg2, arg3, arg4
#define CW_CALL_RETS_1_ARGS_5 arg1, arg2, arg3, arg4, arg5

#define CW_CALL_RETS_2_ARGS_0 ret2
#define CW_CALL_RETS_2_ARGS_1 ret2, arg1
#define CW_CALL_RETS_2_ARGS_2 ret2, arg1, arg2
#define CW_CALL_RETS_2_ARGS_3 ret2, arg1, arg2, arg3
#define CW_CALL_RETS_2_ARGS_4 ret2, arg1, arg2, arg3, arg4
#define CW_CALL_RETS_2_ARGS_5 ret2, arg1, arg2, arg3, arg4, arg5

#define CW_CALL_RETS_3_ARGS_0 ret2, ret3
#define CW_CALL_RETS_3_ARGS_1 ret2, ret3, arg1
#define CW_CALL_RETS_3_ARGS_2 ret2, ret3, arg1, arg2
#define CW_CALL_RETS_3_ARGS_3 ret2, ret3, arg1, arg2, arg3
#define CW_CALL_RETS_3_ARGS_4 ret2, ret3, arg1, arg2, arg3, arg4
#define CW_CALL_RETS_3_ARGS_5 ret2, ret3, arg1, arg2, arg3, arg4, arg5

#define CW_CALL_RETS_4_ARGS_0 ret2, ret3, ret4 
#define CW_CALL_RETS_4_ARGS_1 ret2, ret3, ret4, arg1
#define CW_CALL_RETS_4_ARGS_2 ret2, ret3, ret4, arg1, arg2
#define CW_CALL_RETS_4_ARGS_3 ret2, ret3, ret4, arg1, arg2, arg3
#define CW_CALL_RETS_4_ARGS_4 ret2, ret3, ret4, arg1, arg2, arg3, arg4
#define CW_CALL_RETS_4_ARGS_5 ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5

#define CW_CALL_RETS_5_ARGS_0 ret2, ret3, ret4, ret5
#define CW_CALL_RETS_5_ARGS_1 ret2, ret3, ret4, ret5, arg1
#define CW_CALL_RETS_5_ARGS_2 ret2, ret3, ret4, ret5, arg1, arg2
#define CW_CALL_RETS_5_ARGS_3 ret2, ret3, ret4, ret5, arg1, arg2, arg3
#define CW_CALL_RETS_5_ARGS_4 ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4
#define CW_CALL_RETS_5_ARGS_5 ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5

// define all argument #, parameter # functions of the generation_macro
#define CW_GENERATE_ALL(generation_macro) \
	generation_macro(0, 1) \
	generation_macro(0, 2) \
	generation_macro(0, 3) \
	generation_macro(0, 4) \
	generation_macro(0, 5) \
	generation_macro(1, 0) \
	generation_macro(1, 1) \
	generation_macro(1, 2) \
	generation_macro(1, 3) \
	generation_macro(1, 4) \
	generation_macro(1, 5) \
	generation_macro(2, 0) \
	generation_macro(2, 1) \
	generation_macro(2, 2) \
	generation_macro(2, 3) \
	generation_macro(2, 4) \
	generation_macro(2, 5) \
	generation_macro(3, 0) \
	generation_macro(3, 1) \
	generation_macro(3, 2) \
	generation_macro(3, 3) \
	generation_macro(3, 4) \
	generation_macro(3, 5) \
	generation_macro(4, 0) \
	generation_macro(4, 1) \
	generation_macro(4, 2) \
	generation_macro(4, 3) \
	generation_macro(4, 4) \
	generation_macro(4, 5) \
	generation_macro(5, 0) \
	generation_macro(5, 1) \
	generation_macro(5, 2) \
	generation_macro(5, 3) \
	generation_macro(5, 4) \
	generation_macro(5, 5) 

#endif//TEMPLATEARGUMENTS_H

