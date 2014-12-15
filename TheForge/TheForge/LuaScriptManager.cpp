#include <string>
#include "include\Script\LuaScriptManager.h"

LuaScriptManager* LuaScriptManager::ptrSingleton = NULL;

bool LuaScriptManager::Create(void)
{
    if (ptrSingleton != NULL)
    {
        delete ptrSingleton;
    }

    ptrSingleton = new LuaScriptManager();
    if (ptrSingleton != NULL)
        return ptrSingleton->Init();

    return false;
}

void LuaScriptManager::Destroy(void)
{
	delete ptrSingleton;
	ptrSingleton = NULL;
}

LuaScriptManager::LuaScriptManager(void)
{
    ptrLuaState = NULL;
}

LuaScriptManager::~LuaScriptManager(void)
{
    if (ptrLuaState)
    {
        LuaPlus::LuaState::Destroy(ptrLuaState);
        ptrLuaState = NULL;
    }
}

bool LuaScriptManager::Init(void)
{
    ptrLuaState = LuaPlus::LuaState::Create(true);
    if (ptrLuaState == NULL)
        return false;

    // register functions
    ptrLuaState->GetGlobals().RegisterDirect("ExecuteFile", (*this), &LuaScriptManager::VExecuteFile);
    ptrLuaState->GetGlobals().RegisterDirect("ExecuteString", (*this), &LuaScriptManager::VExecuteString);

    return true;
}

void LuaScriptManager::VExecuteFile(const char* path)
{
    int result = ptrLuaState->DoFile(path);
    if (result != 0)
        SetError(result);
}

void LuaScriptManager::VExecuteString(const char* chunk)
{
    int result = 0;

    if (strlen(chunk) <= 1 || chunk[0] != '=')
    {
        result = ptrLuaState->DoString(chunk);
        if (result != 0)
            SetError(result);
    }

    else
    {
        std::string buffer("print(");
        buffer += (chunk + 1);
        buffer += ")";
        result = ptrLuaState->DoString(buffer.c_str());
        if (result != 0)
            SetError(result);
    }
}

void LuaScriptManager::SetError(int errorNum)
{
  
    LuaPlus::LuaStackObject stackObj(ptrLuaState,-1);
    const char* errStr = stackObj.GetString();
    if (errStr)
    {
        lastError = errStr;
        ClearStack();
    }
    else
        lastError = "Unknown Lua parse error";
}

void LuaScriptManager::ClearStack(void)
{
    ptrLuaState->SetTop(0);
}

LuaPlus::LuaObject LuaScriptManager::GetGlobalVars(void)
{
    return ptrLuaState->GetGlobals();
}

LuaPlus::LuaState* LuaScriptManager::GetLuaState(void) const
{
    return ptrLuaState;
}
