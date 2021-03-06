// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
#include <assert.h>
#include <time.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <array>
#include <functional>
#include <iostream>
using namespace std;

extern HWND g_hWnd;
#define SAFE_RELEASE(p) {if(p) p->Release(); p = nullptr;}
#define SAFE_DELETE(p) {if(p) delete (p); p = nullptr;}
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] (p); p = nullptr;}
#define SINGLETONE(class_name) \
	private : \
	class_name(void); \
	~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		} \

#define SYNTHESIZE(varType, varName, funName) \
protected: varType varName; \
public: inline varType Get##funName(void) const {return varName;}\
public: inline void Set##funName(varType var) {varName = var;}\

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName) \
protected: varType varName; \
public: inline varType& Get##funName(void) {return varName;} \
public: inline void Set##funName(varType& var) {varName = var;} \

#include "./System/cDeviceManager.h"
#include "./System/cCamera.h"
#include "./System/cKeyboard.h"
#include "./System/cMouse.h"

#include "./BasicObject/stVertex.h"

#define	m_yCount	10
#define	m_xCount	6
#define	m_zCount	6