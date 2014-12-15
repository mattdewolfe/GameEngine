#ifndef LUA_SCRIPT_MANAGER_H
#define LUA_SCRIPT_MANAGER_H

#include <vector>
#include <Windows.h>
#include <iostream>
#include <sstream> 
#include <string>
#include "ILuaScriptManager.h"

// Macro for tracing event data names into output window
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s << "\n";                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

// LUA Script manager setup as per the one presented
// in the textbook and slides

class LuaScriptManager : public ILuaScriptManager
{
	static LuaScriptManager* ptrSingleton;
	LuaPlus::LuaState* ptrLuaState;
	std::string lastError;
	

public:
	typedef std::vector<std::string> StringVec;

	static bool Create();
	static void Destroy();
	static LuaScriptManager* Get()
	{
		if (ptrSingleton != nullptr) { return ptrSingleton; }
	}

	virtual bool Init() override;
	virtual void VExecuteFile(const char* _resource) override;
	virtual void VExecuteString(const char* _str) override;

	LuaPlus::LuaObject GetGlobalVars();
    LuaPlus::LuaState* GetLuaState() const;

	// A few helper functions
	LuaPlus::LuaObject CreatePath(const char* pathString, bool toIgnoreLastElement = false);
	void Split(const std::string& str, StringVec& vec, char delimiter);
	void ScriptTest();

private:
    void SetError(int errorNum);
    void ClearStack();

    // private constructor & destructor; call the static Create() and Destroy() functions instead
    explicit LuaScriptManager();
    virtual ~LuaScriptManager();
};
#endif