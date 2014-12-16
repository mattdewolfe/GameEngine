#include "GUI\GUIBox.h"

GUIBox::GUIBox ()
{

}

GUIBox::GUIBox (Vector2 _pos, Vector2 _size, D3DXCOLOR _color, GUI_WINDOW_TYPE _type, bool _isVisible)
{
	m_Position = _pos;
	m_Size = _size;
	m_Color = _color;
	m_IsVisible = _isVisible;
	m_pParent = NULL;
	m_Type = _type;
}

void GUIBox::Init ()
{
}

void GUIBox::OnClick(Vector2 _mousePosition)
{
	GUIWindow::PropogateOnClick(_mousePosition);
}

void GUIBox::OnMouseOver(Vector2 _mousePosition)
{
}

void GUIBox::OnRelease()
{
	for (std::list<GUIWindow*>::const_iterator it = m_ChildWindows.begin(), end = m_ChildWindows.end(); it != end; ++it) 
	{
		(*it)->OnRelease();
	}
}