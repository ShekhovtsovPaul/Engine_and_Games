#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Engine.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <Sprite.h>
#include <Window.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Timing.h>
#include "Bullet.h"

#include <vector>


enum class GameState { PLAY, EXIT };

class MainGame {
public:

	MainGame();
	~MainGame();

	void run();		// Start
	
private:

	void initSystems();		// init SDL, OpenGL, glew...
	void initShaders();	// init SHADER PROGRAM
	void gameLoop();	// GAME LOOP !
	void processInput();	// processing...
	void drawGame();		// rendering...

	// BASIC VARIABLES !
	Engine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Engine::GLSLProgram _colorProgram;
	Engine::Camera2D _camera;
	Engine::SpriteBatch _spriteBatch;
	Engine::InputManager _inputManager;
	Engine::FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _fps;
	float _maxFPS;
	float _time;
};