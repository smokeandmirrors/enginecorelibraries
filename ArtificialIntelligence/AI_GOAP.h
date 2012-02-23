#pragma once
#ifndef AI_GOAP_H
#define AI_GOAP_H

#include "Platform.h"
#include "AI_Behavior.h"

namespace AI
{

/* 
 * a general note on ai behavior:
 * instead of planning every last step of of a plan in relationship
 * to the actual condition of the world, a golden plan is done
 * in reference to the actual state of the world,
 * and then implementation plans are created to (in reference to the actual
 * state of the world, presumably much more computationally intensive) complete 
 * each step of the golden plan
 */


} // namespace AI

#endif//AI_GOAP_H