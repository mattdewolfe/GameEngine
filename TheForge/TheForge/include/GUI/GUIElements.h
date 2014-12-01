#ifndef _GUIELEMENTS_H_
#define _GUIELEMENTS_H_

#include <iostream>

#include "GUIStateManager.h"

//const int MaxElementsPerTexture = 512; ??

struct Vector2
{
	Vector2(float _x = 0, float _y = 0) 
	{
		x = _x;
		y = _y;
	};
	float x, y;
};

struct Vector4
{
	Vector4(float _r = 0, float _g = 0, float _b = 0, float _a = 0) 
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	};
	float r, g, b, a;
};

struct Quad
{
	float xPos;
	float yPos;
	int width;
	int height;
};


struct GUIElementVertexData
{
	Vector2 position;
	Vector2 dimensions; 
	Vector4 rgba;
	Vector4 source;
};


class GUIElement
{
private:
protected:
public:
	GUI_STATE currentState;

	Quad source;
	Quad dest;
	int zPos;
	float theta;
	float scale;

	Vector4 rgba;
	std::string texture;

	GUIElement(float _x = 0.0f, float _y = 0.0f, float _w = 50.0f, float _h = 50.0f)
	{
		zPos = 0;
		scale = 0.0f;
		theta = 0.0f; 

		currentState = GUI_ACTIVE;
	}
	~GUIElement(){}

	std::string GetTexture()
	{ return texture; }
	void SetTexture(std::string _text)
	{ texture = _text; } 
};

class GUIText : public GUIElement
{
private:
protected:
public:
	std::string text;
	std::string font;

	GUIText(float _x = 0.0f, float _y = 0.0f, float _w = 50.0f, float _h = 50.0f, bool _vis = true)
	{
		zPos = 0;
		scale = 0.0f;
		theta = 0.0f; 

		text = "xxxTESTxxx";
		font = "yyyTESTyyy";
	}
	~GUIText(){}

	 std::string GetFont() const
	{ return font; } 
	void SetFont(std::string _font)
	{ font = _font; }

	std::string GetText() const
	{ return text; }
	void SetText(std::string _text)
	{ text = _text; }
};

#endif


//KW