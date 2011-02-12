#pragma once
#ifndef LUAEXTENSIONINCLUSIONS_H
#define LUAEXTENSIONINCLUSIONS_H
/**
\file LuaExentionInclusions.h 

A file to include what will probably be necessary
to compile use of the embedded %Lua and exposition system.

Unfortunately, this means including lua.h and other files that I didn't 
want to happen, but that does make for cleaner implementation in all
other areas.

\warning Much system is dependent on the use of ObjectOrientedParadigm.lua

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/11/2011

\todo 32/64-bit number types, NULL, assert, warn, error
*/
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

#endif//LUAEXTENSIONINCLUSIONS_H