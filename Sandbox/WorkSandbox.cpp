#include "Platform.h"
#include "WorkSandbox.h"
#include <vector>

/*

struct Instance
{
	int dummyData;
}; 

typedef int ZoneComponentTypeID;

struct ComponentBirthResult 
{
	const Component::AttachAction action;
	const Component& component;
}; // struct ComponentBirthResult 

typedef ComponentBirthResult (*OnBirth)(Instance& instance, void* data);
typedef void (*OnRemove)(int ComponentID);
typedef void (*Process)(void);

std::vector<OnBirth> birthFunctions;
std::vector<OnRemove> removeFunctions;
std::vector<Process> processFunctions;


class ComponentManagerController* componentManagerControllers(NULL);

class ComponentManagerController
{
public:
	ComponentManagerController* next;

	ComponentManagerController(void)
	{
		next = componentManagerControllers;
		componentManagerControllers = this;
	}

	virtual ~ComponentManagerController(void) { // empty};
	virtual void AddToBirthFunctions(void) const=0;
	virtual void AddToRemoveFunctions(void) const=0;
	virtual void AddToProcessFunctions(void) const=0;
	virtual bool CallBirthFunction(void) const=0;
	virtual bool CallProcessFunction(void) const=0;
	virtual bool CallRemoveFunction(void) const=0;
	virtual bool Create(void) const=0;
	virtual void Destroy(void) const=0;
	virtual bool IsInitialized(void) const=0;
	virtual void Process(void)const=0;

}; // class ComponentManagerController

template<typename COMPONENT_TYPE>
class CustomComponentManagerController : public ComponentManagerController
{
public:
	virtual void AddToBirthFunctions(void) const
	{
		AddToProcessFunctions<COMPONENT_TYPE::CallBirth>::Internal<COMPONENT_TYPE>::Do(); 
	}

	virtual void AddToRemoveFunctions(void) const
	{

	}

	virtual void AddToProcessFunctions(void) const
	{

	}

	virtual bool CallBirthFunction(void) const
	{
		return COMPONENT_TYPE::CallBirth;
	}

	virtual bool Create(void) const
	{
		ComponentManager<COMPONENT_TYPE>::Create();
	}

	virtual void Destroy(void) const
	{
		ComponentManager<COMPONENT_TYPE>::Destroy();
	}

	virtual bool IsInitialized(void) const
	{
		return COMPONENT_TYPE::IsInitialized();
	}
}; // class CustomComponentManagerController


ComponentManagerController* GetManagerBirthFunction(int )
{
	return NULL;
}

ComponentManagerController* GetManagerRemoveFunction(int )
{
	return NULL;
}

void CreateComponentManagers(void)
{
	ComponentManagerController* controller(componentManagerControllers);

	std::vector<ComponentManagerController*> controllerList;
	while (controller)
	{
		controllerList.push_back(controller);
		controller = controller->next;
	}

	componentManagerControllers = NULL;

	while (!controllerList.empty())
	{
		size_t originalSize = controllerList.size();

		for (size_t i(0); i < controllerList.size(); ++i)
		{
			controller = controllerList[i];

			if (controller->Create())
			{	
				controller->AddToBirthFunctions();
				controller->AddToRemoveFunctions();
				controller->AddToProcessFunctions();

				// chain up for destruction order
				controller->next = componentManagerControllers;
				componentManagerControllers = controller;				 
				// remove it from the creation list
				controllerList.erase(controllerList.begin() + i);
				// set to the proper list index
				--i;
			}
		}
		// at least one must be successful, or there is a problem with singleton construction dependency
		assert(originalSize != controllerList.size());
	}
}

void DestroySimpleComponentManagers(void)
{

}


typedef enum ProcessType 
{
	None,
	PerComponent,
	PerInstance
};

template<ProcessType PROCESS_TYPE>
struct AddToProcessFunctions2
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{	// static assert
			switch(0){case 0:case 0:;} 
		}
	}; // struct ProcessCaller::Internal
};

template<>
struct AddToProcessFunctions2<None>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			// empty // add nothing, there is no process function
		}
	}; // struct ProcessCaller::Internal
};

template<>
struct AddToProcessFunctions2<PerComponent>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			// add to component processing functions
		}
	}; // struct ProcessCaller::Internal
};

template<>
struct AddToProcessFunctions2<PerInstance>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			// add to instance functions (that get added to the instance on its birth)
		}
	}; // struct ProcessCaller::Internal
};

template<bool CALL_PROCESS>
struct AddToProcessFunctions
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			processFunctions.push_back(&ComponentManager<COMPONENT_TYPE>::Process);
		}
	}; // struct ProcessCaller::Internal
}; // struct ProcessCaller<typename CALL_PROCESS>

template<>
struct AddToProcessFunctions<false>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			// empty
		}
	}; // sturct ProcessCaller::Internal
}; // struct ProcessCaller<false>

template<bool CALL_BIRTH_FUNCTION>
struct AddToBirthFunctions
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			ZoneComponentTypeID key = COMPONENT_TYPE::GetComponentTypeID();
			birthFunctions.push_back(&COMPONENT_TYPE::InstanceBirth);
		}
	}; // struct BirthFunctionCaller::Internal
}; // struct BirthFunctionCaller<typename CALL_BIRTH_FUNCTION>

template<>
struct AddToBirthFunctions<false>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{
			
		}
	}; // sturct BirthFunctionCaller::Internal
}; // struct BirthFunctionCaller<false>

template<bool CALL_DESTROY_FUNCTION>
struct AddToRemoveFunctions
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void Do(void)
		{	
			ZoneComponentTypeID key = COMPONENT_TYPE::GetComponentTypeID();
			removeFunctions.push_back(&COMPONENT_TYPE::RemoveComponent);
		}
	}; // struct DestroyFunctionCaller::Internal
}; // struct DestroyFunctionCaller<typename CALL_DESTROY_FUNCTION>

template<>
struct AddToRemoveFunctions<false>
{
	template<typename COMPONENT_TYPE>
	struct Internal
	{
		static inline void FunctionCall(void)
		{
			// empty
		}
	}; // struct DestroyFunctionCaller::Internal
}; // struct DestroyFunctionCaller<false>


class Component
{
public:
}; 


class MyDependency : public Component 
{
	public:
	// put this in a macro
	
	static const bool CallProcess;
	static const int MaxNumber;
	static const ZoneComponentTypeID GetComponentTypeID(void) { return 0; }
	static const char* GetName(void) { return "MyDependency"; }
	

	// static bool CallBirth=true;
	// static bool CallDestroy=true;

protected:
	static void InstanceBirth(Instance& , void* )
	{
		
	}
	
	void Process(void)
	{

	}
};

const int MyDependency::MaxNumComponents = 1 ;
const bool MyDependency::CallProcess = true ;


class MyComponent : public Component // EasyComponent
{
public:
	// put this in a macro
	static bool CallProcess;
	static int MaxNumComponents;
	static const ZoneComponentTypeID GetComponentTypeID(void) { return 0; }
	static const char* GetName(void) { return "MyComponent"; }
	friend class ComponentManager<MyComponent>;
	void InitInstance(Instance& instance) { SetInstance(instance); }
	// static bool CallBirth=true;
	// static bool CallDestroy=true;

protected:
	static void InstanceBirth(Instance& instance, void*)
	{
// 		ComponentManager<MyDependency>::GetDependency(instance);
// 		
// 		CDC_ASSERT(data);
// 		dtp::MyComponent* mycomp = static_cast<dtp::MyComponent*>(data);
// 		MyComponent* component = GenericComponentManager<MyComponent>.AddComponent(instance);
// 		MyComponent.Attach(instance, component);
// 		MyDependency* depedency = GenericComponentManager<MyDependency>.AddComponent(instance);
// 		component.SetDependency(depedency);
		
	}
	
	
	void Process(void)
	{

	}

	
	void Init(Instance& instance);
}; // class MyComponent



bool MyComponent::CallProcess = true;

*/

namespace sandbox 
{

	class HasMaxNumber
	{
	public:
		static const int MaxNumber;
	};

	const int HasMaxNumber::MaxNumber = 0;

	template<typename TYPE_WITH_NUMBER>
	class MustWork
	{
	public:
		int onlyMethod(void) const { return TYPE_WITH_NUMBER::MaxNumber; }
	};
// 
// 	template<typename TEST_SELECTOR>
// 	struct AutoSelect
// 	{
// 		template<bool DO_SOMETHING>
// 		struct DoBase
// 		{
// 			static void Do(void)
// 			{
// 				int i = 0;
// 				++i;
// 			}
// 		};
// 
// 		template<>
// 		struct DoBase<false>
// 		{
// 			static void Do(void)
// 			{
// 				int i = 0;
// 				--i;
// 			}
// 		};
// 
// 		void Do()
// 		{
// 			DoBase<TEST_SELECTOR::DoSelection>::Do();
// 		}
// 	};

	

	class ParentClass
	{
		template<typename ANY>
		friend class SomeOtherClass;

	public:

		static bool DoSelection;
		void myPublicMethod() {}

	protected:
		void myProtectedMethod() {}

	private:
		void myPrivateMethod() {}
	};
	
	bool ParentClass::DoSelection = false;

	class ChildClass : public ParentClass
	{
		//friend class SomeOtherClass;
	public:
		void myPublicMethod() {}

	
	};

	template <typename ANY>
	class SomeOtherClass
	{
	public:
		void OnlyMethod()
		{
			ChildClass cc;
			cc.myProtectedMethod();
			cc.myPrivateMethod();
		}
	private:
		ANY m_member;
	}; 

	template<int NUMBER>
	struct SomeTemplate
	{
		template<typename COMPONENT>
		static inline void BirthFunctions(void)
		{
			// empt
		}

		int numbers[NUMBER];
	};

	template<>
	struct SomeTemplate<5>
	{
		template<typename COMPONENT>
		static inline void BirthFunctions(void)
		{
			int i = 0;
			++i;
			printf("%d", i);
		}

		int numbers[6];
	};


	template<>
	struct SomeTemplate<2>
	{
		template<typename COMPONENT>
		static inline void BirthFunctions(void)
		{
			int i = 0;
			++i;
			printf("%d", i);
		}

		int numbers[2];
	};


	void runWorkSandbox(void)
	{
		SomeOtherClass<int> soc;
		soc.OnlyMethod();

		SomeTemplate<10> st;
		st.numbers[0] = 1;

		SomeTemplate<10>::BirthFunctions<ChildClass>();
		SomeTemplate<5> st5;
		st5.numbers[5] = 1;
		SomeTemplate<5>::BirthFunctions<ChildClass>();


		// AutoSelect<ParentClass> as;
		// as.Do();
		// CreateComponentManagers();
	}
} // namespace sandbox
