#pragma once
#ifndef GENERIC_CONDITIONS_H
#define GENERIC_CONDITIONS_H

#include "HierarchicalFiniteStateMachine.h"

// template<typename AGENT, typename OPERATOR, typename UNO, typename UNO_ARGS>
// class ConditionUnary

// template<typename AGENT, typename OPERATOR, typename UNO>
// class ConditionUnary

namespace HFSM 
{
	
/** A class performs that the binary operation passed in OPERATOR to the conditions LHS and RHS. */
template<typename AGENT, typename OPERATOR, typename LHS, typename RHS>
class ConditionBinary
	: public Condition<AGENT>
{
public: 
	virtual bool isSatisfied(AGENT& agent)
	{
		OPERATOR boolean;
		return boolean(agent, *lhs, *rhs);
	}

	virtual void recycle(void) 
	{ 
		Factory< ConditionBinary< AGENT, OPERATOR, LHS, RHS > >::recycleRunTimeCopy(*this); 
	} 

private: 
	friend class Factory< ConditionBinary< AGENT, OPERATOR, LHS, RHS > >; 
	friend class FactorySelector< LHS::hasAuthorTimeState || RHS::hasAuthorTimeState >::Internal< ConditionBinary< AGENT, OPERATOR, LHS, RHS > >; 

	ConditionBinary(void)
	{
		lhs = Factory< LHS >::getAuthorCopy();
		rhs = Factory< RHS >::getAuthorCopy();
	}

	template<typename LHS_ARGS, typename RHS_ARGS>
	ConditionBinary(LHS_ARGS lhsArgs, RHS_ARGS rhsArgs)
	{
		lhs = Factory< LHS >::getAuthorCopy<LHS_ARGS>(lhsArgs);
		rhs = Factory< RHS >::getAuthorCopy<RHS_ARGS>(rhsArgs);
	}

	template<typename LHS_ARGS>
	ConditionBinary(LHS_ARGS lhsArgs)
	{
		lhs = Factory< LHS >::getAuthorCopy<LHS_ARGS>(lhsArgs);
		rhs = Factory< RHS >::getAuthorCopy();
	}

	bool isEqualToAtAuthorTime(const ConditionBinary< AGENT, OPERATOR, LHS, RHS > & source) const 
	{ 
		return static_cast<LHS*>(lhs)->isEqualToAtAuthorTime(*static_cast<LHS*>(source.lhs)) 
			&& static_cast<RHS*>(rhs)->isEqualToAtAuthorTime(*static_cast<RHS*>(source.rhs)); 
	} 

	static const bool hasAuthorTimeState = LHS::hasAuthorTimeState || RHS::hasAuthorTimeState;

	virtual bool hasRunTimeState(void) const 
	{ 
		return lhs->hasRunTimeState() || rhs->hasRunTimeState(); 
	} 

	static ConditionBinary< AGENT, OPERATOR, LHS, RHS > * duplicate(const ConditionBinary< AGENT, OPERATOR, LHS, RHS > & source) 
	{ 
		ConditionBinary< AGENT, OPERATOR, LHS, RHS >* dupe(new ConditionBinary< AGENT, OPERATOR, LHS, RHS > (source));
		dupe->lhs = source.lhs->getRunTimeCopy();
		dupe->rhs = source.rhs->getRunTimeCopy();
		return dupe;  
	} 
	
	virtual Condition < AGENT >* getRunTimeCopy(void) const 
	{ 
		return Factory< ConditionBinary< AGENT, OPERATOR, LHS, RHS > >::getRunTimeCopy(*this); 
	} 
	
	ConditionBinary< AGENT, OPERATOR, LHS, RHS >& operator=(const ConditionBinary< AGENT, OPERATOR, LHS, RHS >&); 

	Condition<AGENT>* lhs;
	Condition<AGENT>* rhs;
}; // ConditionBinary

/**
A Condition that always is never satisfied
which is a need that comes up frequently 
during iteration & debugging.
*/
template<typename AGENT>
class ConditionFalse
	: public Condition<AGENT>
{
	CONDITION_PURE(ConditionFalse, AGENT)

	ConditionFalse(void)
	{
		/* empty */
	}

protected:
	bool isSatisfied(AGENT&) { return false; };
}; // ConditionFalse

/** A class performs that the !operator to OPERAND. */
template<typename AGENT, typename OPERAND>
class ConditionNot
	: public Condition<AGENT>
{
public: 
	virtual bool isSatisfied(AGENT& agent)
	{
		return !(*operand)(agent);
	}

	virtual void recycle(void) 
	{ 
		Factory< ConditionNot< AGENT, OPERAND > >::recycleRunTimeCopy(*this); 
	} 

private: 
	friend class Factory< ConditionNot< AGENT, OPERAND > >; 
	friend class FactorySelector< OPERAND::hasAuthorTimeState >::Internal< ConditionNot< AGENT, OPERAND > >; 

	ConditionNot(void)
	{
		operand = Factory< OPERAND >::getAuthorCopy();
	}

	template<typename ARGS>
	ConditionNot(ARGS args)
	{
		operand = Factory< OPERAND >::getAuthorCopy<ARGS>(args);
	}

	bool isEqualToAtAuthorTime(const ConditionNot< AGENT, OPERAND > & source) const 
	{ 
		return static_cast<OPERAND*>(operand)->isEqualToAtAuthorTime(*static_cast<OPERAND*>(source.operand));
	} 

	static const bool hasAuthorTimeState = OPERAND::hasAuthorTimeState;

	virtual bool hasRunTimeState(void) const 
	{ 
		return operand->hasRunTimeState(); 
	} 

	static ConditionNot< AGENT, OPERAND > * duplicate(const ConditionNot< AGENT, OPERAND > & source) 
	{ 
		ConditionNot< AGENT, OPERAND >* dupe(new ConditionNot< AGENT, OPERAND > (source));
		dupe->operand = source.operand->getRunTimeCopy();
		return dupe;  
	} 
	
	virtual Condition < AGENT >* getRunTimeCopy(void) const 
	{
		return Factory< ConditionNot< AGENT, OPERAND > >::getRunTimeCopy(*this); 
	} 
	
	ConditionNot< AGENT, OPERAND >& operator=(const ConditionNot< AGENT, OPERAND >&); 
	
	Condition<AGENT>* operand;
}; // ConditionNot


template <typename AGENT>
struct ConditionOperatorAnd
{
	inline bool operator()(AGENT& agent, Condition<AGENT>& lhs, Condition<AGENT>& rhs) const
	{
		return lhs(agent) && rhs(agent);
	}
};

template <typename AGENT>
struct ConditionOperatorNot
{
	inline bool operator()(AGENT& agent, Condition<AGENT>& operand) const
	{
		return !operand(agent);
	}
};

template <typename AGENT>
struct ConditionOperatorOr
{
	inline bool operator()(AGENT& agent, Condition<AGENT>& lhs, Condition<AGENT>& rhs) const
	{
		return lhs(agent) || rhs(agent);
	}
};

template <typename AGENT>
struct ConditionOperatorXor
{
	inline bool operator()(AGENT& agent, Condition<AGENT>& lhs, Condition<AGENT>& rhs) const
	{
		return lhs(agent) ^ rhs(agent);
	}
};

/**
A Condition that always is always satisfied,
which is a need that comes up frequently 
during iteration & debugging.
*/
template<typename AGENT>
class ConditionTrue
	: public Condition<AGENT>
{
	CONDITION_PURE(ConditionTrue, AGENT)

		ConditionTrue(void)
	{
		/* empty */
	}

protected:
	bool isSatisfied(AGENT&) { return true; };
}; // ConditionTrue

} // namespace HFSM 

#endif//GENERIC_CONDITIONS_H