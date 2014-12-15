#ifndef LUA_SCRIPT_MANAGER_H
#define LUA_SCRIPT_MANAGER_H

#include "ILuaScriptManager.h"

// LUA Script manager setup as per the one presented
// in the textbook and slides

class LuaScriptManager : public ILuaScriptManager
{
	static LuaScriptManager* ptrSingleton;
	LuaPlus::LuaState* ptrLuaState;
	std::string lastError;

public:
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
    
private:
    void SetError(int errorNum);
    void ClearStack();

    // private constructor & destructor; call the static Create() and Destroy() functions instead
    explicit LuaScriptManager();
    virtual ~LuaScriptManager();
};
#endif