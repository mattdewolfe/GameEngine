#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();

	bool Init();
	void Update(float _dt);
	void Shutdown();
};

#endif
