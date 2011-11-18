#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<typename ELEMENT>
class Array
{
public:
	Array(uint reservedSize=0)
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