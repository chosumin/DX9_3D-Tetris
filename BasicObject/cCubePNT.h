#pragma once

class cCubePNT
{
public:
	cCubePNT();
	virtual ~cCubePNT();
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();
private:

protected:
	vector<ST_PNT_VERTEX> m_vecVertex;
};
