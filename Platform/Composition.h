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
#include "Synchronization.h"

namespace designPatterns
{

typedef uint Component_GUID;

template<typename OWNER>
class AbstractComponent
{
	template<typename OWNER> friend class Composite;

public:
	AbstractComponent(void)
	: m_owner(NULL)
	{
		/* empty */
	}

	virtual
	~AbstractComponent(void)=0
	{
		/* empty */
	}

	virtual 
	Component_GUID
	getGUID(void) const=0;

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
}; // Component

template<typename OWNER, typename DERIVED_CLASS>
class Component : public AbstractComponent<OWNER>
{
public:
	static const Component_GUID componentGUID;

	Component_GUID 
	getGUID(void) const
	{
		return componentGUID;
	}
}; // Component

template<typename OWNER, typename DERIVED_CLASS> 
const Component_GUID Component<OWNER, DERIVED_CLASS>::componentGUID = __COUNTER__;

template<typename OWNER>
class Composite // interface/base/member
{
	typedef std::map<uint, AbstractComponent<OWNER>*> 
		components;
	
	typedef typename std::map<uint, AbstractComponent<OWNER>*>::iterator 
		components_iter;
	
public:
	virtual
	~Composite(void)=0
	{
		/* empty */
	}

	void
	add(AbstractComponent<OWNER>& component) 
	{
		//typeid(component)
		uint id = 0; //component.getComponentID();

		if (!m_components[id])
		{
			m_components[id] = &component;
			component.attach(static_cast<OWNER*>(this));
		}
	}
	
	template<typename COMPONENT> 
	COMPONENT* 
	get(bool construct_missing=false)
	{
		uint id = COMPONENT::componentGUID;
		AbstractComponent<OWNER>* component = m_components[id];
		
		if (!component && construct_missing)
		{
			component = new COMPONENT();
			component->attach(static_cast<OWNER*>(this));
		}

		return static_cast<COMPONENT*>(component);
	}

	template<typename COMPONENT>
	bool 
	has(void) const
	{
		return m_components.find(COMPONENT::componentGUID) != m_components.end();
	}
	
	void 
	remove(AbstractComponent<OWNER>& component)
	{
		components_iter iter = m_components.find(component.getGUID());
		
		if (iter != m_components.end())
		{
			m_components.erase(iter);
		}
	}
	
private:
	components	
		m_components;
}; // Composite

} // namespace designPatterns


#endif//COMPOSITION_H