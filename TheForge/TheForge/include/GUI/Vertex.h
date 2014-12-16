// TEMP DELETE used in tutorial, replace with our own vertex type when the time comes

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <d3dx10.h>

struct Vertex
{
	Vertex()
	{
		X = 0;
		Y = 0;
		Z = 0;
		Color = D3DXCOLOR(0,0,0,1);
	}
	Vertex (float _x, float _y, float _z, D3DXCOLOR _color)
	{
		X = _x;
		Y = _y;
		Z = _z;
		Color = _color;
	}
	FLOAT X, Y, Z; D3DXCOLOR Color;
};    // a struct to define a vertex

#endif