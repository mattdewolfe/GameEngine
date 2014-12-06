#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <assert.h>
#include <Windows.h>
#include <iostream>
#include <sstream> 
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

// Macro for tracing event data names into output window
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s << "\n";                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();
	bool LoadScript(const char* _fileName);
	
	// Set a variable by passing in the variable name in script and the variable itself
	// The variable must be passed in to determine type to return
	// @Parem - node to look under, attribute name, variable type to return
	float GetVariableFromScript(char* _node, char* _name, float *var);
	int GetVariableFromScript(char* _node, char* _name, int *var);
	bool GetVariableFromScript(char* _node, char* _name, bool *var);
	std::string GetVariableFromScript(char* _node, char* _name, std::string *var);
	/*
	void CreateComponentFromScript(char* _name, ICompoment* comp);
	float SetVariableInScript(char* _name, float &var);
	int SetVariableInScript(char* _name, int &var);
	bool SetVariableInScript(char* _name, bool &var);
	*/
private:
	rapidxml::xml_document<> doc;
	rapidxml::file<>* xmlFile;
};

#endif