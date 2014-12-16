// A simple box with no functionality. Should be used as a parent to other GUI contols

#ifndef _GUIBOX_H_
#define _GUIBOX_H_

#include "GUIWindow.h"

class GUIBox : public GUIWindow
{
public:
	GUIBox();
	GUIBox(Vector2 _pos, Vector2 _size, D3DXCOLOR _color, GUI_WINDOW_TYPE _type, bool _isVisible = true);
	~GUIBox();
	void Init();
	virtual void OnClick(Vector2 _mousePosition);
	virtual void OnMouseOver(Vector2 _mousePosition);
	virtual void OnRelease();
private:
protected:
	
};

#endif