#pragma once
#ifndef COMPOSITION_H
#define COMPOSITION_H
/**
\file Composition.h

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 4/15/2011

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

#include "Platform.h"

#include <algorithm>
#include <list>

#include "Synchronization.h"

/// \todo activate/deactivate pause/play is/active functions
/// \todo composite grained functionality
/// \todo component grained functionality

namespace designPatterns
{

class RunTimeType
{
public:
	template<typename SOURCE, typename TARGET>
	static TARGET* dynamicCast(SOURCE* object)
	{
		return object->getRunTimeType().IS_A(TARGET::runTimeType) ? static_cast<TARGET*>(object) : NULL;
	}

	RunTimeType(const RunTimeType* const parentClassNullIfThisIsBase, const RunTimeType* const* nullTerminatedInterfaceArray)
		: super(parentClassNullIfThisIsBase)
		, interfaces(nullTerminatedInterfaceArray)
	{
		/* empty */
	}

	bool IS_A(const RunTimeType& otherType) const
	{
		const RunTimeType* thisType(this);

		do 
		{
			if (thisType == &otherType)
			{
				return true;
			}
			else if (interfaces)
			{
				const RunTimeType* const* interface = &interfaces[0];
				do 
				{
					if (*interface == &otherType)
						return true;
				}
				while(*++interface);
			}

			thisType = thisType->super;
		} 
		while (thisType);

		return false;
	}

	bool IS_EXACTLY(const RunTimeType& type) const 
	{ 
		return this == &type; 
	}
		
private:
	RunTimeType(const RunTimeType&);
	RunTimeType operator=(const RunTimeType&);

	const RunTimeType* const* interfaces; // = { *, *, *, *, NULL}
	const RunTimeType* const super;
};

typedef uint Component_GUID;

template<typename COMPOSITE>
class Component
{
	template<typename COMPOSITE> friend class Composite;

public:
	Component(void)
	: composite(NULL)
	{
		/* empty */
	}
	
	virtual ~Component(void)
	{
		/* empty */
	}
	
	const COMPOSITE* getComposite(void) const
	{
		return composite;
	}

	virtual const RunTimeType& getRunTimeType(void) const=0;

protected:
	virtual void onAttachTo(void)
	{
		/* empty */
	}

	virtual void onDetach(void)
	{
		/* empty */
	}

private:
	void attach(COMPOSITE* c)
	{
		assert(c);
		assert(!composite);
		composite = c;
		onAttachTo();
	}

	void detach(void)
	{
		assert(composite);
		onDetach();
		composite = NULL;
	}

	COMPOSITE* composite;
}; // Component

template<typename COMPOSITE>
class Composite // interface/base/member
{
	typedef std::list< Component<COMPOSITE>* > 
		Components;
	
	typedef typename std::list< Component<COMPOSITE>* >::iterator 
		ComponentsIter;
	
	typedef typename std::list< Component<COMPOSITE>* >::const_iterator
		ComponentsIterConst;
public:
	virtual
	~Composite(void)=0
	{
		std::for_each(components.begin(), components.end(), Composite<COMPOSITE>::deleteFunction);
	}

	void add(Component<COMPOSITE>& component) 
	{
		component.attach(static_cast<COMPOSITE*>(this));
		components.push_back(&component);
	}

	template<typename COMPONENT>
	bool has(void) const
	{
		for (ComponentsIterConst iter(components.begin()), sentinel(components.end()); iter != sentinel; ++iter)
		{
			if ((*iter)->getRunTimeType().IS_A(COMPONENT::runTimeType))
				return true;
		}

		return false;
	}

	void remove(Component<COMPOSITE>& component)
	{	
		assert(component.getComposite() == this);
		component.detach();
		components.erase(std::find(components.begin(), components.end(), &component));
	}
	
private:
	static void deleteFunction(Component<COMPOSITE>* object)
	{
		object->detach();
		delete object;
	}

	Components components;
}; // Composite

} // namespace designPatterns


#endif//COMPOSITION_H