#include "GUI\GUIManager.h"	

bool GUIManager::Init(int _screenWidth, int _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	pRootWindow = new GUIBox(Vector2(0,0), Vector2(screenWidth, screenHeight), D3DXCOLOR(1.0,1.0,1.0,0.0), GWT_BOX);
	return true;
}

/*
void GUIManager::Render()
{
	int s = elements.size();
	
	for(int i = 0; i < s; i++)
	{
		// Kayla,
		// Incomplete line, commented out for time being.
		// MD
		//GUIElementVertexData* data = 
	}
}*/

// seems silly, but can't think of any other way to keep rootWindow private and still add windows from outside GUIManager
bool GUIManager::AddWindow(GUIWindow* win)
{
	return pRootWindow->AddWindow(win);
}

void GUIManager::Shutdown()
{

}

void GUIManager::GetUpdatedVertices (Vertex* _vertices, UINT& _vertexCount)
{
	_vertexCount = 0;
	// iterate over every Window child of pRootWindow. Don't get the verts of pRootWindow itself because it is not intented to be rendered
	for (std::list<GUIWindow*>::const_iterator it = pRootWindow->m_ChildWindows.begin(), end = pRootWindow->m_ChildWindows.end(); it != end; ++it) 
	{
		(*it)->GetVertices(_vertices, _vertexCount, Vector2(0,0));
	}
}

/*
void GUIManager::AddElement(GUIElement _emt, float _txWidth, float _txHeight)
{

}*/

//void GUIManager::AddFont(std::string _name, FontSheet _sheet)
//{
//}

/*
void GUIManager::AddText(std::string _name, std::string _font)
{

}*/

/*
void GUIManager::DrawElementsUsingTexture(GUIElement _emt, GUIElementVertexData& _data)
{
	GUIElementVertexData v;
	BuildElementQuad(_emt, v);

	_data = v;
}*/

/*
void GUIManager::BuildElementQuad(GUIElement& _emt, GUIElementVertexData& _data)
{
	const Quad& dest = _emt.dest;
	const Quad& src = _emt.source;
	Vector2 localTextureDimensions = textureDimensions[_emt.GetTexture()];

	_data.position = PointToNDC(dest.xPos, dest.yPos);
	_data.dimensions = Vector2(dest.width / screenWidth * 2.0f, dest.height / screenWidth * 2.0f);
	_data.rgba = _emt.rgba;

	_data.source = Vector4(src.xPos / localTextureDimensions.x, src.height / localTextureDimensions.y, 
		src.width / localTextureDimensions.x, src.yPos / localTextureDimensions.y);
}*/

/*
void GUIManager::BuildTextElement(GUIText _text, GUIElementVertexData* _data)
{

}*/

/*
Vector2 GUIManager::PointToNDC(int _x, int _y)
{
	Vector2 out; 

	out.x = 2.0f * (float)_x / screenWidth - 1.0f; 
	out.y = 1.0f - 2.0f * (float)_y / screenHeight;

	return out;
}*/
