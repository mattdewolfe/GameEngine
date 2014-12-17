#include "GUI\GUIWindow.h"

bool GUIWindow::AddWindow(GUIWindow *win)
{
	if (!win)
		return false;
	if (win->GetParent() == this) 
		return false;
	// should check if win has a parent and remove it from its childWindows list if it does
	win->SetParent(this);
	m_ChildWindows.push_back(win);
	return true;
}

bool GUIWindow::RemoveWindow(GUIWindow *win)
{
	// Check if window is in List, then remove and delete it
	return true;
}

// Checks if the coordinates are within the bounds of this window. 
bool GUIWindow::CheckBounds (Vector2 _localCoordinates)
{
	if (_localCoordinates.x > m_Position.x && _localCoordinates.x < m_Position.x + m_Size.x)
	{
		if (_localCoordinates.y > m_Position.y && _localCoordinates.y < m_Position.y + m_Size.y)
		{
			return true;
		}
	}
	return false;
}

void GUIWindow::GetVertices (Vertex* _vertices, UINT& _vertexCount, Vector2 _offset)
{
	// get this windows verts
	// first triangle	
	_vertices[_vertexCount] = Vertex(m_Position.x + _offset.x, m_Position.y + _offset.y, 0.0, m_Color);							// Top Left
	_vertexCount++;	
	_vertices[_vertexCount] = Vertex(m_Position.x + m_Size.x + _offset.x, m_Position.y + _offset.y, 0.0, m_Color);				// Top Right
	_vertexCount++;
	_vertices[_vertexCount] = Vertex(m_Position.x + _offset.x, m_Position.y + m_Size.y + _offset.y, 0.0, m_Color);				// Bottom Left
	_vertexCount++;
	// second triangle
	_vertices[_vertexCount] = Vertex(m_Position.x + m_Size.x + _offset.x, m_Position.y + _offset.y, 0.0, m_Color);				// Top Right
	_vertexCount++;
	_vertices[_vertexCount] = Vertex(m_Position.x + m_Size.x + _offset.x, m_Position.y + m_Size.y + _offset.y, 0.0, m_Color);	// Bottom Right
	_vertexCount++;
	_vertices[_vertexCount] = Vertex(m_Position.x + _offset.x, m_Position.y + m_Size.y + _offset.y, 0.0, m_Color);				// Bottom Left
	_vertexCount++;

	// get the verts of all child windows
	for (std::list<GUIWindow*>::const_iterator it = m_ChildWindows.begin(), end = m_ChildWindows.end(); it != end; ++it) 
	{
		(*it)->GetVertices(_vertices, _vertexCount, Vector2(_offset.x + m_Position.x, _offset.y + m_Position.y));
	}
}

void GUIWindow::PropogateOnClick(Vector2 _mousePosition) 
{
	Vector2 localPosition = _mousePosition;
	localPosition.x -= m_Position.x;
	localPosition.y -= m_Position.y;

	for (std::list<GUIWindow*>::const_iterator it = m_ChildWindows.begin(), end = m_ChildWindows.end(); it != end; ++it) 
	{
		if ((*it)->CheckBounds(localPosition))
		{			
			(*it)->OnClick(localPosition);
		}		
	}
}