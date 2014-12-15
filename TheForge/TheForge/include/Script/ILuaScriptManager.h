#ifndef I_LUA_SCRIPT_MANAGER_H
#define I_LUA_SCRIPT_MANAGER_H

#include <LuaPlus.h>

class ILuaScriptManager
{
public:
	ILuaScriptManager() { }
	virtual ~ILuaScriptManager() { }

	virtual bool Init() =0;
	virtual void VExecuteFile(const char* resource) =0;
	virtual void VExecuteString(const char* _str) =0;
};
#endif