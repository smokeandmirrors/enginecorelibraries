#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include "Platform.h"

template<typename ELEMENT>
class Array
{
public:
	Array(uint reservedSize=0);
	~Array(void);
	
	ELEMENT&
		back(void);

	const ELEMENT&
		back(void) const;

	ELEMENT*
		begin(void);

	const ELEMENT*
		begin(void) const;

	void
		empty(void);

	void
		emptyAndDeallocate(void);
	
	ELEMENT*
		end(void);

	const ELEMENT*
		end(void) const;
	uint
		getCapacity(void) const;

	uint 
		getSize(void) const;

	bool 
		isEmpty(void) const;

	ELEMENT& 
		operator[](sint index);

	const ELEMENT&
		operator[](sint index) const;

	void
		pushRisky(const ELEMENT& object);

	void 
		pushSlowly(const ELEMENT& object);

	void 
		pop(void);

	void
		removeSlowly(sint index);
	
	void
		removeSlowly(sint index, sint numRemoved);

	void
		removeUnstable(sint index);
	
	void
		removeUnstable(sint index, sint numRemoved);

	bool
		setCapacity(sint capacity);

	bool
		setCapacityExactly(sint capacity);

	void
		setSizeRisky(sint newSize);

	void 
		setSizeSlowly(sint newSize);	

private:
	uint 
		capacity;

	uint
		size;

	ELEMENT*
		data;
};

#endif//ARRAY_H