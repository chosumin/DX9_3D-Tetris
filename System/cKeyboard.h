#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

class cKeyboard
{
public:
	enum class KeyType
	{
		NONE = 0, DOWN, UP, PRESS,
	};

	static cKeyboard* Get();
	static void Delete();

	void Update();

	bool KeyDown(DWORD key) { return keyMap[key] == KeyType::DOWN; }
	bool KeyUp(DWORD key) { return keyMap[key] == KeyType::UP; }
	bool KeyPress(DWORD key) { return keyMap[key] == KeyType::PRESS; }

	KeyType KeyMap(DWORD key) { return keyMap[key]; }

private:
	cKeyboard();
	~cKeyboard();

	static cKeyboard* instance;

	BYTE keyState[MAX_INPUT_KEY];
	BYTE keyOldState[MAX_INPUT_KEY];
	KeyType keyMap[MAX_INPUT_KEY];
};