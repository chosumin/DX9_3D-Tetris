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
	//���Ϸ� ������ ���ʹϾ����� ��ȯ
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