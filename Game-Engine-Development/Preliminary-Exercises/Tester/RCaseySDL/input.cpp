#include "input.h"
#include <SDL.h>



void Input::Update(SDL_Event m_event)
{
	//loop through all the events in the events list
	//while (SDL_PollEvent(&m_event) != NULL)
	//{


		//got an event, lets process it.

		//check for keydown
		if (m_event.type == SDL_KEYDOWN)
		{
			//cache the code of key we pressed for easier debugging
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = true;
				break;

			case SDLK_r:
				m_keysPressed[KEY_R] = true;
				break;

			case SDLK_g:
				m_keysPressed[KEY_G] = true;
				break;

			case SDLK_b:
				m_keysPressed[KEY_B] = true;
				break;

			case SDLK_w:
				m_keysPressed[KEY_W] = true;
				break;

			case SDLK_s:
				m_keysPressed[KEY_S] = true;
				break;

			case SDLK_d:
				m_keysPressed[KEY_D] = true;
				break;

			case SDLK_a:
				m_keysPressed[KEY_A] = true;
				break;

			case SDLK_u:
				m_keysPressed[KEY_U] = true;
				break;

			case SDLK_j:
				m_keysPressed[KEY_J] = true;
				break;

			case SDLK_h:
				m_keysPressed[KEY_H] = true;
				break;

			case SDLK_k:
				m_keysPressed[KEY_K] = true;
				break;

			case SDLK_RETURN:
				m_keysPressed[KEY_RETURN] = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_keysPressed[KEY_MOUSE] = true;
				break;
			}
		}
		// check for key up
		else if (m_event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			// update keys
			switch (keyPressed)
			{
			case SDLK_r:
				m_keysPressed[KEY_R] = false;
				break;

			case SDLK_g:
				m_keysPressed[KEY_G] = false;
				break;

			case SDLK_b:
				m_keysPressed[KEY_B] = false;
				break;

			case SDLK_w:
				m_keysPressed[KEY_W] = false;
				break;

			case SDLK_s:
				m_keysPressed[KEY_S] = false;
				break;

			case SDLK_a:
				m_keysPressed[KEY_A] = false;
				break;

			case SDLK_d:
				m_keysPressed[KEY_D] = false;
				break;

			case SDLK_u:
				m_keysPressed[KEY_U] = false;
				break;

			case SDLK_j:
				m_keysPressed[KEY_J] = false;
				break;

			case SDLK_h:
				m_keysPressed[KEY_H] = false;
				break;

			case SDLK_k:
				m_keysPressed[KEY_K] = false;
				break;

			case SDLK_RETURN:
				m_keysPressed[KEY_RETURN] = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_keysPressed[KEY_MOUSE] = false;
				break;
			}
		}
	//}
}

Input::Input()
{
}

Input::~Input()
{
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}
