
// newdrawDlg.h : 头文件
//

#pragma once
#include "picdata.h"
#include <vector>
#include "order.h"
using namespace std;


// CnewdrawDlg 对话框
class CnewdrawDlg : public CDialogEx
{
// 构造
public:
	CnewdrawDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NEWDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
