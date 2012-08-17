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


THIS FUNCTIONALITY IS NOT THREAD SAFE!

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
#include <vector>

#include "Synchronization.h"
#include "Singleton.h"

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
				while (*++interface);
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

template<typename COMPOSITE>
class Component
{
	template<typename COMPOSITE> friend class Composite;
	// make a singleton for class based component grain management?
public:
	Component(void)
	: composite(NULL)
	, thisIsActive(false)
	{
		/* empty */
	}
	
	virtual ~Component(void)
	{
		assert(!isActive());
		assert(!isAttached());
	}

	inline void activate(void)
	{	
		assert(isAttached());
		if (!thisIsActive)
		{
			thisIsActive = true;
			onActivate();
		}
	}

	inline void deactivate(void)
	{
		if (thisIsActive)
		{
			thisIsActive = false;
			onDeactivate();
		}
	}

	inline const COMPOSITE* getComposite(void) const
	{
		return composite;
	}

	inline int getID(void) const
	{
		return ID:
	}

	virtual const RunTimeType& getRunTimeType(void) const=0;

	inline bool isActive(void) const
	{
		return thisIsActive;
	}

	inline bool isAttached(void) const
	{
		return composite != NULL;
	}

	virtual void update(void)
	{
		/* empty */
	}

protected:
	virtual void onActivate(void)
	{
		/* empty */
	}

	virtual void onAttach(void)
	{
		/* empty */
	}

	virtual void onDeactivate(void)
	{
		/* empty */
	}

	virtual void onDetach(void)
	{
		/* empty */
	}

private:
	inline void attach(COMPOSITE* c)
	{
		assert(c);
		assert(!composite);
		composite = c;
		onAttach();
		activate();
	}
	
	inline void detach(void)
	{
		assert(composite);
		deactivate();
		onDetach();
		composite = NULL;
	}

	COMPOSITE* composite;
	int ID;
	bool thisIsActive;
}; // Component

template<typename COMPOSITE>
class Composite // interface/base/member
{
	typedef std::list< Component<COMPOSITE>* > Components;
	typedef typename std::list< Component<COMPOSITE>* >::iterator ComponentsIter;
	typedef typename std::list< Component<COMPOSITE>* >::const_iterator ComponentsIterConst;

public:
	~Composite(void)
	{
		std::for_each(components.begin(), components.end(), &Composite<COMPOSITE>::detachAndDelete);
	}

	template<typename COMPONENT>
	void activate(void)
	{
		if (COMPONENT* component = find<COMPONENT>())
		{
			component->activate();
		}
	}
	
	template<typename COMPONENT>
	void activateUnchecked(void)
	{
		assert(has<COMPONENT>());
		find<COMPONENT>()->activate();
	}

	void add(Component<COMPOSITE>& component)
	{
		if (!(has(component.getRunTimeType()) || component.isAttached()))
		{
			insert(component);
		}
	}

	void addUnchecked(Component<COMPOSITE>& component) 
	{
		assert(!(has(component.getRunTimeType()) || component.isAttached()));
		insert(component);
	}
	
	template<typename COMPONENT>
	void deactivate(void)
	{
		if (COMPONENT* component = find<COMPONENT>())
		{
			component->activate();
		}
	}

	template<typename COMPONENT>
	COMPONENT* get(void) const
	{
		return find<COMPONENT>();
	}

	inline int getID(void) const
	{
		return ID;
	}

	template<typename COMPONENT>
	COMPONENT* getOrCreate(void)
	{
		COMPONENT* component(find<COMPONENT>());
		
		if (!component)
		{
			component = new COMPONENT;
			insert(*component);
		}

		return component;
	}

	bool has(const RunTimeType& componentType) const
	{
		return find(componentType) != NULL;
	}

	template<typename COMPONENT>
	bool has(void) const
	{
		return find(COMPONENT::runTimeType) != NULL;
	}

	template<typename COMPONENT>
	bool isActive(void) const
	{
		COMPONENT* component = find<COMPONENT>();
		return component && component->isActive();
	}	

	template<typename COMPONENT>
	void remove(bool destroy=false)
	{
		for (ComponentsIter iter(components.begin()), sentinel(components.end()); iter != sentinel; ++iter)
		{
			if ((*iter)->getRunTimeType().IS_A(COMPONENT::runTimeType))
			{
				(*iter)->detach();
				
				if (destroy)
				{
					delete (*iter);
				}

				components.erase(iter);
				break;
			}
		}
	}

	void update(void)
	{
		std::for_each(components.begin(), components.end(), &Composite<COMPOSITE>::callUpdate);
	}
		
private:
	static void detachAndDelete(Component<COMPOSITE>* component)
	{
		component->detach();
		delete component;
	}

	static void callUpdate(Component<COMPOSITE>* component)
	{
		component->update();
	}

	Component<COMPOSITE>* find(const RunTimeType& componentType) const
	{
		for (ComponentsIterConst iter(components.begin()), sentinel(components.end()); iter != sentinel; ++iter)
		{
			if ((*iter)->getRunTimeType().IS_A(componentType))
			{
				return *iter;
			}
		}

		return NULL;
	}

	template<typename COMPONENT>
	COMPONENT* find(void) const
	{
		return static_cast<COMPONENT*>(find(COMPONENT::runTimeType));
	}

	inline void insert(Component<COMPOSITE>& component) 
	{
		component.attach(static_cast<COMPOSITE*>(this));
		components.push_back(&component);
	}

	Components components;
	Components updateComponents;
	int ID;
}; // Composite

template<typename UPDATER>
class UpdateManager
	: public Singleton< UpdateManager<UPDATER> >
{
	friend class designPatterns::Singleton< UpdateManager<UPDATER> >;

public:
	void add(UPDATER* updater)
	{
		updaters.push_back(updater);
	}

	void remove(UPDATER* updater)
	{
		updaters.remove(updaters.find(updater));
	}

	void update(void)
	{
		std::for_each(updaters.begin(), updaters.end(), &UpdateManager<UPDATER>::callUpdate);
	}

protected:
	static void callUpdate(UPDATER* updater)
	{
		updater->update();
	}

	static UpdateManager<UPDATER>* createSingleton(void) 
	{ 
		return new UpdateManager<UPDATER>; 
	}

private:
	std::vector<UPDATER*> updaters;
}; // UpdateManager

} // namespace designPatterns


#endif//COMPOSITION_H