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
#include "Build.h"
#include "Synchronization.h"

namespace design_patterns
{

template<typename OWNER>
class Component
{
public:
	static 
	uint4 
	staticGetComponentID(void)
	{ 
		return __COUNTER__;
	}

	virtual
	~Component(void)=0
	{
		/* empty */
	}

	void 
	attach(OWNER* owner)
	{
		assert(owner);
		m_owner = owner;
		onAttachTo();
	}
	
	void 
	detach(void)
	{
		onDetach();
		m_owner = NULL;
	}
	
	uint4 
	getComponentID(void) const
	{
		return staticGetComponentID();
	}

	const OWNER* 
	getOwner(void) const
	{
		return m_owner;
	}

protected:
	virtual 
	void 
	onAttachTo(void)
	{
		/* empty */
	}

	virtual 
	void 
	onDetach(void)
	{
		/* empty */
	}

private:
	OWNER*	m_owner;
}; // Component
 
template<typename OWNER>
class Composite // interface/base/member
{
	typedef std::map<uint4, Component<OWNER>*> 
		components;
	
	typedef typename std::map<uint4, Component<OWNER>*>::iterator 
		components_iter;
	
public:
	virtual
	~Composite(void)=0
	{
		/* empty */
	}

	void
	add(Component<OWNER>* component) 
	{
		uint4 id = component->getComponentID();

		if (!m_components[id])
		{
			m_components[id] = component;
			component->attach(static_cast<OWNER*>(this));
		}
	}
	
	template<typename COMPONENT> 
	COMPONENT* 
	get(bool construct_missing=false)
	{
		uint4 id = COMPONENT::staticGetComponentID();
		Component<OWNER>* component = m_components[id];
		
		if (!component && construct_missing)
		{
			component = new COMPONENT();
			component->attach(static_cast<OWNER*>(this));
		}

		return static_cast<COMPONENT>(component);
	}

	template<typename COMPONENT>
	bool 
	has(void) const
	{
		return m_components.find(COMPONENT::staticGetComponentID()) != m_components.end();
	}
	
	void 
	remove(Component<OWNER>* component)
	{
		components_iter iter = m_components.find(component->getComponentID());
		
		if (iter != m_components.end())
		{
			m_components.erase(iter);
		}
	}
	
private:
	components	
		m_components;
}; // Composite

} // namespace design_patterns


#endif//COMPOSITION_H