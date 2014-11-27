#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

//standard includes.
#include <map>
#include <vector>

//GUI related includes.
#include "GUIElements.h"
#include "GUIStateManager.h"

//Feedback includes.
#include "GameEngine.h"

#include <map>

#define SCREENWIDTH 500
#define SCREENHEIGHT 400

class GUIManager 
{
private:
	//a map of all current GUI elements.
	std::vector<std::shared_ptr<GUIElement>> elements;
	std::vector<std::shared_ptr<GUIText>> textElements;
	
	std::map<std::string, int> batchingIndexMap;
	//std::map<std::string, FontSheet> fontSheets;
	std::map<std::string, Vector2> textureDimensions;

	//event handling for GUI objects
	EventManager* events;
	GraphicsManager* graphics; 
protected:
	//
public:
	GUIManager();
	~GUIManager(); 

	bool Init(GameEngine* _eng);
	void Render();
	void Shutdown();

	void AddElement(GUIElement _emt, float _txWidth, float _txHeight);
	//void AddFont(std::string _name, FontSheet _sheet);
	void AddText(std::string _name, std::string _font);

	void DrawElementsUsingTexture(GUIElement _emt, GUIElementVertexData& _data);
	void BuildElementQuad(GUIElement& _emt, GUIElementVertexData& _data);
	void BuildTextElement(GUIText _text, GUIElementVertexData* _data);

	Vector2 PointToNDC(int _x, int _y);
};

#endif

//KW