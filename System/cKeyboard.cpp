#include "../stdafx.h"
#include "cKeyboard.h"

cKeyboard* cKeyboard::instance = NULL;

//싱글톤 패턴
cKeyboard * cKeyboard::Get()
{
	if (instance == NULL)
		instance = new cKeyboard();

	return instance;
}

void cKeyboard::Delete()
{
	SAFE_DELETE(instance);
}

void cKeyboard::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));
	
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		BYTE oldState = keyOldState[i];
		BYTE state = keyState[i];

		if (oldState == 0 && state == 1)
			keyMap[i] = KeyType::DOWN; //이전 0, 현재 1 - KeyDown
		else if (oldState == 1 && state == 0)
			keyMap[i] = KeyType::UP; //이전 1, 현재 0 - KeyUp
		else if (oldState == 1 && state == 1)
			keyMap[i] = KeyType::PRESS; //이전 1, 현재 1 - KeyPress
		else 
			keyMap[i] = KeyType::NONE;
	}
}

cKeyboard::cKeyboard()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

cKeyboard::~cKeyboard()
{
	
}
