#include "InputSystem.h"

void nc::InputSystem::Startup() {

	const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
	keyboardState.resize(numKeys);
	std::copy(keyboardStateSDL , keyboardStateSDL + numKeys, keyboardState.begin());
	prevKeyboardState = keyboardState;
}

void nc::InputSystem::Shutdown()
{
}

void nc::InputSystem::Update(float dt) {

	prevKeyboardState = keyboardState;
	const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

	prevMouseButtonState = mouseButtonState;
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	mousePosition = nc::Vector2{ x, y };
	mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML]
	mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML]
	mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

	
}


bool nc::InputSystem::IsKeyDown(int id)
{
	return keyboardState[id];
}

bool nc::InputSystem::IsPreviousKeyDown(int id)
{
	return prevKeyboardState[id];
}

nc::InputSystem::eKeyState nc::InputSystem::GetButtonState(int id)
{
	eKeyState state = eKeyState::Idle;

	bool keyDown = IsButtonDown(id);
	bool prevKeyDown = IsPreviousButtonDown(id);

	if (keyDown)
	{
		state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
	}
	else
	{
		state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
	}

	return state;
}

nc::InputSystem::eKeyState nc::InputSystem::GetKeyState(int id)
{
	eKeyState state = eKeyState::Idle;

	bool keyDown = IsKeyDown(id);
	bool prevKeyDown = IsPreviousKeyDown(id);

	if (keyDown)
	{
		state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
	}
	else
	{
		state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
	}

	return state;

}


