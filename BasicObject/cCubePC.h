#pragma once

class cCubePC
{
public:
	cCubePC();
	~cCubePC();
public:
	virtual void Setup();
	virtual void Render();
protected:
	vector<ST_PC_VERTEX> m_vecVertex;
};