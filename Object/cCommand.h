#pragma once

struct cCommand
{
public:
	cCommand();
	virtual ~cCommand();
public:
	bool RotationKeyDown();
	bool DirectionKeyDown();

	void Reflect();
	void UpdateWorld();
	void ResetRotAndDir();
	void ResetPosition();
private:
	//오일러 라디안을 쿼터니언으로 변환
	D3DXQUATERNION CreateQuaternion(float roll, float pitch, float yaw) const;
public:
	D3DXVECTOR3		Angle;
	D3DXVECTOR3		Rotation;
	D3DXVECTOR3		Position;
	D3DXMATRIXA16	World;
	D3DXVECTOR3		Direction;
	DWORD			PrevTime;
private:
	bool			m_spaceKeyDown;
	D3DXQUATERNION	m_quaternion;
};