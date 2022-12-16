#include "pch.h"
#include "Cball.h"


Cball::Cball() {
}

Cball::Cball(CPoint pt, int bc, int rd) {

	m_pos = pt;
	m_ball_count = bc;
	m_ball_radius = rd;

}


void Cball::Draw(CDC* pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 225));
	pDC->SelectObject(&brush);
	
	pDC->Ellipse(m_pos.x - m_ball_radius, m_pos.y - m_ball_radius, m_pos.x + m_ball_radius, m_pos.y + m_ball_radius);
	// ���� �߽� (x,y)	������ r
	// x-r,y-r , x+r ,y+r 

}
