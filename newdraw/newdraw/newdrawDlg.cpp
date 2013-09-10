
// newdrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "newdraw.h"
#include "newdrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnewdrawDlg �Ի���

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


// CnewdrawDlg ��Ϣ�������

BOOL CnewdrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnewdrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		RECT rect;
	//	GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ

		CWnd*c=GetDlgItem(IDC_PICTURE);//��ȡ�ؼ����,����ȷ����ʾ��Χ
		c->GetWindowRect(&rect);//�������Ļ
		ScreenToClient(&rect);//����ڸ��ؼ�
	

		CDC MemDC;//�ڴ���������ʵ��˫���弼��
		CBitmap MemBitmap;


		MemDC.CreateCompatibleDC(NULL);//�������ݾ����λͼ
		MemBitmap.CreateCompatibleBitmap(&dc,500,400);
		MemDC.SelectObject(&MemBitmap);
		::SetStretchBltMode(MemDC, HALFTONE);

		if(img) 
			img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
		else
			MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���



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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CnewdrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CnewdrawDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CnewdrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(tmp==NULL)tmp=creatdata(m_radio1,m_linewidth.GetPos(),m_pencolor.GetColor());
	else {delete tmp;tmp=creatdata(m_radio1,m_linewidth.GetPos(),m_pencolor.GetColor());}
	tmp->p1=tmp->p2=point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CnewdrawDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_radio1==5)
		for(int i=0;i<data.size();i++)
			if((*data[i]).checkin(tmp->p1,tmp->p2))
				(*data[i]).eraser();
	if(tmp)data.push_back(tmp);
	tmp=NULL;	


	CClientDC dc(this);
	RECT rect;

	CWnd*c=GetDlgItem(IDC_PICTURE);//��ȡ�ؼ����,����ȷ����ʾ��Χ
	c->GetWindowRect(&rect);//�������Ļ
	ScreenToClient(&rect);//����ڸ��ؼ�


	CDC MemDC;//�ڴ���������ʵ��˫���弼��
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);//�������ݾ����λͼ
	MemBitmap.CreateCompatibleBitmap(&dc,500,400);
	MemDC.SelectObject(&MemBitmap);
	::SetStretchBltMode(MemDC, HALFTONE);

	if(img) 
		img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
	else
		MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���



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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	int a=AfxMessageBox("�Ƿ񱣴棿",MB_YESNOCANCEL);
	if(a==IDYES)
	{
		OnBnClickedSave();
		if(img!=NULL){ img->Destroy();img=NULL;}
		data.clear();
		tmp=NULL;
		CClientDC dc(this);
		RECT rect;
		GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
		dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���

	}
	else if(a==IDNO)
	{
		if(img!=NULL){ img->Destroy();img=NULL;}
		data.clear();
		tmp=NULL;

		CClientDC dc(this);
		RECT rect;
		GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
		dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���

	}
	else return;
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg��ʽ (*.jpg)|*.jpg|bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if(dlg.DoModal()==IDOK)
	{
		if(img==NULL) img=new CImage();
		else img->Destroy();//�ͷ���ǰ��ͼƬ
		img->Load(dlg.GetPathName());
		InvalidateRect(NULL);
		UpdateWindow();
	}
}


void CnewdrawDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	CString strFilter="λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";  
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
		MessageBox("����ͼ���ļ�ʧ�ܣ�"); 
	else 
	MessageBox("����ͼ���ļ��ɹ���"); 
	image.Detach(); 
	::SelectObject(hDCMem, hOldMap);
	::DeleteObject(hBitMap); 
	::DeleteDC(hDCMem); 
	::DeleteDC(hDC); 

}


void CnewdrawDlg::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int visiblesize=0;
	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			visiblesize++;
	if(visiblesize!=0||img!=NULL)
	{
		int a=AfxMessageBox("�Ƿ񱣴棿",MB_YESNOCANCEL);
		if(a==IDYES)
		{
			OnBnClickedSave();
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;
			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���
		
		}
		else if(a==IDNO)
		{
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;

			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���

		}
		else return;
	}
}


void CnewdrawDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int visiblesize=0;
	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			visiblesize++;
	if(visiblesize!=0||img!=NULL)
	{
		int a=AfxMessageBox("�Ƿ񱣴棿",MB_YESNOCANCEL);
		if(a==IDYES)
		{
			OnBnClickedSave();
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;
			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���

		}
		else if(a==IDNO)
		{
			if(img!=NULL){ img->Destroy();img=NULL;}
			data.clear();
			tmp=NULL;

			CClientDC dc(this);
			RECT rect;
			GetClientRect(&rect);//�õ��ɻ��Ƶ�����Χ
			dc.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���

		}
		else return;
	}


	CDialogEx::OnCancel();
}


void CnewdrawDlg::OnEnChangeEditOrder()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}


void CnewdrawDlg::OnBnClickedOrderconfirm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	CWnd*c=GetDlgItem(IDC_PICTURE);//��ȡ�ؼ����,����ȷ����ʾ��Χ
	c->GetWindowRect(&rect);//�������Ļ
	ScreenToClient(&rect);//����ڸ��ؼ�


	CDC MemDC;//�ڴ���������ʵ��˫���弼��
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(CDC::FromHandle(::GetDC(NULL)));//�������ݾ����λͼ
	MemBitmap.CreateCompatibleBitmap(CDC::FromHandle(::GetDC(NULL)),499,399);
	MemDC.SelectObject(&MemBitmap);
	::SetStretchBltMode(MemDC, HALFTONE);

	if(img) 
		img->StretchBlt(MemDC,0,0,500,400,0,0,img->GetWidth(),img->GetHeight(),SRCCOPY);
	else
		MemDC.FillSolidRect(0,0,500,400,RGB(255,255,255));//�ð�ɫ���



	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	MemDC.SelectObject(pBrush);

	for(int i=0;i<data.size();i++)
		if((*data[i]).GetVisible())
			data[i]->draw(MemDC);
	dc.BitBlt(0,0,500,400,&MemDC,0,0,SRCCOPY);
	MemDC.DeleteDC();
	MemBitmap.DeleteObject();


}
