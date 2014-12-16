#include "GUI\GUIButton.h"

GUIButton::GUIButton ()
{

}

GUIButton::GUIButton (Vector2 _pos, Vector2 _size, D3DXCOLOR _color, GUI_WINDOW_TYPE _type, bool _isVisible)
{
	m_Position = _pos;
	m_Size = _size;
	m_Color = _color;
	// lazy method for having buttons change colours
	// TODO make these 3 colours set by the user
	colors[0] = _color;
	_color.r *= 0.8;	_color.g *= 0.8;	_color.b *= 0.8;	
	colors[1] = _color;
	_color.r *= 1.2;	_color.g *= 1.2;	_color.b *= 1.2;
	colors[2] = _color;
	state = BS_NORMAL;
	m_IsVisible = _isVisible;
	m_pParent = NULL;
}

void GUIButton::Init ()
{

}

void GUIButton::OnClick(Vector2 _mousePosition)
{
	GUIWindow::PropogateOnClick(_mousePosition);
	m_Color = colors[1];
}

void GUIButton::OnMouseOver(Vector2 _mousePosition)
{
}

void GUIButton::OnRelease()
{
	m_Color = colors[0];
	for (std::list<GUIWindow*>::const_iterator it = m_ChildWindows.begin(), end = m_ChildWindows.end(); it != end; ++it) 
	{
		(*it)->OnRelease();
	}
}