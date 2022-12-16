#pragma once
class CBrick
{
public: // 블럭이 내려갈때 현재 HP와 m_state의 값을 다음 블럭 자리에 줘야함

	CPoint m_pos; //사각형의 좌표
	int m_width;  // 가로
	int m_height; // 새로
	int m_HP;	  // 사각형 HP
	bool m_state; // 사각형의 생성 여부			 차라리 HP를 비교해서 해버릴까..?

public:
	CBrick();	// 기본 컨스트럭트
	CBrick(CPoint pt, int w, int h, int L, bool st);
	void Draw(CDC* pDC); // 사각형 그리는 함수
	bool CBrick::CheckTouch(int xp, int yp); // 사각형이 공과 닿았는지 확인 하는 함수 
	CRect m_block;
	void TextDraw(CDC* pDC);
	CString str;
};