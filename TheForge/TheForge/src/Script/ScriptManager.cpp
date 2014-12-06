#include "Script\ScriptManager.h"

ScriptManager::ScriptManager()
{
}

void ScriptManager::GetVariableFromScript(char* _name, float* var)
{
	rapidxml::xml_node<> *node = doc.first_node(_name);
	char* ret = node->value();
	float total;
	for (int i = 0; ret[i] != '\0'; i++)
	{
		total = (float)(ret[i] - '0');
	}
	var = &total;
}

void ScriptManager::GetVariableFromScript(char* _name, int* var)
{
	rapidxml::xml_node<> *node = doc.first_node(_name);
	int ret = (int)node->value();
	var = &ret;
}

void ScriptManager::GetVariableFromScript(char* _name, bool* var)
{
	rapidxml::xml_node<> *node = doc.first_node(_name);
	if (node->value() == "true")
	{ 
		*var = true;
	}
	else
	{
		*var = false;
	}
}

void ScriptManager::GetVariableFromScript(char* _name, char *var)
{
	rapidxml::xml_node<> *node = doc.first_node(_name);
	char* ret = node->value();
	var = ret;
}

bool ScriptManager::Init()
{
	LoadScript("scripts\\xmlTest.xml");
	return true;
}

bool ScriptManager::LoadScript(const char* _fileName)
{
	xmlFile = new rapidxml::file<>(_fileName);
	if (xmlFile != nullptr)
	{
		doc.parse<0>(xmlFile->data());
		return true;
	}
	return false;
}

void ScriptManager::Update(float _dt)
{

}

void ScriptManager::Shutdown()
{

}

// Global print function for string output
void PrintString(std::string &str)
{
	std::cout << str;
}


ScriptManager::~ScriptManager()
{

}
