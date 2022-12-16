#include "pch.h"
#include "CBrick.h"
#include <time.h>

//#include <iostream>
//#include <string>

CBrick::CBrick(){ // 기본 컨스트럭트 함수

}


CBrick::CBrick(CPoint pt, int w, int h, int L, bool st) { // 컨스트럭트 함수

	m_pos = pt;
	m_width = w;
	m_height = h;
	m_HP = L;
	m_state = st;
}

void CBrick::Draw(CDC* pDC) 
{
	// 사각형 채우기 
	
	CBrush brush;
	if (m_HP < 2) {
		brush.CreateSolidBrush(RGB(255, 211, 176));
	}
	else if (2 <= m_HP && m_HP < 4) {
		brush.CreateSolidBrush(RGB(255, 185, 185));
	}
	else if (4 <= m_HP && m_HP < 6) {
		brush.CreateSolidBrush(RGB(237, 149, 149));
	}
	else if (6 <= m_HP && m_HP < 8) {
		brush.CreateSolidBrush(RGB(255, 113, 113));
	}
	else if (m_HP >= 8) {
		brush.CreateSolidBrush(RGB(223, 77, 77));
	}

	pDC->SelectObject(&brush);
	m_block = CRect(m_pos.x, m_pos.y, m_pos.x + m_width, m_pos.y + m_height);
	pDC->Rectangle(m_block);
}

bool CBrick::CheckTouch(int xp, int yp) // 공이 사각형에 닿았을 때를 확인 공(x,y)
{
	if (m_pos.x < xp && xp < (m_pos.x + m_width)
			&& m_pos.y < yp && yp < (m_pos.y + m_height) ) {
		return true;
	}
	else {
		return false;
	}
}
void CBrick::TextDraw(CDC* pDC)
{

	str.Format(L" %d ", m_HP);
	pDC->TextOutW(m_pos.x+56, m_pos.y+40, str);

}

