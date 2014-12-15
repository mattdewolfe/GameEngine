// Base class for all GUI objects. A window can be any GUI elements (a box, a button, a slider, etc.)
// Each window has a List of child windows. Use this parenting system to set up complex GUI objects

#ifndef _IGUIWINDOW_H_
#define _IGUIWINDOW_H_

#include <iostream>
#include <list>

// TODO add function overrides for Vector class
struct Vector2
{
	Vector2(float _x = 0, float _y = 0) 
	{
		x = _x;
		y = _y;
	};
	float x, y;
};

class IGUIWindow
{
public:
	IGUIWindow();
	~IGUIWindow();
	virtual void Init(void);
	void SetParent(IGUIWindow* win) { if (win) m_pParent = win; }
	IGUIWindow* GetParent(void) { return m_pParent; }
	bool AddWindow(IGUIWindow* win);
	bool RemoveWindow(IGUIWindow* win);

	void SetVisible (bool _vis) { m_IsVisible = _vis; }
	bool GetVisible () { return m_IsVisible; }

	void SetPosition(Vector2 _pos);
	Vector2 GetPosition() { return m_Position; }

	void SetSize(Vector2 _size);
	Vector2 GetSize () { return m_Size; }

	virtual void OnClick(Vector2 _mousePosition);
	virtual void Render();

	bool CheckBounds (Vector2 _localCoordinates);

private:
protected:
	IGUIWindow* m_pParent;

	Vector2 m_Position;
	Vector2 m_Size;
	bool m_IsVisible;

   std::list<IGUIWindow*> m_ChildWindows;
};


bool IGUIWindow::AddWindow(IGUIWindow *win)
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

bool IGUIWindow::RemoveWindow(IGUIWindow *win)
{
	// Check if window is in List, then remove and delete it
}

// Checks if the coordinates are within the bounds of this window. 
bool IGUIWindow::CheckBounds (Vector2 _localCoordinates)
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

#endif