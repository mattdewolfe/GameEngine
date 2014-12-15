// A simple box with no functionality. Should be used as a parent to other GUI contols

#ifndef _GUIBOX_H_
#define _GUIBOX_H_

#include "IGUIWindow.h"

class GUIBox : public IGUIWindow
{
	GUIBox();
	GUIBox(Vector2 _pos, Vector2 _size, IGUIWindow* _parent, bool _isVisible);
	~GUIBox();
	void OnClick(Vector2 _mousePosition);
	void Render();
};

#endif