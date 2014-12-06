#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

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
	void GetVariableFromScript(char* _name, float *var);
	void GetVariableFromScript(char* _name, int *var);
	void GetVariableFromScript(char* _name, bool *var);
	void GetVariableFromScript(char* _name, char *var);
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