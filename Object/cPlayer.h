#pragma once

struct cCommand;
class cCubeNode;
class cArray;
class cBlockFactory;
class cPlayer
{
public:
	cPlayer(cArray* array);
	~cPlayer();
public:
	void Setup();
	void Update();
	void Render();
private:
	void IntersectWidthArray();
	void OffsetPlayerBlock();
private:
	cBlockFactory * m_pFactory;
	cCommand *		m_pCommand;
	cCubeNode*		m_pBlock;
	cArray*			m_pArray;
};