
// newdrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "newdraw.h"
#include "newdrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnewdrawDlg 对话框

Picdata* creatdata(int r,int l,int pc);


CnewdrawDlg::CnewdrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CnewdrawDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_radio1 = 0;
	//  m_order = _T("");
}

void CnewdrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_SLIDER_LINEWIDTH, m_linewidth);
	DDX_Control(pDX, IDC_PENCOLOR, m_pencolor);
	//  DDX_Text(pDX, IDC_EDIT_ORDER, m_order);
	DDX_Text(pDX, IDC_EDIT_ORDER, m_order);
}

BEGIN_MESSAGE_MAP(CnewdrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CnewdrawDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CnewdrawDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CnewdrawDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CnewdrawDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CnewdrawDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CnewdrawDlg::OnBnClickedRadio6)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_OPEN, &CnewdrawDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CnewdrawDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_CLEAR, &CnewdrawDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDCANCEL, &CnewdrawDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_ORDER, &CnewdrawDlg::OnEnChangeEditOrder)
	ON_BN_CLICKED(IDC_ORDERCONFIRM, &CnewdrawDlg::OnBnClickedOrderconfirm)
END_MESSAGE_MAP()


// CnewdrawDlg 消息处理程序

BOOL CnewdrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	img=NULL;
	tmp=NULL;
	m_order="";
	m_radio1=0;
	m_linewidth.SetRange(1,30);
	m_linewidth.SetPos(1);
	m_pencolor.SetColor(RGB(0,0,0));
	RECT rect;
	GetClientRect(&rect);
	GetDlgItem(IDC_PICTURE)->MoveWindow(0,0,500,400);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CnewdrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		RECT rect;
	//	GetClientRect(&rect);//得到可绘制的区域范围

		CWnd*c=GetDlgItem(IDC_PICTURE);//获取控件句柄,用于确定显示范围
		c->GetWindowRect(&rect);//相对于屏幕
		ScreenToClient(&rect);//相对于父控件
	

		CDC MemDC;//内存句柄，用于实现双缓冲技术
		CBitmap MemBitmap;


		MemDC.CreateCompatibleDC(NULL);//创建兼容句柄和位图
		MemBitmap.CreateCompatibleBitmap(&dc,500,400);
		MemDC.SelectObject(&MemBitmap);
		::SetStretchBltMode(MemDC, HALFTONE);

		if(img) 
			img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
		else
			MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充



		CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		MemDC.SelectObject(pBrush);

		if(tmp)tmp->draw(MemDC);

		for(int i=0;i<data.size();i++)
			if((*data[i]).GetVisible())
				data[i]->draw(MemDC);
		dc.BitBlt(0,0,500,400,&MemDC,0,0,SRCCOPY);
		MemDC.DeleteDC();
		MemBitmap.DeleteObject();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CnewdrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CnewdrawDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CnewdrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(tmp==NULL)tmp=creatdata(m_radio1,m_linewidth.GetPos(),m_pencolor.GetColor());
	else {delete tmp;tmp=creatdata(m_radio1,m_linewidth.GetPos(),m_pencolor.GetColor());}
	tmp->p1=tmp->p2=point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CnewdrawDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_radio1==5)
		for(int i=0;i<data.size();i++)
			if((*data[i]).checkin(tmp->p1,tmp->p2))
				(*data[i]).eraser();
	if(tmp)data.push_back(tmp);
	tmp=NULL;	


	CClientDC dc(this);
	RECT rect;

	CWnd*c=GetDlgItem(IDC_PICTURE);//获取控件句柄,用于确定显示范围
	c->GetWindowRect(&rect);//相对于屏幕
	ScreenToClient(&rect);//相对于父控件


	CDC MemDC;//内存句柄，用于实现双缓冲技术
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);//创建兼容句柄和位图
	MemBitmap.CreateCompatibleBitmap(&dc,500,400);
	MemDC.SelectObject(&MemBitmap);
	::SetStretchBltMode(MemDC, HALFTONE);

	if(img) 
		img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
	else
		MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充



	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	MemDC.SelectObject(pBrush);

	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			data[i]->draw(MemDC);
	dc.BitBlt(0,0,500,400,&MemDC,0,0,SRCCOPY);
	MemDC.DeleteDC();
	MemBitmap.DeleteObject();




	CDialogEx::OnLButtonUp(nFlags, point);
}


void CnewdrawDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
	{

		if (m_radio1==1)
		{
			if(tmp){tmp->p2=point;data.push_back(tmp);}
			tmp=NULL;
			tmp=creatdata(m_radio1,m_linewidth.GetPos(),m_pencolor.GetColor());
			tmp->p1=tmp->p2=point;
		}
		else
			if(tmp) 
				tmp->p2=point;
		Invalidate();
		UpdateWindow();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

Picdata* creatdata(int r,int l,int pc)
{
	switch(r)
	{
	case 1:
	case 2:
		return(new Line(r,l,pc));
		break;
	case 0:
		return(new Square(r,l,pc,false,false));
		break;
	case 3:
		return(new Square(r,l,pc));
		break;
	case 5:
		return(new Eraser(r,l,pc,false,false));
		break;
	case 4:
		return(new Circle(r,l,pc));
		break;

	}
}

BOOL CnewdrawDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CnewdrawDlg::OnBnClickedOpen()
{
	int visiblesize=0;
	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			visiblesize++;


	if(visiblesize!=0||img!=NULL)
	{

	int a=AfxMessageBox("是否保存？",MB_YESNOCANCEL);
	if(a==IDYES)
	{
		OnBnClickedSave();
		if(img!=NULL){ img->Destroy();img=NULL;}
		data.clear();
		tmp=NULL;
		CClientDC dc(this);
		RECT rect;
		GetClientRect(&rect);//得到可绘制的区域范围
		dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充

	}
	else if(a==IDNO)
	{
		if(img!=NULL){ img->Destroy();img=NULL;}
		data.clear();
		tmp=NULL;

		CClientDC dc(this);
		RECT rect;
		GetClientRect(&rect);//得到可绘制的区域范围
		dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充

	}
	else return;
	}

	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg格式 (*.jpg)|*.jpg|bmp格式 (*.bmp)|*.bmp||",NULL);
	if(dlg.DoModal()==IDOK)
	{
		if(img==NULL) img=new CImage();
		else img->Destroy();//释放以前的图片
		img->Load(dlg.GetPathName());
		InvalidateRect(NULL);
		UpdateWindow();
	}
}


void CnewdrawDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd = GetDlgItem(IDC_PICTURE)->GetSafeHwnd(); 


	HDC hDC = ::GetWindowDC(hwnd);
	RECT rect; 
	::GetWindowRect(hwnd, &rect);
	HDC hDCMem = ::CreateCompatibleDC(hDC);
	HBITMAP hBitMap =::CreateCompatibleBitmap(hDC,rect.right-rect.left,rect.bottom-rect.top);
	HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap);
	::BitBlt(hDCMem, 0, 0, rect.right-rect.left, rect.bottom-rect.top, hDC, 0, 0, SRCCOPY);
	CImage image;
	image.Attach(hBitMap); 
	CString strFilter="位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";  
	CFileDialog dlg(FALSE,"bmp","1.bmp",NULL,strFilter); 
	if ( IDOK != dlg.DoModal()) 
		return; 
	CString strFileName; 
	CString strExtension; 
	strFileName = dlg.m_ofn.lpstrFile;  
	if (dlg.m_ofn.nFileExtension == 0) 
	{  
		switch (dlg.m_ofn.nFilterIndex) 
		{  
		case 1:  
			strExtension = "bmp"; break; 
		case 2:  
			strExtension = "jpg"; break; 
		case 3:  
			strExtension = "gif"; break; 
		case 4:  
			strExtension = "png"; break; 
		default: 
			break; 
		}  
		strFileName = strFileName + '.' + strExtension; 
	} 
	HRESULT hResult = image.Save(strFileName); 
	if (FAILED(hResult))  
		MessageBox("保存图像文件失败！"); 
	else 
	MessageBox("保存图像文件成功！"); 
	image.Detach(); 
	::SelectObject(hDCMem, hOldMap);
	::DeleteObject(hBitMap); 
	::DeleteDC(hDCMem); 
	::DeleteDC(hDC); 

}


void CnewdrawDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	int visiblesize=0;
	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			visiblesize++;
	if(visiblesize!=0||img!=NULL)
	{
		int a=AfxMessageBox("是否保存？",MB_YESNOCANCEL);
		if(a==IDYES)
		{
			OnBnClickedSave();
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;
			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//得到可绘制的区域范围
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充
		
		}
		else if(a==IDNO)
		{
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;

			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//得到可绘制的区域范围
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充

		}
		else return;
	}
}


void CnewdrawDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	int visiblesize=0;
	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			visiblesize++;
	if(visiblesize!=0||img!=NULL)
	{
		int a=AfxMessageBox("是否保存？",MB_YESNOCANCEL);
		if(a==IDYES)
		{
			OnBnClickedSave();
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;
			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//得到可绘制的区域范围
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充

		}
		else if(a==IDNO)
		{
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;

			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//得到可绘制的区域范围
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充

		}
		else return;
	}


	CDialogEx::OnCancel();
}


void CnewdrawDlg::OnEnChangeEditOrder()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedOrderconfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Order myorder(m_order);
	tmp=creatdata(myorder.seporder(),m_linewidth.GetPos(),m_pencolor.GetColor());
	tmp->p1=myorder.GetPoint1();
	tmp->p2=myorder.GetPoint2();
	data.push_back(tmp);
	tmp=NULL;
	m_order="";
	UpdateData(FALSE);

	CClientDC dc(this);
	RECT rect;

	CWnd*c=GetDlgItem(IDC_PICTURE);//获取控件句柄,用于确定显示范围
	c->GetWindowRect(&rect);//相对于屏幕
	ScreenToClient(&rect);//相对于父控件


	CDC MemDC;//内存句柄，用于实现双缓冲技术
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(CDC::FromHandle(::GetDC(NULL)));//创建兼容句柄和位图
	MemBitmap.CreateCompatibleBitmap(CDC::FromHandle(::GetDC(NULL)),499,399);
	MemDC.SelectObject(&MemBitmap);
	::SetStretchBltMode(MemDC, HALFTONE);

	if(img) 
		img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
	else
		MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//用白色填充



	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	MemDC.SelectObject(pBrush);

	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			data[i]->draw(MemDC);
	dc.BitBlt(0,0,500,400,&MemDC,0,0,SRCCOPY);
	MemDC.DeleteDC();
	MemBitmap.DeleteObject();


}
