#include "Script\ScriptManager.h"

ScriptManager::ScriptManager()
{

}

float ScriptManager::GetVariableFromScript(char* _node, char* _name, float* var)
{
	rapidxml::xml_node<>* parent = doc.first_node();
	rapidxml::xml_node<>* targetNode = parent->first_node(_name);
	char* ret = targetNode->value();
	float total = 0.0f;
	bool afterDecimal = false;
	for (int i = 0; ret[i] != '\0'; i++)
	{
		if (ret[i] == '.')
		{
			// If we find a second decimal place, break and ignore further values
			if (afterDecimal == true)
			{
				DBOUT("SCRIPT: Read float: Terminated early due to second decimal.");
				break;
			}
			afterDecimal = true;
		}
		else
		{
			if (afterDecimal == false)
				total += (float)(ret[i] - '0');
			else
				total += (float)(ret[i] - '0')/10;
		}
	}
	DBOUT("SCRIPT: Read float: " << total);
	return total;
}

int ScriptManager::GetVariableFromScript(char* _node, char* _name, int* var)
{
	rapidxml::xml_node<>* parent = doc.first_node();
	rapidxml::xml_node<>* targetNode = parent->first_node(_name);
	int ret = (int)targetNode->value();
	DBOUT("SCRIPT: Read int: " << targetNode->value());
	return ret;
}

bool ScriptManager::GetVariableFromScript(char* _node, char* _name, bool* var)
{
	rapidxml::xml_node<>* parent = doc.first_node();
	rapidxml::xml_node<>* targetNode = parent->first_node(_name);
	DBOUT("SCRIPT: Read bool: " << targetNode->value());
	if (targetNode->value() == "true")
	{ 
		
		return true;
	}
	else
	{
		return false;
	}
}

std::string ScriptManager::GetVariableFromScript(char* _node, char* _name, std::string* var)
{
	rapidxml::xml_node<>* parent = doc.first_node();
	rapidxml::xml_node<>* targetNode = parent->first_node(_name);
	std::string ret = targetNode->value();
	DBOUT("SCRIPT: Read string: " << targetNode->value());
	return ret;
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
	}
	DBOUT( "SCRIPT: Loaded " << doc.first_node()->name() << " script." );
	return false;
}

void ScriptManager::Update(float _dt)
{

}

void ScriptManager::Shutdown()
{
	doc.clear();

	delete xmlFile;
	xmlFile = nullptr;
}

// Global print function for string output
void PrintString(std::string &str)
{
	std::cout << str;
}


ScriptManager::~ScriptManager()
{

}
