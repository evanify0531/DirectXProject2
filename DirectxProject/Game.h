#pragma once
#include "Graphics.h"
#include "GameObject.h"
#include "Pipeline.h"

class InputManager;
class TimeManager;
class SceneManager;
class ResourceManager;


class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();

	shared_ptr<InputManager> GetInputManager() { return _input; }
	shared_ptr<TimeManager> GetTimeManager() { return _time; }
	shared_ptr<SceneManager> GetSceneManager() { return _scene;  }
	shared_ptr<ResourceManager> GetResourceManager() { return _resource; }


	shared_ptr<Pipeline> GetPipeline() { return _pipeline;  }

private:
	HWND _hwnd = NULL;
	//uint32 _width = 0;
	//uint32 _height = 0;
	
	//Graphics
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;

private:
	shared_ptr<InputManager> _input;
	shared_ptr<TimeManager> _time;
	shared_ptr<SceneManager> _scene;
	shared_ptr<ResourceManager> _resource;
};

extern unique_ptr<Game> GGame;