
// MFC_final_projectView.cpp: CMFCfinalprojectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_final_project.h"
#endif

#include "MFC_final_projectDoc.h"
#include "MFC_final_projectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CBrick.h"
#include "Cball.h"
#include <time.h>

// CMFCfinalprojectView

IMPLEMENT_DYNCREATE(CMFCfinalprojectView, CView)

BEGIN_MESSAGE_MAP(CMFCfinalprojectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCfinalprojectView 생성/소멸

CMFCfinalprojectView::CMFCfinalprojectView() noexcept
{
	level = 1; // 현재 상태 
	m_flag = false;
	//---------------------------------------사각형 생성 1단계--------------------------------------//
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 6;j++){
			brick_obj[i][j] = CBrick(CPoint(BOARD_X1 + j*130, BOARD_Y1 + 100 + i*100),128,98,0,false); //사각형 만들기 [좌표 ,가로길이,세로길이.HP, 생성]
		}
	}
	//----------------------------------------------------------------------------------------------//

	//초기 블럭 랜덤 생성
	MakeBrick(3);

	// 첫 공 만들기 [중심좌표,공의 갯수]ㄴ
	ball_obj = Cball(CPoint(BOARD_X1 + 390, BOARD_Y1 + 880),1,RADIUS); // 공 만들기 [ 좌표, count , 반지름 ]

}

CMFCfinalprojectView::~CMFCfinalprojectView()
{
}

BOOL CMFCfinalprojectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCfinalprojectView 그리기


void CMFCfinalprojectView::OnDraw(CDC* pDC)
{
	CMFCfinalprojectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->Rectangle(BOARD_X1, BOARD_Y1, BOARD_X1 + 780, BOARD_Y1 + 900); // 보드판 780*900

	ball_obj.Draw(pDC); // 만든 원 그리기 
	//---------------------true 인 사각형 그리기-----------------------//
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if(brick_obj[i][j].m_state == true){
				brick_obj[i][j].Draw(pDC); // 만든 사각형 그리기
				brick_obj[i][j].TextDraw(pDC); // 사각형 안에 점수 그리기
			}
		}
	}
	//------------------------------------------------------------------//




	//-----------------공과 마우스 사이의 선---------------//
	if (!m_flag) {
		CPen pen, * oldPen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 200));
		oldPen = pDC->SelectObject(&pen);
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptEnd.x - (m_ptEnd.x - m_ptStart.x) / 2, m_ptEnd.y - (m_ptEnd.y - m_ptStart.y) / 2);
		pDC->SelectObject(oldPen);
		pen.DeleteObject();
	}
	//-----------------------------------------------------//

	
	//----------------점수 알려주는 창 보여주기------------//
	pDC->TextOut(BOARD_X1, 20, L"NOW SCORE", 9);
	str.Format(L" %d ", level);
	pDC->TextOutW(BOARD_X1+103, 20, str);
	//-----------------------------------------------------//	

	//--------------------사진 첨부------------------------//
	CDC mdc;
	CBitmap s_bit, l_bit, * oldbit;
	mdc.CreateCompatibleDC(pDC);
	s_bit.LoadBitmap(IDB_BITMAP3);
	oldbit = mdc.SelectObject(&s_bit);
	pDC->BitBlt(50, 50, 500, 700, &mdc, 0, 0, SRCCOPY);
	mdc.SelectObject(oldbit);
	s_bit.DeleteObject();
	l_bit.DeleteObject();
	mdc.DeleteDC();
	//-----------------------------------------------------//


}


// CMFCfinalprojectView 인쇄

BOOL CMFCfinalprojectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCfinalprojectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCfinalprojectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCfinalprojectView 진단

#ifdef _DEBUG
void CMFCfinalprojectView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCfinalprojectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCfinalprojectDoc* CMFCfinalprojectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCfinalprojectDoc)));
	return (CMFCfinalprojectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCfinalprojectView 메시지 처리기


void CMFCfinalprojectView::OnLButtonDown(UINT nFlags, CPoint point) // 마우스 왼쪽 버튼 누른 상태 
{
	m_ptStart = ball_obj.m_pos;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCfinalprojectView::OnLButtonUp(UINT nFlags, CPoint point) // 마우스 왼쪽 버튼 땐 상태
{
	if (!m_flag) { // 마우스 클릭 제어

		m_xStep = (point.x - ball_obj.m_pos.x);
		m_yStep = (point.y - ball_obj.m_pos.y);

		int x_abs = abs(m_xStep); // x값을 절대값으로 변환
		int y_abs = abs(m_yStep); // y값을 절대값으로 변환

		int x_sign = m_xStep / x_abs;
		int y_sign = m_yStep / y_abs;

		if (x_abs < y_abs) {// x의 값과 y의 값의 속도비를 맞춰서 정해줌
			int temp = (x_abs * SPEED) / y_abs;
			x_abs = temp;
			y_abs = SPEED;

		}
		else {
			int temp = (y_abs * SPEED) / x_abs;
			y_abs = temp;
			x_abs = SPEED;
		}
		m_xStep = x_abs * x_sign;
		m_yStep = y_abs * y_sign;
		m_flag = true;
		m_ptEnd = ball_obj.m_pos;
		SetTimer(1, 30, NULL);
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMFCfinalprojectView::OnMouseMove(UINT nFlags, CPoint point) // 마우스 커셔가 움직일 때
{
	if (!m_flag) {
		if (nFlags & MK_LBUTTON) {
			m_ptEnd = point;
			Invalidate();
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCfinalprojectView::OnTimer(UINT_PTR nIDEvent)
{
	ball_obj.m_pos.x += m_xStep; // ball의 x좌표가 마우스가 클린한 좌표로 m_xStep 만큼 더해져 움직임
	ball_obj.m_pos.y += m_yStep; // ball의 y좌표가 마우스가 클린한 좌표로 m_yStep 만큼 더해져 움직임

	//---------------------------------------------------공이 블럭에 닿았을 시에----------------------------------------------------------//
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if (brick_obj[i][j].m_state == false)  // 현재 생성되어있는 블럭을 탐색
			{
				continue;
			}
			else
			{
				if (brick_obj[i][j].CheckTouch(ball_obj.m_pos.x, ball_obj.m_pos.y - ball_obj.m_ball_radius) || // 원의 1번 좌표
					brick_obj[i][j].CheckTouch(ball_obj.m_pos.x, ball_obj.m_pos.y + ball_obj.m_ball_radius))   // 원의 3번 좌표
				{
					brick_obj[i][j].m_HP = brick_obj[i][j].m_HP - ball_obj.m_ball_count;
					if (brick_obj[i][j].m_HP == 0) {
						brick_obj[i][j].m_state = false;
					}
					ball_obj.m_pos.y -= m_yStep;
					m_yStep = m_yStep * (-1);
				}

				if (brick_obj[i][j].CheckTouch(ball_obj.m_pos.x - ball_obj.m_ball_radius, ball_obj.m_pos.y) || // 원의 2번 좌표
					brick_obj[i][j].CheckTouch(ball_obj.m_pos.x + ball_obj.m_ball_radius, ball_obj.m_pos.y))   // 원의 4번 좌표
				{
					brick_obj[i][j].m_HP = brick_obj[i][j].m_HP - ball_obj.m_ball_count;
					if (brick_obj[i][j].m_HP <= 0) {
						brick_obj[i][j].m_state = false;
					}
					ball_obj.m_pos.x -= m_xStep;
					m_xStep = m_xStep * (-1);

				}
			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------------------------------//

	//----------------------------공이 보드판 벽에 닿았을 때-----------------------------//
	if (ball_obj.m_pos.x - RADIUS < BOARD_X1 || ball_obj.m_pos.x + RADIUS  > BOARD_X1 + 780) {

		ball_obj.m_pos.x -= m_xStep;
		m_xStep *= -1;
	}
	if (ball_obj.m_pos.y - RADIUS < BOARD_Y1) {

		ball_obj.m_pos.y -= m_yStep;
		m_yStep *= -1;
	}
	if (ball_obj.m_pos.y + RADIUS > BOARD_Y1 + 900) { // 공이 바닥에 닿았을 때
		m_flag = false; // 공이 바닥에 닿으면 다시 마우스 클릭 가능
		ball_obj.m_pos.x -= m_xStep; // 공이 제 위치에 정지 하기 위해서 갔던 값을 다시 빼줌
		ball_obj.m_pos.y -= m_yStep; //							"
		m_xStep = 0;
		m_yStep = 0;

		if (GameOver()) {// 게임 오버 확인

			KillTimer(1);
			AfxMessageBox(_T("GAME OVER"));
			m_flag = true;

		}
		else {

			ChangeBrick();// 사각형 자리 바꾸기
			level++;
			MakeBrick(3); // 공이 바닥에 오면 새로운 블럭 생성
			KillTimer(1);

		}
	}
	//-----------------------------------------------------------------------------------//
	Invalidate();
	/* 깜박거림 현상 고치기
	CRect rt(ball_obj.m_pos.x-ball_obj.m_ball_radius-100, ball_obj.m_pos.y - ball_obj.m_ball_radius - 100,
		ball_obj.m_pos.x - ball_obj.m_ball_radius + 100, ball_obj.m_pos.y - ball_obj.m_ball_radius + 100);
	InvalidateRect(&rt,true);
	*/
	CView::OnTimer(nIDEvent);
}

int CMFCfinalprojectView::RandNum(int n) // 난수 생성 함수
{
	srand(time(NULL)); // 난수 생성을 위해서 
	return rand() % n;
}


void CMFCfinalprojectView::MakeBrick(int cn) // 블럭 랜덤 생성
{

		count = 0; // 블럭 생성시 사용
	
		while (count < cn) { // 랜덤으로 첫번째 줄 블럭 생성하기 (3개) 

			if (brick_obj[0][RandNum(5)].m_state == true) {
				continue;
			}
			else {
				brick_obj[0][RandNum(5)].m_state = true;
				brick_obj[0][RandNum(5)].m_HP = level;
				count++;
			}
		}

}


bool CMFCfinalprojectView::GameOver() // 게임 오버 확인 
{	

		for (int i = 0; i < 6; i++) {
			if (brick_obj[6][i].m_state == false) { // 마지막줄 
				continue;
			}else{
				return true;
			}
		}
		return false;
}


void CMFCfinalprojectView::ChangeBrick() // 사각형 위치 바꾸기
{
	if (GameOver()!=true) {
		for (int i = 5; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				brick_obj[i+1][j].m_state = brick_obj[i][j].m_state;
				brick_obj[i+1][j].m_HP = brick_obj[i][j].m_HP;
				if (i == 0) {
				brick_obj[i][j].m_state = false;
				brick_obj[i][j].m_HP = 0;
				}
			}
		}
	}
}

