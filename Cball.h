#pragma once
class Cball
{
public:
	CPoint m_pos;		//공의 좌표
	int m_ball_count;	// 공의 갯수
	int m_ball_radius;	// 공의 반지름
public:
	Cball();	// 기본 컨스트럭트
	Cball(CPoint pt, int bc, int rd);
	void Draw(CDC* pDC);

};