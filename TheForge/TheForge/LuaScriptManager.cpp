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
		// Given an error when trying to call destroy on the state
		// LuaPlus::LuaState::Destroy(ptrLuaState);
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
	ptrLuaState->GetGlobals().RegisterDirect("ScriptTest", (*this), &LuaScriptManager::ScriptTest);
    return true;
}

void LuaScriptManager::ScriptTest(void)
{
	DBOUT("LUA: Called ScripTest from script");
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

LuaPlus::LuaObject LuaScriptManager::CreatePath(const char* pathString, bool toIgnoreLastElement)
{
	StringVec splitPath;
    Split(pathString, splitPath, '.');
    if (toIgnoreLastElement)
        splitPath.pop_back();

    LuaPlus::LuaObject context = GetGlobalVars();
    for (auto it = splitPath.begin(); it != splitPath.end(); ++it)
    {
        // make sure we still have a valid context
        if (context.IsNil())
        {
            return context;  // this will be nil
        }

        // grab whatever exists for this element
        const std::string& element = (*it);
        LuaPlus::LuaObject curr = context.GetByName(element.c_str());

        if (!curr.IsTable())
        {
            // if the element is not a table and not nil, we clobber it
            if (!curr.IsNil())
            {
                context.SetNil(element.c_str());
            }

            // element is either nil or was clobbered so add the new table
            context.CreateTable(element.c_str());
        }

        context = context.GetByName(element.c_str());
    }

    // if we get here, we have created the path
    return context;
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

void LuaScriptManager::Split(const std::string& str, StringVec& vec, char delimiter)
{
	vec.clear();
	size_t strLen = str.size();
	if (strLen == 0)
		return;

	size_t startIndex = 0;
	size_t indexOfDel = str.find_first_of(delimiter, startIndex);
	while (indexOfDel != std::string::npos)
	{
		vec.push_back(str.substr(startIndex, indexOfDel-startIndex));
		startIndex=indexOfDel + 1;
		if (startIndex >= strLen)
			break;
		indexOfDel = str.find_first_of(delimiter, startIndex);
	}
	if(startIndex < strLen)
		vec.push_back(str.substr(startIndex));
}
