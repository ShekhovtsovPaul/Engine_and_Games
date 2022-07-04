#include "MainGame.h"
#include <Errors.h>
#include <ResourceManager.h>

#include <iostream>
#include <string>


MainGame::MainGame() :
_screenWidth(900),
_screenHeight(600),
_time(0.0f),
_gameState(GameState::PLAY),
_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}
MainGame::~MainGame() 
{
}

// RUN ALL GAME!
void MainGame::run()
{
	initSystems();	// init SDL, OpenGL, OBJECTS, settings

	gameLoop();		// ALL MAGIC - input(), update(), render();
}

void MainGame::initSystems()
{
	Engine::init();

	_window.create("Game Engine //framework", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

// ALL GLOBAL CHANGES HERE !!! (TIME)
void MainGame::gameLoop()
{

	while (_gameState != GameState::EXIT)		// stop when enum FLAG::EXIT
	{
		_fpsLimiter.begin();

		processInput();		// keyword & mouse events
		_time += 0.01;

		_camera.update();

		for (int i = 0; i < _bullets.size();) {
			if (_bullets[i].update() == true) {
				// SWAP LAST ELEMENT of VECTOR
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else {
				i++;
			}
		}

		drawGame();

		_fps = _fpsLimiter.end();

		// FPS - every 10 frames
		static int frameCounter = 0;	// initialize ONES !
		frameCounter++;
		if (frameCounter == 10000) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::processInput()
{
	//SDL_PollEvent		//get user input & process them!
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	SDL_Event evnt;		// QUEUE (FIFO) ! - bunch of variables
	while (SDL_PollEvent(&evnt))		// waiting input... when PUSHED BUTTON!
	{
		// after PUSHED BUTTON!
		switch (evnt.type)
		{
		case SDL_QUIT:		// "Esc" (button)
			// action after "Esc"
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);

		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 1.00f, 1000);
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// every frame - clear

	_colorProgram.use();	// ACTIVE SHADERS

	// BIND TEXTURE !
	glActiveTexture(GL_TEXTURE0);

	// SET SAMPLER2D - what texture to use !
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");	// LINK - from Fragment SHADER
	glUniform1i(textureLocation, 0);

	// SET UNIFORM CAMERA2D for all MESH !
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));	// UPLOAD to the GPU!

	// DRAW SPRITE BATCH !
	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	// static - INITIALIZE ONCE - LOAD ONCE !!!
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	
	for (int i = 0; i < _bullets.size(); i++)
		_bullets[i].draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();
}