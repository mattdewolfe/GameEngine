#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

class DebugManager
{
public:
	DebugManager();
	~DebugManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();
};

#endif