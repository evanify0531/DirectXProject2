#pragma once
#include "GameObject.h"
class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = NULL;
	//uint32 _width = 0;
	//uint32 _height = 0;
	
	//Graphics
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;

private:
	shared_ptr<GameObject> _gameObject;
};