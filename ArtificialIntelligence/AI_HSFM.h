#pragma once
#ifndef AI_HSFM_H
#define AI_HSFM_H

#include "Platform.h"
#include "AI_Behavior.h"

namespace AI
{
	template<typename AGENT>
	class Behavior
	{
	public:
		virtual ~Behavior(void)=0 {}
		virtual void execute(AGENT&)=void;
	}; // class Behavior

	template<typename AGENT>
	class Action : public Behavior<AGENT>
	{
	public:
		void execute(AGENT&)=0;
	}; // class Action

	template<typename AGENT>
	class Condition
	{
	public:
		virtual ~Condition(void)=0 {}
		void isSatisfied(AGENT&)=0;
	}; // class Condition

	template<typename AGENT>
	class Selector : public Behavior<AGENT> // public Action?
	{
	public:
		// void connect(&
	}; // class Selector

} // namespace AI

#endif//AI_HSFM_H