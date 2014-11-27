#include "GUI\GUIManager.h"	

bool GUIManager::Init(GameEngine* _eng)
{
	return true;
}
void GUIManager::Render()
{
	int s = elements.size();
	
/*	for(int i = 0; i < s; i++)
	{
		GUIElementVertexData* data = 
	}*/
}

void GUIManager::Shutdown()
{
}

void GUIManager::AddElement(GUIElement _emt, float _txWidth, float _txHeight)
{
}

//void GUIManager::AddFont(std::string _name, FontSheet _sheet)
//{
//}

void GUIManager::AddText(std::string _name, std::string _font)
{
}

void GUIManager::DrawElementsUsingTexture(GUIElement _emt, GUIElementVertexData& _data)
{
	GUIElementVertexData v;
	BuildElementQuad(_emt, v);

	_data = v;
}

void GUIManager::BuildElementQuad(GUIElement& _emt, GUIElementVertexData& _data)
{
	/* Commented out - breaks everything
	const Quad& dest = _emt.dest;
	const Quad& src = _emt.source;
	Vector2 localTxtDimensions = textureDimensions[_emt.GetTexture()];

	_data.position = PointToNDC(dest.xPos, dest.yPos);
	_data.dimensions = Vector2(dest.width / SCREENWIDTH * 2.0f, dest.height / SCREENWIDTH * 2.0f);
	_data.rgba = _emt.rgba;

	_data.source = Vector4(src.xPos / localTxtDimensions.x, src.height / localTxtDimensions.y, src.width / localTxtDimensions.x, src.yPos / localTxtDimensions.y);*/
}

void GUIManager::BuildTextElement(GUIText _text, GUIElementVertexData* _data)
{

}

Vector2 GUIManager::PointToNDC(int _x, int _y)
{
	Vector2 out; 

	out.x = 2.0f * (float)_x / SCREENWIDTH - 1.0f; 
	out.y = 1.0f - 2.0f * (float)_y / SCREENHEIGHT;

	return out;
}