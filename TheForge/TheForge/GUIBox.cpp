#include "GUIBox.h"

GUIBox::GUIBox ()
{

}

GUIBox::GUIBox (Vector2 _pos, Vector2 _size, IGUIWindow* _parent, bool _isVisible = true)
{
	m_Position = _pos;
	m_Size = _size;
	m_pParent = _parent;
	m_IsVisible = _isVisible;
}

void GUIBox::OnClick(Vector2 _mousePosition)
{

}

void GUIBox::Render()
{

}