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

/// \todo activate/deactivate pause/play functions

namespace designPatterns
{

typedef uint Component_GUID;

template<typename OWNER>
class Component
{
	template<typename OWNER> friend class Composite;

public:
	Component(void)
	: m_owner(NULL)
	{
		/* empty */
	}
	
	virtual ~Component(void)
	{
		/* empty */
	}

	const OWNER* getOwner(void) const
	{
		return m_owner;
	}

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
	void attach(OWNER* owner)
	{
		assert(owner);
		assert(!m_owner);
		m_owner = owner;
		onAttachTo();
	}

	void detach(void)
	{
		assert(m_owner);
		onDetach();
		m_owner = NULL;
	}

	OWNER* m_owner;
}; // Component

template<typename OWNER>
class Composite // interface/base/member
{
	typedef std::list< Component<OWNER>* > 
		components;
	
	typedef typename std::list< Component<OWNER>* >::iterator 
		components_iter;
	
public:
	virtual
	~Composite(void)=0
	{
		std::for_each(m_components.begin(), m_components.end(), Composite<OWNER>::deleteFunction);
	}

	void add(Component<OWNER>& component) 
	{
		component.attach(static_cast<OWNER*>(this));
		m_components.push_back(&component);
	}
	
	void remove(Component<OWNER>& component)
	{	
		assert(component.getOwner() == this);
		component.detach();
		m_components.erase(std::find(m_components.begin(), m_components.end(), &component));
	}
	
private:
	static void deleteFunction(Component<OWNER>* object)
	{
		object->detach();
		delete object;
	}
	
	components m_components;
}; // Composite

} // namespace designPatterns


#endif//COMPOSITION_H