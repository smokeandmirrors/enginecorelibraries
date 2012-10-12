#pragma once
#ifndef RUN_TIME_TYPE_H
#define RUN_TIME_TYPE_H

#include "Platform.h"

#define DEFINE_TEMPLATE_BASE_RUN_TIME_TYPE(TEMPLATE, CLASS_NAME, ...) \
	template<typename TEMPLATE> const designPatterns::RunTimeType* const CLASS_NAME <TEMPLATE>::interfaces[] = { __VA_ARGS__ }; \
	template<typename TEMPLATE> const designPatterns::RunTimeType CLASS_NAME <TEMPLATE>::runTimeType(NULL, CLASS_NAME <TEMPLATE>::interfaces);

#define DEFINE_TEMPLATE_DERIVED_RUN_TIME_TYPE(TEMPLATE, CLASS_NAME, SUPER_CLASS_NAME, ...) \
	template<typename TEMPLATE> const designPatterns::RunTimeType* const CLASS_NAME <TEMPLATE>::interfaces[] = { __VA_ARGS__ }; \
	template<typename TEMPLATE> const designPatterns::RunTimeType CLASS_NAME <TEMPLATE>::runTimeType(& SUPER_CLASS_NAME::runTimeType, CLASS_NAME <TEMPLATE>::interfaces);

#define BASE_RUN_TIME_TYPE_DEFINITION(CLASS_NAME, ...) \
	const designPatterns::RunTimeType* const CLASS_NAME::interfaces[] = { __VA_ARGS__ }; \
	const designPatterns::RunTimeType CLASS_NAME::runTimeType(NULL, CLASS_NAME::interfaces);

#define DERIVED_RUN_TIME_TYPE_DEFINITION(CLASS_NAME, SUPER_CLASS_NAME, ...) \
	const designPatterns::RunTimeType* const CLASS_NAME::interfaces[] = { __VA_ARGS__ }; \
	const designPatterns::RunTimeType CLASS_NAME::runTimeType(& SUPER_CLASS_NAME::runTimeType, CLASS_NAME::interfaces);

#define RUN_TIME_TYPE_DECLARATION \
	public: \
	static const designPatterns::RunTimeType runTimeType; \
	virtual const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; } \
	private: \
	static const designPatterns::RunTimeType* const interfaces[];

namespace designPatterns
{
	typedef const class RunTimeType* const* Interfaces;

	class RunTimeType
	{
	public:
		/** all RunTimeType objects are statically initialized */
		RunTimeType(const RunTimeType* const parentClassNullIfThisIsBase, Interfaces nullTerminatedInterfaceArray)
			: super(parentClassNullIfThisIsBase)
			, interfaces(nullTerminatedInterfaceArray)
		{
			/* empty */
		}

		/** operates on classes and interfaces of the type and the hierarchy */
		bool IS_A(const RunTimeType& otherType) const
		{
			const RunTimeType* thisType(this);

			do 
			{	// check the class hierarchy
				if (thisType == &otherType)
				{
					return true;
				}
				assert(interfaces);
				// check the interface implementation
				Interfaces interface = &interfaces[0];
				while (*interface)
				{
					if (*interface == &otherType)
					{
						return true;
					}
					else
					{
						*++interface;
					}
				}
				// check the next class
				thisType = thisType->super;
			} 
			while (thisType);
			// IS-A test is falls
			return false;
		}

		/** operates on the class of the type only */
		bool IS_EXACTLY(const RunTimeType& type) const 
		{ 
			return this == &type; 
		}

	private:
		RunTimeType(const RunTimeType&);
		RunTimeType operator=(const RunTimeType&);

		Interfaces interfaces; // = { *, *, *, *, NULL}
		const RunTimeType* const super;
	}; // class RunTimeType
} // namespace designPatterns

#endif//RUN_TIME_TYPE_H