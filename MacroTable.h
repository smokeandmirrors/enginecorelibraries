// initial
#define DEFINE_LUA_CLASS(TYPE, CLASS, SUPER_CLASS)

#define DEFINE_LUA_CLASS_BY_PROXY(TYPE, CLASS, SUPER_CLASS)

#define DEFINE_LUA_CLASS_NO_CTOR(TYPE, CLASS, SUPER_CLASS)

#define DEFINE_LUA_CLASS_NO_DTOR(TYPE, CLASS, SUPER_CLASS)

#define DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(TYPE, CLASS, SUPER_CLASS) 
	
#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) 	

#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NODTOR(TYPE, CLASS, SUPER_CLASS) 
	
#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NOCTOR_NODTOR(TYPE, CLASS, SUPER_CLASS) 
	
// library
#define DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS)

#define DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS)
	
// PROXY / PUBLIC_MEMBERS / CTOR / DTOR / 
inline bool CLASS##__newindexImplementation(##CLASS##& t, const char* k, lua_State* L, const char* className, const char* superClassName) 
{
	if (!strcmp(k, #INDEX)) { t.##INDEX = to<##TYPE##>(L, -1); pushTrue(L); return 1; }
	if (strcmp(className, superClassName)) 
	{	/* here would be a recursive call that would be never called */ 
		return SUPER_CLASS##__newindexImplementation(t, k, L, #CLASS, #SUPER_CLASS); 
	} 
	else 
	{ 
		pushFalse(L); 
		return 1; 
	} 
} 
LUA_FUNC(CLASS##__newindexSupport) 
{ 
	return CLASS##__newindexImplementation(to<##CLASS##&>(L, -3), to<const schar*>(L, -2), L, #CLASS, #SUPER_CLASS); 
} 
