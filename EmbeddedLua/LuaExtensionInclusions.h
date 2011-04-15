#pragma once
#ifndef LUAEXTENSIONINCLUSIONS_H
#define LUAEXTENSIONINCLUSIONS_H
/**
\file LuaExtensionInclusions.h 
A file to include what will probably be necessary
to compile use of the embedded %Lua and exposition system.

Unfortunately, this means including lua.h and other files that I didn't 
want to include all over the place, but that does make for cleaner 
implementation for much of the required functionality.

\warning Much of the system is dependent on the use of ObjectOrientedParadigm.lua,
in order to properly use it, your lua_States must load that chunk before
processing the run-time directives of this system.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/11/2011
*/

#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "LuaFunctionExposition.h"

#endif//LUAEXTENSIONINCLUSIONS_H