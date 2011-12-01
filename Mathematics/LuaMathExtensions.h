#pragma once
#ifndef LUAMATHEXTENSIONS_H
#define LUAMATHEXTENSIONS_H

#if EXTENDED_BY_LUA
#include "Platform.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"
#include "Vector.h"

DECLARE_LUA_CLASS_NS(math, Vector2);
DECLARE_LUA_CLASS_NS(math, Vector3);

#endif//EXTENDED_BY_LUA
#endif//LUAMATHEXTENSIONS_H