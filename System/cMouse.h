#pragma once

#define MAX_INPUT_cMouse 8

class cMouse
{
public:
	void SetHandle(HWND handle)
	{
		this->handle = handle;
	}

	static cMouse* Get();
	static void Delete();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);

	D3DXVECTOR2 GetPosition() { return position; }

	bool ButtonDown(DWORD button) 
	{ 
		return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
	}
	
	bool ButtonUp(DWORD button)
	{ 
		return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
	}

	bool ButtonPress(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS;
	}

private:
	cMouse();
	~cMouse();

	static cMouse* instance;

	HWND handle;
	D3DXVECTOR2 position; //마우스 위치

	byte buttonStatus[MAX_INPUT_cMouse];
	byte buttonOldStatus[MAX_INPUT_cMouse];
	byte buttonMap[MAX_INPUT_cMouse];

	D3DXVECTOR3 wheelStatus;
	D3DXVECTOR3 wheelOldStatus;
	D3DXVECTOR3 wheelMoveValue;

	DWORD timeDblClk;
	DWORD startDblClk[MAX_INPUT_cMouse];
	int buttonCount[MAX_INPUT_cMouse];

	enum 
	{ 
		cMouse_ROTATION_NONE = 0, 
		cMouse_ROTATION_LEFT, 
		cMouse_ROTATION_RIGHT 
	};

	enum 
	{ 
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN, 
		BUTTON_INPUT_STATUS_UP, 
		BUTTON_INPUT_STATUS_PRESS, 
		BUTTON_INPUT_STATUS_DBLCLK
	};
};

