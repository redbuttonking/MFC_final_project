#pragma once
class Cball
{
public:
	CPoint m_pos;		//���� ��ǥ
	int m_ball_count;	// ���� ����
	int m_ball_radius;	// ���� ������
public:
	Cball();	// �⺻ ����Ʈ��Ʈ
	Cball(CPoint pt, int bc, int rd);
	void Draw(CDC* pDC);

};