// A simple button object

#ifndef _GUIBUTTON_H_
#define _GUIBUTTON_H_

#include "GUIWindow.h"

enum BUTTON_STATE { BS_NORMAL, BS_HOVER, BS_CLICK };

class GUIButton : public GUIWindow
{
public:
	GUIButton();
	GUIButton(Vector2 _pos, Vector2 _size, D3DXCOLOR _color, GUI_WINDOW_TYPE _type, bool _isVisible = true);
	GUIButton(Vector2 _pos, Vector2 _size, D3DXCOLOR _color, bool _isVisible = true);
	~GUIButton();
	void Init();
	virtual void OnClick(Vector2 _mousePosition);
	virtual void OnMouseOver(Vector2 _mousePosition);
	virtual void OnRelease();
	BUTTON_STATE GetState () { return state; }
	void SetState (BUTTON_STATE _state) { state = _state; }	
private:
protected:
	// 0 = normal, 1 = hover, 2 = click
	D3DXCOLOR colors[3];
	BUTTON_STATE state;
};

#endif