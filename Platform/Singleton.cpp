#include "Singleton.h"
#include <vector>

namespace designPatterns
{

SingletonController* singletonInitializers(NULL);

void createSingletons()
{
	SingletonController* initializer(singletonInitializers);

	std::vector<SingletonController*> initializationList;

	while (initializer)
	{	
		initializationList.push_back(initializer);
		initializer = initializer->next;
	}

	singletonInitializers = NULL;

	while (initializationList.size() > 0)
	{
		IF_DEBUG(size_t originalSize = initializationList.size();)
		
		for (size_t i(0); i < initializationList.size(); ++i)
		{
			initializer = initializationList[i];

			if (initializer->create())
			{	// chain up for destruction order
				initializer->next = singletonInitializers;
				singletonInitializers = initializer;				 
				// remove it from the creation list
				initializationList.erase(initializationList.begin() + i);
				--i;
			}
		}
		// at least one must be successful, or there is a problem with singleton construction dependency
		assert(originalSize != initializationList.size());
	} 
}

void destroySingletons()
{
	SingletonController* initializer(singletonInitializers);

	while (initializer)
	{
		initializer->destroy();
		initializer = initializer->next;
	}
}

} // namespace designPatterns