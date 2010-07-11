#pragma once
#ifndef LUALIBRARYDECLARATIONS_H
#define LUALIBRARYDECLARATIONS_H

/**
 * LuaLibraryDeclarations.h
 *
 * Declares %Lua libraries for registration
 * in %Lua instances.
 *
 * @author Smoke and Mirrors Development
 * copyright 2010 Smoke and Mirrors Development
 * smokeandmirrorsdevelopment@gmail.com
 * @date 2/24/2010
 */

#include "LuaRegistration.h"

declare_lua_library(Vector2)
declare_lua_library(Vector3)

declare_lua_library(Grandparent);
declare_lua_library(Parent);
declare_lua_library(Child);

#endif//LUALIBRARYDECLARATIONS_H