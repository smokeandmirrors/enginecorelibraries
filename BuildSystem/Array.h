#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<typename ELEMENT>
class Array
{
public:
	Array(void)
		: size(0)
		, data(NULL)
	{
		
	}

private:
	uint
		size;
	
	ELEMENT*
		data;
};

#endif//ARRAY_H