#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();
};

#endif