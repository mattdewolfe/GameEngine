// Base class for all GUI objects. A window can be any GUI elements (a box, a button, a slider, etc.)
// Each window has a List of child windows. Use this parenting system to set up complex GUI objects

#ifndef _GUIWINDOW_H_
#define _GUIWINDOW_H_

#include <iostream>
#include <list>
#include "Vertex.h"

// DEBUG DELETE
#include "Events\EventManager.h"

// enum of all the different types of GUI windows
// TODO move creation of GUI windows into a GUI factory, have it handle tagging
enum GUI_WINDOW_TYPE { GWT_BOX, GWT_BUTTON };

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

class GUIWindow
{
public:
	GUIWindow() {};
	~GUIWindow() {};
	virtual void Init(void) = 0;
	void SetParent(GUIWindow* win) { if (win) m_pParent = win; }
	GUIWindow* GetParent(void) { return m_pParent; }
	bool AddWindow(GUIWindow* win);
	bool RemoveWindow(GUIWindow* win);

	void SetVisible (bool _vis) { m_IsVisible = _vis; }
	bool GetVisible () { return m_IsVisible; }

	void SetPosition(Vector2 _pos);
	Vector2 GetPosition() { return m_Position; }

	void SetSize(Vector2 _size);
	Vector2 GetSize () { return m_Size; }

	virtual void OnClick(Vector2 _mousePosition) = 0;
	void PropogateOnClick (Vector2 _mousePosition);
	virtual void OnMouseOver(Vector2 _mousePosition) = 0;
	// when the user releases the mouse button
	virtual void OnRelease() = 0;
	//virtual void Render() = 0;

	bool CheckBounds (Vector2 _localCoordinates);

	void GetVertices (Vertex* _vertices, UINT& _vertexCount, Vector2 _offset);

	// TODO: should be private, made public so iterator in GUIManager::GetUpdatedVertices had access. Find alternative
	std::list<GUIWindow*> m_ChildWindows;

	GUI_WINDOW_TYPE GetType() { return m_Type; }

private:
protected:
	GUIWindow* m_pParent;

	Vector2 m_Position;
	Vector2 m_Size;
	D3DXCOLOR m_Color;
	bool m_IsVisible;
	UINT m_VertexCount;  
	UINT m_ZOrder;

	GUI_WINDOW_TYPE m_Type;
};

#endif