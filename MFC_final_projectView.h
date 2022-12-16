
// MFC_final_projectView.h: CMFCfinalprojectView 클래스의 인터페이스
//

#pragma once

#include "CBrick.h"
#include "Cball.h"

#define BOARD_X1 640 // 보드판 X1 좌표 
#define BOARD_Y1 50	// 보드판 Y2 좌표
#define RADIUS 14 // 공의 반지름
#define SPEED 10 // 공의 속도

//#define BOARD_X2 1350 // 보드판 X2 좌표
//#define BOARD_Y2 1270 // 보드판 Y2 좌표

class CMFCfinalprojectView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCfinalprojectView() noexcept;
	DECLARE_DYNCREATE(CMFCfinalprojectView)

// 특성입니다.
public:
	CMFCfinalprojectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.

public:
	virtual ~CMFCfinalprojectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CBrick brick_obj[7][6]; // 가로 7개 새로 6칸
	Cball ball_obj;
	int level; //현재 라운드 레벨 
	int count; // 초기 블럭 생성 할 때 쓰일 count  
	int m_xStep; // 공이 움직일때 가는 x거리
	int m_yStep; // 공이 움직일때 가는 y거리
	bool m_flag; // 마우스 클릭 제어
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int RandNum(int n); // 난수 생성 함수
	void MakeBrick(int cn); // 사각형 만드는 함수
	bool GameOver(); 
	void ChangeBrick();
	CString str;
	CPoint m_ptStart, m_ptEnd;//마우스 끝 좌표 얻기
};

#ifndef _DEBUG  // MFC_final_projectView.cpp의 디버그 버전
inline CMFCfinalprojectDoc* CMFCfinalprojectView::GetDocument() const
   { return reinterpret_cast<CMFCfinalprojectDoc*>(m_pDocument); }
#endif
