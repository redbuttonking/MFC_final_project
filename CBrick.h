#pragma once
class CBrick
{
public: // ���� �������� ���� HP�� m_state�� ���� ���� �� �ڸ��� �����

	CPoint m_pos; //�簢���� ��ǥ
	int m_width;  // ����
	int m_height; // ����
	int m_HP;	  // �簢�� HP
	bool m_state; // �簢���� ���� ����			 ���� HP�� ���ؼ� �ع�����..?

public:
	CBrick();	// �⺻ ����Ʈ��Ʈ
	CBrick(CPoint pt, int w, int h, int L, bool st);
	void Draw(CDC* pDC); // �簢�� �׸��� �Լ�
	bool CBrick::CheckTouch(int xp, int yp); // �簢���� ���� ��Ҵ��� Ȯ�� �ϴ� �Լ� 
	CRect m_block;
	void TextDraw(CDC* pDC);
	CString str;
};