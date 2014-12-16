#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

//standard includes.
#include <map>
#include <vector>

//GUI related includes.
//#include "GUIElements.h"
#include "GUIStateManager.h"
#include "GUIBox.h"
#include "GUIButton.h"
#include "Vertex.h"

#include <map>

//Feedback includes.
//#include "GameEngine.h";

class GUIManager 
{
private:
	//a map of all current GUI elements.
	//std::vector<std::shared_ptr<GUIElement>> elements;
	//std::vector<std::shared_ptr<GUIText>> textElements;
	
	std::map<std::string, int> batchingIndexMap;
	//std::map<std::string, FontSheet> fontSheets;
	std::map<std::string, Vector2> textureDimensions;
	
	//event handling for GUI objects
	//EventManager* events;
	//GraphicsManager* graphics; 

	int screenWidth, screenHeight;

	// The root window. Does not render, simply holds all the GUI elements. 
	// TODO: find a better way to represent it than a GUIBox
	GUIBox* pRootWindow;

protected:
	//
public:
	GUIManager() {};
	~GUIManager() {}; 

	bool Init(int _screenWidth, int _screenHeight);
	void Render();
	void Shutdown();

	bool AddWindow(GUIWindow* win);

	GUIBox* GetRootWindow() { return pRootWindow; }

	void GetUpdatedVertices (Vertex* _vertices, UINT& _vertexCount);	
};

#endif

//KW