
// newdrawDlg.h : ͷ�ļ�
//

#pragma once
#include "picdata.h"
#include <vector>
#include "order.h"
using namespace std;


// CnewdrawDlg �Ի���
class CnewdrawDlg : public CDialogEx
{
// ����
public:
	CnewdrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NEWDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_radio1;
	CSliderCtrl m_linewidth;
	CMFCColorButton m_pencolor;
	vector<Picdata* > data;
	Picdata* tmp;
	CImage * img;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCancel();
	CString m_order;
	afx_msg void OnEnChangeEditOrder();
	afx_msg void OnBnClickedOrderconfirm();
};
