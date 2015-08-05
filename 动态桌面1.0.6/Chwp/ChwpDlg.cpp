// ChwpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chwp.h"
#include "ChwpDlg.h"
#include "Exit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////





// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{/*/////////////////////////////////////////////////////////////////////////////////////
	SetWindowLong(this->GetSafeHwnd() ,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd() ,GWL_EXSTYLE)^0x80000);    //0x80000    :    WS_EX_LAYERED   
	HINSTANCE  hInst=LoadLibrary("User32.DLL");    //    ��ʽ����DLL   
	if(hInst!=NULL)   
	{   
		typedef    BOOL(WINAPI    *MYFUNC)(HWND,COLORREF,BYTE,DWORD);   
		//ȡ��SetLayeredWindowAttributes����ָ��   
		MYFUNC pFunc=(MYFUNC)GetProcAddress(hInst,    "SetLayeredWindowAttributes");   
		if(pFunc!=NULL)   
		{ 
			pFunc(this->GetSafeHwnd(), 0, 230, 2);    //    2    :    LWA_ALPHA   
		}
		FreeLibrary(hInst);   
		hInst    =    NULL;   
	} 

*///////////////////////////////////////////////////////////////////////////////////	

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
// CChwpDlg �Ի���
CChwpDlg::CChwpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChwpDlg::IDD, pParent)
	, m_curpaper(0)
	, m_date(COleDateTime::GetCurrentTime())
	, m_currentday(0)
	, m_currenthour(0)
	, m_currentminute(0)
	, m_currentsecond(0)
	, m_paperday(0)
	, m_paperhour(0)
	, m_paperminute(0)
	, m_papersecond(0)
	, m_currentyear(0)
	, num(0)
	, curdispmode(0)
	, strPicFile(_T(""))
	, RUN(false)
	, CheckRand(FALSE)
	, X(0)
	, Y(0)
{
	m_image.Create(16,16,ILC_COLOR8,4,1000);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	RUN=false;
}
void CChwpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_LIST, m_list1);
	DDX_Control(pDX, IDC_COMBO1, m_dispmode);
	DDX_Text(pDX, IDC_DAY, m_paperday);
	DDX_Text(pDX, IDC_HOUR, m_paperhour);
	DDX_Text(pDX, IDC_MINUTE, m_paperminute);
	DDX_Text(pDX, IDC_SECOND, m_papersecond);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Check(pDX, IDC_RAND, CheckRand);
}

BEGIN_MESSAGE_MAP(CChwpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER+1,OnStatusIcon)
	ON_BN_CLICKED(IDC_Exit, &CChwpDlg::OnBnClickedExit)
ON_COMMAND(ID_MENUABOUT,OnMenuAbout)
ON_COMMAND(ID_MENUEXIT,OnMenuExit)
ON_COMMAND(ID_MENUSHOW,OnShowMainDialog)
ON_COMMAND(ID_MENUNEXT,OnNext)
ON_COMMAND(ID_MENULAST,OnLast)
ON_COMMAND(ID_MENUPAUSE,OnPause)
ON_COMMAND(ID_MENUCONTINUE,OnContinue)
ON_BN_CLICKED(IDC_ADDPAPER, &CChwpDlg::OnAddpaper)
ON_BN_CLICKED(IDC_DELETEPAPER, &CChwpDlg::OnDeletepaper)
ON_BN_CLICKED(IDC_Ok, &CChwpDlg::OnOk)
ON_NOTIFY(NM_CLICK, IDC_LIST, &CChwpDlg::OnClickList1)
ON_WM_TIMER()
ON_CBN_SELCHANGE(IDC_COMBO1, &CChwpDlg::OnChangeMode)
ON_WM_DROPFILES()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTONHIDE, &CChwpDlg::OnBnClickedButtonhide)
ON_BN_CLICKED(IDC_BUTTONPAUSE, &CChwpDlg::OnBnClickedButtonpause)
ON_BN_CLICKED(IDC_BUTTONCONTINUE, &CChwpDlg::OnBnClickedButtoncontinue)
ON_BN_CLICKED(IDC_BUTTONLAST, &CChwpDlg::OnBnClickedButtonlast)
ON_BN_CLICKED(IDC_BUTTONNEXT, &CChwpDlg::OnBnClickedButtonnext)
END_MESSAGE_MAP()


// CChwpDlg ��Ϣ�������

BOOL CChwpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
//////////////////////////////////////////////////////////////////////////////////////
	SetWindowLong(this->GetSafeHwnd() ,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd() ,GWL_EXSTYLE)^0x80000);    //0x80000    :    WS_EX_LAYERED   
	HINSTANCE  hInst=LoadLibrary("User32.DLL");    //    ��ʽ����DLL   
	if(hInst!=NULL)   
	{   
		typedef    BOOL(WINAPI    *MYFUNC)(HWND,COLORREF,BYTE,DWORD);   
		//ȡ��SetLayeredWindowAttributes����ָ��   
		MYFUNC pFunc=(MYFUNC)GetProcAddress(hInst,    "SetLayeredWindowAttributes");   
		if(pFunc!=NULL)   
		{ 
			pFunc(this->GetSafeHwnd(), 0, 230, 2);    //    2    :    LWA_ALPHA   
		}
		FreeLibrary(hInst);   
		hInst    =    NULL;   
	} 

///////////////////////////////////////////////////////////////////////////////////	

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	PostMessage(WM_USER+2);
	//��ϵͳ��Ϣ�����ͼ��
	HICON icon=AfxGetApp()->LoadIcon(IDI_ICON1);
	
	data.cbSize=sizeof(NOTIFYICONDATA);
	data.hIcon=icon;
	data.hWnd=m_hWnd;
	strcpy(data.szTip,"��̬����");
	data.uCallbackMessage=WM_USER+1;
	data.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
	data.uID=88;
	if(!Shell_NotifyIcon(NIM_ADD,&data))	//��������ͼ��
		AfxMessageBox("����ϵͳ����ͼ��ʧ�ܣ�");


//	DWORD dwThreadID;
//	hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,NULL,CREATE_SUSPENDED,&dwThreadID);
//	if(hThread==NULL)
//		AfxMessageBox("�����̴߳���!");

	//CWinThread *pThread;
	IfExit=false;
	DWORD dwParam;
	pThread=AfxBeginThread(ThreadProc,&dwParam,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread==NULL)
		AfxMessageBox("�����̴߳���!");

/////////////////////////////////////////////
	//CWnd *pWnd=GetDlgItem(IDC_SCREENSIZE);
	//CRect rect;
	//pWnd->GetWindowRect(rect);
	//this->ScreenSize .gety
	//this->ScreenSize.Create(SS,WS_CHILD|WS_VISIBLE|SS_LEFT,rect,pWnd);

/////////////////////////////////////////////
//	SetThreadPriority(
//	thread.m_bAutoDelete=FALSE;
//	thread.m_pfnThreadProc=ThreadProc();
	//thread.m_pThreadParams=
//	thread.CreateThread();


///////////////////////////////////////////////
	
//	hr = CoCreateInstance (CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,IID_IActiveDesktop, (void**) &pIAD );
//		if(!SUCCEEDED(hr)) 
//			AfxMessageBox("�����ӿ�ʵ������");

////////////////////////////////////////////////


/*		//���ļ�����Ϊ���ַ���,����IActiveDesktop::SetWallpaper��Ҫ��
		WCHAR   wszWallpaper [MAX_PATH];
		LPTSTR lpStr = str.GetBuffer(str.GetLength() );
		MultiByteToWideChar(CP_ACP, 0, lpStr, -1, wszWallpaper, MAX_PATH);
		str.ReleaseBuffer();
		//����ǽֽ
		hr = pIAD->SetWallpaper(wszWallpaper, 0);
		if(!SUCCEEDED(hr)) 
			return ;
		//����ǽֽ����ʽ
		WALLPAPEROPT wpo;
		wpo.dwSize = sizeof(wpo);
		wpo.dwStyle = mode;
		hr = pIAD->SetWallpaperOptions(&wpo, 0);
		if(!SUCCEEDED(hr))
			return ;
		//Ӧ��ǽֽ������
		hr = pIAD->ApplyChanges(AD_APPLY_ALL);
		if(!SUCCEEDED(hr))
			return ;
		//��ȡǽֽ���ļ�������ӡ��debug������
		//hr = pIAD->GetWallpaper(wszWallpaper, MAX_PATH, 0);
		//CString strFile = wszWallpaper;
		//TRACE(str); //�������λͼ�Ļ�,�����������벻���ķ���
		//�ͷŽӿڵ�ʵ��
		pIAD->Release();

*///////////////////////////////////////////////


	//����List Box �ؼ���ص�Image�б����ͼ��
	m_image.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_image.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_image.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_image.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	

	//��ʼ�� list box
	m_list1.SetImageList(&m_image,LVSIL_SMALL);
	m_list1.SetIconSpacing(16,16);

	//��ʼ��������ˢ
	m_brush.CreateSolidBrush(RGB(255,255,255));

///////////////////////////////////////////////////
	//��ע����������
	int nums=AfxGetApp()->GetProfileIntA("paper","papernum",-100);
	if(nums<0)
	{
		m_spin1.SetRange(0,30);
		m_spin1.SetPos(0);
		m_spin2.SetRange(0,23);
		m_spin2.SetPos(0);
		m_spin3.SetRange(0,59);
		m_spin3.SetPos(0);
		m_spin4.SetRange(0,59);
		m_spin4.SetPos(10);
		m_dispmode.SetCurSel(0);
		if(nums==-100)
		{
			m_curpaper=-1;
			AfxGetApp()->WriteProfileInt("paper","papernum",-1);
			MessageBox("��ӭʹ�ñ�������״�ʹ�ã�����δ�����κα���ͼƬ������ӣ�������Դ�����ྫ��ͼƬ�������Ҫ�뵽��װĿ¼�鿴��","��ܰ��ʾ");
		}
		else if(nums==-1)
		{
			m_curpaper=-1;
			MessageBox("δ�����κα���ͼƬ������ӣ�","��ʾ");
		}
		else
			AfxMessageBox("ע�������������˲飡");
		return TRUE; 
	}
	if(nums>=0)
	{
		for(int i=0;i<=nums;i++)
		{
			CString string,getstring;
			string.Format("wallpaper%d",i);
			getstring=AfxGetApp()->GetProfileString("paper",string);
			char c=getstring[getstring.Find('.')+1];
			int item;
			if(c=='b'||c=='B'||c=='d'||c=='D')
				item=0;
			else if(c=='j'||c=='J')
				item=1;
			else if(c=='g'||c=='G')
				item=2;
			else if(c=='p'||c=='P')
				item=3;
			else
			{
				AfxMessageBox("�ļ���������˲飡");
				return TRUE;
			}
			m_list1.InsertItem(i,getstring,item);
		}
	}
	num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
	m_curpaper=AfxGetApp()->GetProfileInt("paper","currentpaper",-100);	
	if(m_curpaper<0)
	{
		AfxMessageBox("ע���������������˲飡");
		m_curpaper=0;
		return TRUE;
	}
	m_list1.SetSelectionMark(m_curpaper);
	CString dispaper;
	dispaper.Format("dispaper%d",m_curpaper);
	curdispmode=AfxGetApp()->GetProfileInt("paper",dispaper,-1);
	dispaper.Format("wallpaperpath%d",m_curpaper);
	strPicFile=AfxGetApp()->GetProfileString("paperpath",dispaper);
	m_dispmode.SetCurSel(curdispmode);


	//if(!OnPreviewPaper())
	//	AfxMessageBox("Ԥ������");
	//��ע���õ����õĸ���ʱ�䲢�����ĸ�����
	m_paperday=AfxGetApp()->GetProfileInt("papertime","updateday",0);
	m_paperhour=AfxGetApp()->GetProfileInt("papertime","updatehour",0);
	m_paperminute=AfxGetApp()->GetProfileInt("papertime","updateminute",0);
	m_papersecond=AfxGetApp()->GetProfileInt("papertime","updatesecond",0);

  //spin �ؼ�������
	m_spin1.SetRange(0,30);
	m_spin1.SetPos(m_paperday);
	m_spin2.SetRange(0,23);
	m_spin2.SetPos(m_paperhour);
	m_spin3.SetRange(0,59);
	m_spin3.SetPos(m_paperminute);
	m_spin4.SetRange(0,59);
	m_spin4.SetPos(m_papersecond);

	m_lastupdateyear=AfxGetApp()->GetProfileInt("papertime","lastupdateyear",0);
	m_lastupdateday=AfxGetApp()->GetProfileInt("papertime","lastupdateday",0);
	m_lastupdatehour=AfxGetApp()->GetProfileInt("papertime","lastupdatehour",0);
	m_lastupdateminute=AfxGetApp()->GetProfileInt("papertime","lastupdateminute",0);
	m_lastupdatesecond=AfxGetApp()->GetProfileInt("papertime","lastupdatesecond",0);

	//��ʼ������m_date���õ���ǰ���ڲ������������
	m_date=COleDateTime::GetCurrentTime();
	m_currentyear=m_date.GetYear();
	m_currentday=m_date.GetDayOfYear();
	m_currenthour=m_date.GetHour();
	m_currentminute=m_date.GetMinute();
	m_currentsecond=m_date.GetSecond();
	
	//��ʱ����м���
	int year=m_lastupdateyear;
	int second=0,minute=0,hour=0,day=0;
	if((year%4==0)&&!(year%100==0&&year%400!=0))	//�ж��Ƿ�������
		year=366;
	else
		year=365;
	second=m_lastupdatesecond+m_papersecond;
	if(second>59)
	{
		second-=60;
		minute++;
	}
	minute+=m_lastupdateminute+m_paperminute;
	if(minute>59)
	{
		minute-=60;
		hour++;
	}
	hour+=m_lastupdatehour+m_paperhour;
	if(hour>23)
	{
		hour-=24;
		day++;
	}
	day+=m_lastupdateday+m_paperday;
	if(day>year)
	{
		day-=year;
		year=m_lastupdateyear+1;
	}
	else
		year=m_lastupdateyear;


	//���ݼ������ж��Ƿ���Ҫ�ı�ǽֽ
	BOOL m_changeflag=FALSE;
	if(m_currentyear>year)
		m_changeflag=TRUE;
	else if(m_currentday>day)
		m_changeflag=TRUE;
	else if(m_currenthour>hour)
		m_changeflag=TRUE;
	else if(m_currentminute>minute)
		m_changeflag=TRUE;
	else if(m_currentsecond>second)
		m_changeflag=TRUE;

	//�����Ҫ�ı�ǽֽ���򽫵�ǰǽֽ��Ϣ������ٵ��ú����޸�����ǽֽ
	if(m_changeflag)
	{
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_currentyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_currentday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_currenthour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_currentminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_currentsecond);
		if(!SetWallPaper())
		{
			AfxMessageBox("����ǽֽʧ�ܣ�");
			return TRUE;
		}


		//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
		++m_curpaper;
		if(m_curpaper>nums)
			m_curpaper=0; 
		dispaper.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
		strPicFile=AfxGetApp()->GetProfileString("paperpath",dispaper);//����ע���õ���ǰǽֽ·��
		dispaper.Format("dispaper%d",m_curpaper);
		curdispmode=AfxGetApp()->GetProfileInt("paper",dispaper,-1);
		m_list1.SetSelectionMark(m_curpaper);
		m_dispmode.SetCurSel(curdispmode);
		//if(!OnPreviewPaper())
		//	AfxMessageBox("Ԥ������");

		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChwpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	Sleep(0);//������߳̿�������ͣ���߳������ڸ������ȼ��̵߳�����
	if ((nID&0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChwpDlg::OnPaint()
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
		CFont *OldFont,NewFont;
//////////////////////////////////////////////
		CPaintDC DC(this);
		X=GetSystemMetrics(SM_CXSCREEN);
		Y=GetSystemMetrics(SM_CYSCREEN);
		char x[10],y[10];
		CString SS;
		itoa(X,x,10);
		itoa(Y,y,10);
		SS="��ǰ��Ļ�ֱ���Ϊ";
		SS+=x;
		SS+="��";
		SS+=y;
		SS+="������Ԥ��Ч����";
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=DC.SelectObject(&NewFont);
		DC.TextOutA(235,30,SS);
		DC.SelectObject(OldFont);
		NewFont.DeleteObject();
	/*
		CRect RECT;
		GetClientRect(RECT);
		CBrush brush;
		brush.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		DC.SelectObject(brush);
		DC.FillRect(RECT,&brush);
		brush.DeleteObject();
*////////////////////////////////////////////
		CWnd * pWnd1=GetDlgItem(IDC_Ok);
		CRect rt1;
		CBrush brush1ab,brush1bc,brush1ca;
		CPaintDC dc1(pWnd1);
		CRgn rgn1a,rgn1b,rgn1ab,rgn1bc;
		pWnd1->GetClientRect(rt1);
		rgn1a.CreateRoundRectRgn(rt1.left,rt1.top,rt1.right,rt1.bottom,10,10);
		rgn1b.CreateRectRgn(rt1.left,rt1.top,rt1.right,rt1.bottom);
		rgn1ab.CreateRectRgn(rt1.left,rt1.top,rt1.right,rt1.bottom);
		rgn1bc.CreateRectRgn(rt1.left,rt1.top,rt1.right,rt1.bottom);
		rgn1ab.CombineRgn(&rgn1b,&rgn1a,RGN_DIFF);
		rgn1bc.CombineRgn(&rgn1b,&rgn1a,RGN_AND);
		brush1ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush1bc.CreateSolidBrush(RGB(255,255,255));
		brush1ca.CreateSolidBrush(RGB(0,0,0));
		dc1.SelectObject(&brush1ab);
		dc1.SelectObject(&brush1bc);
		dc1.SelectObject(&brush1ca);
		dc1.FillRgn(&rgn1ab,&brush1ab);
		dc1.FillRgn(&rgn1bc,&brush1bc);
		dc1.FrameRgn(&rgn1bc,&brush1ca,1,1);
		dc1.SetBkMode(OPAQUE);
		dc1.SetBkColor(RGB(255,255,255));
		dc1.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc1.SelectObject(&NewFont);
		dc1.TextOutA(rt1.Width()/3,rt1.Height()/5,"Ӧ��");
		dc1.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush1bc.DeleteObject();		
		brush1ab.DeleteObject();		
		brush1ca.DeleteObject();
///////////////////////////////////////////////
		CWnd * pWnd2=GetDlgItem(IDC_Exit);
		CRect rt2;
		CBrush brush2ab,brush2bc,brush2ca;
		CPaintDC dc2(pWnd2);
		CRgn rgn2a,rgn2b,rgn2ab,rgn2bc;
		pWnd2->GetClientRect(rt2);
		rgn2a.CreateRoundRectRgn(rt2.left,rt2.top,rt2.right,rt2.bottom,10,10);
		rgn2b.CreateRectRgn(rt2.left,rt2.top,rt2.right,rt2.bottom);
		rgn2ab.CreateRectRgn(rt2.left,rt2.top,rt2.right,rt2.bottom);
		rgn2bc.CreateRectRgn(rt2.left,rt2.top,rt2.right,rt2.bottom);
		rgn2ab.CombineRgn(&rgn2b,&rgn2a,RGN_DIFF);
		rgn2bc.CombineRgn(&rgn2b,&rgn2a,RGN_AND);
		brush2ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush2bc.CreateSolidBrush(RGB(255,255,255));
		brush2ca.CreateSolidBrush(RGB(0,0,0));
		dc2.SelectObject(&brush2ab);
		dc2.SelectObject(&brush2bc);
		dc2.SelectObject(&brush2ca);
		dc2.FillRgn(&rgn2ab,&brush2ab);
		dc2.FillRgn(&rgn2bc,&brush2bc);
		dc2.FrameRgn(&rgn2bc,&brush2ca,1,1);
		dc2.SetBkMode(OPAQUE);
		dc2.SetBkColor(RGB(255,255,255));
		dc2.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc2.SelectObject(&NewFont);
		dc2.TextOutA(rt2.Width()/3,rt2.Height()/5,"�˳�");
		dc2.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush2bc.DeleteObject();		
		brush2ab.DeleteObject();		
		brush2ca.DeleteObject();
/////////////////////////////////////////////////
		CWnd * pWnd3=GetDlgItem(IDC_ADDPAPER);
		CRect rt3;
		CBrush brush3ab,brush3bc,brush3ca;
		CPaintDC dc3(pWnd3);
		CRgn rgn3a,rgn3b,rgn3ab,rgn3bc;
		pWnd3->GetClientRect(rt3);
		rgn3a.CreateRoundRectRgn(rt3.left,rt3.top,rt3.right,rt3.bottom,10,10);
		rgn3b.CreateRectRgn(rt3.left,rt3.top,rt3.right,rt3.bottom);
		rgn3ab.CreateRectRgn(rt3.left,rt3.top,rt3.right,rt3.bottom);
		rgn3bc.CreateRectRgn(rt3.left,rt3.top,rt3.right,rt3.bottom);
		rgn3ab.CombineRgn(&rgn3b,&rgn3a,RGN_DIFF);
		rgn3bc.CombineRgn(&rgn3b,&rgn3a,RGN_AND);
		brush3ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush3bc.CreateSolidBrush(RGB(255,255,255));
		brush3ca.CreateSolidBrush(RGB(0,0,0));
		dc3.SelectObject(&brush3ab);
		dc3.SelectObject(&brush3bc);
		dc3.SelectObject(&brush3ca);
		dc3.FillRgn(&rgn3ab,&brush3ab);
		dc3.FillRgn(&rgn3bc,&brush3bc);
		dc3.FrameRgn(&rgn3bc,&brush3ca,1,1);
		dc3.SetBkMode(OPAQUE);
		dc3.SetBkColor(RGB(255,255,255));
		dc3.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc3.SelectObject(&NewFont);
		dc3.TextOutA(rt3.Width()/10,rt3.Height()/5,"���(A)...");
		dc3.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush3bc.DeleteObject();		
		brush3ab.DeleteObject();		
		brush3ca.DeleteObject();
/////////////////////////////////////////////////
		CWnd * pWnd4=GetDlgItem(IDC_DELETEPAPER);
		CRect rt4;
		CBrush brush4ab,brush4bc,brush4ca;
		CPaintDC dc4(pWnd4);
		CRgn rgn4a,rgn4b,rgn4ab,rgn4bc;
		pWnd4->GetClientRect(rt4);
		rgn4a.CreateRoundRectRgn(rt4.left,rt4.top,rt4.right,rt4.bottom,10,10);
		rgn4b.CreateRectRgn(rt4.left,rt4.top,rt4.right,rt4.bottom);
		rgn4ab.CreateRectRgn(rt4.left,rt4.top,rt4.right,rt4.bottom);
		rgn4bc.CreateRectRgn(rt4.left,rt4.top,rt4.right,rt4.bottom);
		rgn4ab.CombineRgn(&rgn4b,&rgn4a,RGN_DIFF);
		rgn4bc.CombineRgn(&rgn4b,&rgn4a,RGN_AND);
		brush4ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush4bc.CreateSolidBrush(RGB(255,255,255));
		brush4ca.CreateSolidBrush(RGB(0,0,0));
		dc4.SelectObject(&brush4ab);
		dc4.SelectObject(&brush4bc);
		dc4.SelectObject(&brush4ca);
		dc4.FillRgn(&rgn4ab,&brush4ab);
		dc4.FillRgn(&rgn4bc,&brush4bc);
		dc4.FrameRgn(&rgn4bc,&brush4ca,1,1);
		dc4.SetBkMode(OPAQUE);
		dc4.SetBkColor(RGB(255,255,255));
		dc4.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc4.SelectObject(&NewFont);
		dc4.TextOutA(rt4.Width()/3,rt4.Height()/5,"ɾ��");
		dc4.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush4bc.DeleteObject();		
		brush4ab.DeleteObject();		
		brush4ca.DeleteObject();

/////////////////////////////////////////////////
		CWnd * pWnd5=GetDlgItem(IDC_BUTTONHIDE);
		CRect rt5;
		CBrush brush5ab,brush5bc,brush5ca;
		CPaintDC dc5(pWnd5);
		CRgn rgn5a,rgn5b,rgn5ab,rgn5bc;
		pWnd5->GetClientRect(rt5);
		rgn5a.CreateRoundRectRgn(rt5.left,rt5.top,rt5.right,rt5.bottom,10,10);
		rgn5b.CreateRectRgn(rt5.left,rt5.top,rt5.right,rt5.bottom);
		rgn5ab.CreateRectRgn(rt5.left,rt5.top,rt5.right,rt5.bottom);
		rgn5bc.CreateRectRgn(rt5.left,rt5.top,rt5.right,rt5.bottom);
		rgn5ab.CombineRgn(&rgn5b,&rgn5a,RGN_DIFF);
		rgn5bc.CombineRgn(&rgn5b,&rgn5a,RGN_AND);
		brush5ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush5bc.CreateSolidBrush(RGB(255,255,255));
		brush5ca.CreateSolidBrush(RGB(0,0,0));
		dc5.SelectObject(&brush5ab);
		dc5.SelectObject(&brush5bc);
		dc5.SelectObject(&brush5ca);
		dc5.FillRgn(&rgn5ab,&brush5ab);
		dc5.FillRgn(&rgn5bc,&brush5bc);
		dc5.FrameRgn(&rgn5bc,&brush5ca,1,1);
		dc5.SetBkMode(OPAQUE);
		dc5.SetBkColor(RGB(255,255,255));
		dc5.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc5.SelectObject(&NewFont);
		dc5.TextOutA(rt5.Width()/8,rt5.Height()/5,"���ص�����");
		dc5.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush5bc.DeleteObject();		
		brush5ab.DeleteObject();		
		brush5ca.DeleteObject();

/////////////////////////////////////////////////
		CWnd * pWnd6=GetDlgItem(IDC_BUTTONLAST);
		CRect rt6;
		CBrush brush6ab,brush6bc,brush6ca;
		CPaintDC dc6(pWnd6);
		CRgn rgn6a,rgn6b,rgn6ab,rgn6bc;
		pWnd6->GetClientRect(rt6);
		rgn6a.CreateRoundRectRgn(rt6.left,rt6.top,rt6.right,rt6.bottom,10,10);
		rgn6b.CreateRectRgn(rt6.left,rt6.top,rt6.right,rt6.bottom);
		rgn6ab.CreateRectRgn(rt6.left,rt6.top,rt6.right,rt6.bottom);
		rgn6bc.CreateRectRgn(rt6.left,rt6.top,rt6.right,rt6.bottom);
		rgn6ab.CombineRgn(&rgn6b,&rgn6a,RGN_DIFF);
		rgn6bc.CombineRgn(&rgn6b,&rgn6a,RGN_AND);
		brush6ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush6bc.CreateSolidBrush(RGB(255,255,255));
		brush6ca.CreateSolidBrush(RGB(0,0,0));
		dc6.SelectObject(&brush6ab);
		dc6.SelectObject(&brush6bc);
		dc6.SelectObject(&brush6ca);
		dc6.FillRgn(&rgn6ab,&brush6ab);
		dc6.FillRgn(&rgn6bc,&brush6bc);
		dc6.FrameRgn(&rgn6bc,&brush6ca,1,1);
		dc6.SetBkMode(OPAQUE);
		dc6.SetBkColor(RGB(255,255,255));
		dc6.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc6.SelectObject(&NewFont);
		dc6.TextOutA(rt6.Width()/4,rt6.Height()/5,"��һ��");
		dc6.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush6bc.DeleteObject();		
		brush6ab.DeleteObject();		
		brush6ca.DeleteObject();

/////////////////////////////////////////////////
		CWnd * pWnd7=GetDlgItem(IDC_BUTTONNEXT);
		CRect rt7;
		CBrush brush7ab,brush7bc,brush7ca;
		CPaintDC dc7(pWnd7);
		CRgn rgn7a,rgn7b,rgn7ab,rgn7bc;
		pWnd7->GetClientRect(rt7);
		rgn7a.CreateRoundRectRgn(rt7.left,rt7.top,rt7.right,rt7.bottom,10,10);
		rgn7b.CreateRectRgn(rt7.left,rt7.top,rt7.right,rt7.bottom);
		rgn7ab.CreateRectRgn(rt7.left,rt7.top,rt7.right,rt7.bottom);
		rgn7bc.CreateRectRgn(rt7.left,rt7.top,rt7.right,rt7.bottom);
		rgn7ab.CombineRgn(&rgn7b,&rgn7a,RGN_DIFF);
		rgn7bc.CombineRgn(&rgn7b,&rgn7a,RGN_AND);
		brush7ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush7bc.CreateSolidBrush(RGB(255,255,255));
		brush7ca.CreateSolidBrush(RGB(0,0,0));
		dc7.SelectObject(&brush7ab);
		dc7.SelectObject(&brush7bc);
		dc7.SelectObject(&brush7ca);
		dc7.FillRgn(&rgn7ab,&brush7ab);
		dc7.FillRgn(&rgn7bc,&brush7bc);
		dc7.FrameRgn(&rgn7bc,&brush7ca,1,1);
		dc7.SetBkMode(OPAQUE);
		dc7.SetBkColor(RGB(255,255,255));
		dc7.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc7.SelectObject(&NewFont);
		dc7.TextOutA(rt7.Width()/4,rt7.Height()/5,"��һ��");
		dc7.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush7bc.DeleteObject();		
		brush7ab.DeleteObject();		
		brush7ca.DeleteObject();

/////////////////////////////////////////////////
		CWnd * pWnd8=GetDlgItem(IDC_BUTTONPAUSE);
		CRect rt8;
		CBrush brush8ab,brush8bc,brush8ca;
		CPaintDC dc8(pWnd8);
		CRgn rgn8a,rgn8b,rgn8ab,rgn8bc;
		pWnd8->GetClientRect(rt8);
		rgn8a.CreateRoundRectRgn(rt8.left,rt8.top,rt8.right,rt8.bottom,10,10);
		rgn8b.CreateRectRgn(rt8.left,rt8.top,rt8.right,rt8.bottom);
		rgn8ab.CreateRectRgn(rt8.left,rt8.top,rt8.right,rt8.bottom);
		rgn8bc.CreateRectRgn(rt8.left,rt8.top,rt8.right,rt8.bottom);
		rgn8ab.CombineRgn(&rgn8b,&rgn8a,RGN_DIFF);
		rgn8bc.CombineRgn(&rgn8b,&rgn8a,RGN_AND);
		brush8ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush8bc.CreateSolidBrush(RGB(255,255,255));
		brush8ca.CreateSolidBrush(RGB(0,0,0));
		dc8.SelectObject(&brush8ab);
		dc8.SelectObject(&brush8bc);
		dc8.SelectObject(&brush8ca);
		dc8.FillRgn(&rgn8ab,&brush8ab);
		dc8.FillRgn(&rgn8bc,&brush8bc);
		dc8.FrameRgn(&rgn8bc,&brush8ca,1,1);
		dc8.SetBkMode(OPAQUE);
		dc8.SetBkColor(RGB(255,255,255));
		dc8.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc8.SelectObject(&NewFont);
		dc8.TextOutA(rt8.Width()/5,rt8.Height()/5,"��ͣ����");
		dc8.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush8bc.DeleteObject();		
		brush8ab.DeleteObject();		
		brush8ca.DeleteObject();

/////////////////////////////////////////////////
		CWnd * pWnd9=GetDlgItem(IDC_BUTTONCONTINUE);
		CRect rt9;
		CBrush brush9ab,brush9bc,brush9ca;
		CPaintDC dc9(pWnd9);
		CRgn rgn9a,rgn9b,rgn9ab,rgn9bc;
		pWnd9->GetClientRect(rt9);
		rgn9a.CreateRoundRectRgn(rt9.left,rt9.top,rt9.right,rt9.bottom,10,10);
		rgn9b.CreateRectRgn(rt9.left,rt9.top,rt9.right,rt9.bottom);
		rgn9ab.CreateRectRgn(rt9.left,rt9.top,rt9.right,rt9.bottom);
		rgn9bc.CreateRectRgn(rt9.left,rt9.top,rt9.right,rt9.bottom);
		rgn9ab.CombineRgn(&rgn9b,&rgn9a,RGN_DIFF);
		rgn9bc.CombineRgn(&rgn9b,&rgn9a,RGN_AND);
		brush9ab.CreateSolidBrush(RGB(255,255,255));//(238,130,238));
		brush9bc.CreateSolidBrush(RGB(255,255,255));
		brush9ca.CreateSolidBrush(RGB(0,0,0));
		dc9.SelectObject(&brush9ab);
		dc9.SelectObject(&brush9bc);
		dc9.SelectObject(&brush9ca);
		dc9.FillRgn(&rgn9ab,&brush9ab);
		dc9.FillRgn(&rgn9bc,&brush9bc);
		dc9.FrameRgn(&rgn9bc,&brush9ca,1,1);
		dc9.SetBkMode(OPAQUE);
		dc9.SetBkColor(RGB(255,255,255));
		dc9.SetTextColor(RGB(0,0,0));
		NewFont.CreatePointFont(100,"����",NULL);
		OldFont=dc9.SelectObject(&NewFont);
		dc9.TextOutA(rt9.Width()/5,rt9.Height()/5,"��������");
		dc9.SelectObject(OldFont);
		NewFont.DeleteObject();
		brush9bc.DeleteObject();		
		brush9ab.DeleteObject();		
		brush9ca.DeleteObject();

//////////////////////////////////////////////////////////////////////
		OnPreviewPaper();
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChwpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CChwpDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//AfxGetApp()->WriteProfileInt("papertime","updateday",m_paperday);
	//AfxGetApp()->WriteProfileInt("papertime","updatehour",m_paperhour);
	//AfxGetApp()->WriteProfileInt("papertime","updateminute",m_paperminute);
	//AfxGetApp()->WriteProfileInt("papertime","updatesecond",m_papersecond);
	CExit dlg;
	dlg.DoModal();
	if(dlg.IFEXIT)
	{
		OnPause();
		Sleep(0);
		if(!Shell_NotifyIcon(NIM_DELETE,&data))
			AfxMessageBox("���ͼ�����");
		exit(0);
	}
}

LRESULT CChwpDlg::OnStatusIcon(WPARAM wparam, LPARAM lparam)
{
	Sleep(0);//������߳̿�������ͣ���߳������ڸ������ȼ��̵߳�����
	if(wparam=IDI_ICON1)
	{
		switch(lparam)
		{
		case WM_LBUTTONDBLCLK:
			OnShowMainDialog();
			break;
		case WM_LBUTTONDOWN:
			OnContextMenu2(this);
			break;
		case WM_RBUTTONDOWN:
			OnContextMenu(this);
			break;
		default:
			break;
		}
		return 0;
	}
	return 0;
}

// ϵͳ��Ϣ��ͼ����Ҽ������˵�
void CChwpDlg::OnContextMenu(CWnd* pWnd)
{
	CMenu menu;
	if(menu.LoadMenu(IDR_MENU2))
	{
		CMenu * popup=menu.GetSubMenu(0);
		ASSERT(popup!=NULL);
		CPoint mouse;
		GetCursorPos(& mouse);
		::SetForegroundWindow(data.hWnd);
		popup->TrackPopupMenu(TPM_LEFTALIGN,mouse.x,mouse.y,pWnd,NULL);
	}
}

// ����ʽ�˵���ʾ���ڶԻ���
void CChwpDlg::OnMenuAbout(void)
{
	CAboutDlg dlg;
	dlg.DoModal();
}

// ����ʽ�˵����˳���ť
void CChwpDlg::OnMenuExit(void)
{
	/*AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
	AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
	AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
	AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
	AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
	AfxGetApp()->WriteProfileInt("papertime","updateday",m_paperday);
	AfxGetApp()->WriteProfileInt("papertime","updatehour",m_paperhour);
	AfxGetApp()->WriteProfileInt("papertime","updateminute",m_paperminute);
	AfxGetApp()->WriteProfileInt("papertime","updatesecond",m_papersecond);
	*/
	UpdateData(TRUE);
	//AfxGetApp()->WriteProfileInt("papertime","updateday",m_paperday);
	//AfxGetApp()->WriteProfileInt("papertime","updatehour",m_paperhour);
	//AfxGetApp()->WriteProfileInt("papertime","updateminute",m_paperminute);
	//AfxGetApp()->WriteProfileInt("papertime","updatesecond",m_papersecond);
	CExit dlg;
	dlg.DoModal();
	if(dlg.IFEXIT)
	{
		OnPause();
	//	IfExit=true;
		Sleep(0);

		if(!Shell_NotifyIcon(NIM_DELETE,&data))
			AfxMessageBox("���ͼ�����");
		exit(0);
	}
}
void CChwpDlg::OnAddpaper()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog file(TRUE,"bmp",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,"�����ļ�(*.*)|*.*|����ͼ���ļ�(BMP,JPEG,GIF,PNG)|*.bmp;*.dib;*.jpeg;*.jpe;*.jpg;*.jfif;*.gif;*.png|BMP(*.bmp;*.dib)|*.bmp;*.dib|JPEG(*.jpg;*.jpeg;*.jpe;*.jfif)|*.jpg;*.jpeg;*.jpe;*.jfif|PNG(*.png)|*.png|GIF(*.gif)|*.gif||");
	file.m_ofn.nMaxFile=4000;
	char *pc=new char[4000];
	file.m_ofn.lpstrFile=pc;
	file.m_ofn.lpstrFile[0]=NULL;
	if(file.DoModal()==IDOK)
	{
		CString filename,filepath,fileext;
		int nums;
		int item;
		char c;
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		CString stringpaper,stringpath,dispaper;
		POSITION pos=file.GetStartPosition();
		filepath=file.GetPathName();
		while(pos!=NULL)
		{
			filepath=file.GetNextPathName(pos);
			_splitpath(filepath,drive,dir,fname,ext);//����ļ�����������·�����Ϊ�ĸ����֣��ֱ���
			if(drive[0]>96&&drive[0]<123)
				drive[0]-=32;
			filename=fname;
			filename+=ext;
			fileext=ext;
			if(fileext!=".bmp"&&fileext!=".BMP"&&fileext!=".dib"&&fileext!=".DIB"&&fileext!=".jpg"&&fileext!=".JPG"&&fileext!=".jpeg"&&fileext!=".JPEG"&&fileext!=".jpe"&&fileext!=".JPE"&&fileext!=".jfif"&&fileext!=".JFIF"&&fileext!=".gif"&&fileext!=".GIF"&&fileext!=".png"&&fileext!=".PNG")
			{
				AfxMessageBox("�Բ��𣬱�����ݲ�֧�ָø�ʽ�ļ�������ʹ�ø��ļ�����ʹ�ø�ʽת�����ת���ļ���ʽ��");
				num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
				return;
			}
			nums=m_list1.GetItemCount();
			if(nums==1000)
			{
				AfxMessageBox("���ֻ�ܼ���1000���ļ���");
				num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
				//AfxGetApp()->WriteProfileInt("paper","papernum",num);
				return;
			}
			for(int i=0;i<nums;i++)
			{
				if(strcmp(m_list1.GetItemText(i,0),filename)==0)
				{
					AfxMessageBox("�ļ��Ѿ�����!");
					num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
					//AfxGetApp()->WriteProfileInt("paper","papernum",num);
					return;
				}
			}
			c=fileext[1];
			if(c=='b'||c=='B'||c=='d'||c=='D')
				item=0;
			else if(c=='j'||c=='J')
				item=1;
			else if(c=='g'||c=='G')
				item=2;
			else if(c=='p'||c=='P')
				item=3;
			else
			{
				AfxMessageBox("�ļ���������˲飡");
				num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
				//AfxGetApp()->WriteProfileInt("paper","papernum",num);
				return;
			}
			m_list1.InsertItem(nums,filename,item);
			stringpaper.Format("wallpaper%d",nums);
			stringpath.Format("wallpaperpath%d",nums);
			dispaper.Format("dispaper%d",nums);
			//дע���
			curdispmode=m_dispmode.GetCurSel();
			if(curdispmode<0)
				curdispmode=0;
			AfxGetApp()->WriteProfileInt("paper",dispaper,curdispmode);
			AfxGetApp()->WriteProfileInt("paper","papernum",nums);
			AfxGetApp()->WriteProfileString("paper",stringpaper,filename);
			AfxGetApp()->WriteProfileString("paperpath",stringpath,filepath);
		}
		m_curpaper=nums;
		strPicFile=filepath;
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
		AfxGetApp()->WriteProfileInt("paper","papernum",nums);
		m_list1.SetSelectionMark(m_curpaper);
		num=m_curpaper;
		OnPreviewPaper();
	}
	delete [] pc;
	num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
}

void CChwpDlg::OnDeletepaper()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);
	int ntextbefore,ntextafter,nums;
	int *a,*deletenum;
	CString *b,m_stringpaper,dispaper;
	POSITION pos=m_list1.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("��ѡ��Ҫɾ�����ļ�!");
		UpdateData(FALSE);
		return;
	}
	else
	{
		ntextbefore=m_list1.GetItemCount();					//ɾ��֮ǰ��ǽֽ����
		ntextafter=ntextbefore;
		a=new int[ntextbefore];
		deletenum=new int[ntextbefore];
		b=new CString[ntextbefore];
		int t=0,i=0,j;
		while(pos)
		{
			Sleep(0);
			nums = m_list1.GetNextSelectedItem(pos);					//�õ�Ҫɾ����ǽֽ���
			deletenum[ntextbefore-ntextafter]=nums;
			ntextafter--;
			for(;i<nums;i++)							//ɾ��ע����е������Ա�����д��
			{
				dispaper.Format("dispaper%d",i);
				a[t]=AfxGetApp()->GetProfileIntA("paper",dispaper,0);
				AfxGetApp()->WriteProfileString("paper",dispaper,NULL);
				dispaper.Format("wallpaperpath%d",i);
				b[t]=AfxGetApp()->GetProfileStringA("paperpath",dispaper);
				AfxGetApp()->WriteProfileStringA("paperpath",dispaper,NULL);
				t++;
				m_stringpaper.Format("wallpaper%d",i);
				AfxGetApp()->WriteProfileString("paper",m_stringpaper,NULL);
			}
			dispaper.Format("dispaper%d",i);
			AfxGetApp()->WriteProfileString("paper",dispaper,NULL);
			dispaper.Format("wallpaperpath%d",i);
			AfxGetApp()->WriteProfileString("paperpath",dispaper,NULL);
			m_stringpaper.Format("wallpaper%d",i);
			AfxGetApp()->WriteProfileString("paper",m_stringpaper,NULL);
			i++;
		}
		for(;i<ntextbefore;i++)
		{
			Sleep(0);
			dispaper.Format("dispaper%d",i);
			a[t]=AfxGetApp()->GetProfileInt("paper",dispaper,0);
			AfxGetApp()->WriteProfileString("paper",dispaper,NULL);
			dispaper.Format("wallpaperpath%d",i);
			b[t]=AfxGetApp()->GetProfileString("paperpath",dispaper);
			AfxGetApp()->WriteProfileString("paperpath",dispaper,NULL);
			t++;
			m_stringpaper.Format("wallpaper%d",i);
			AfxGetApp()->WriteProfileString("paper",m_stringpaper,NULL);
		}
		for(j=ntextbefore-ntextafter-1;j>=0;j--)
			m_list1.DeleteItem(deletenum[j]);								//ɾ���б���еĸ���
		for(j=0;j<ntextafter;j++)							//������ע�����д��ǽֽ����
		{
			Sleep(0);
			CString m_string;
			m_string.Format("wallpaper%d",j);
			AfxGetApp()->WriteProfileString("paper",m_string,m_list1.GetItemText(j,0));
			m_string.Format("dispaper%d",j);
			AfxGetApp()->WriteProfileInt("paper",m_string,a[j]);
			m_string.Format("wallpaperpath%d",j);
			AfxGetApp()->WriteProfileString("paperpath",m_string,b[j]);
		}
	}
	AfxGetApp()->WriteProfileInt("paper","papernum",ntextafter-1);
	m_curpaper=ntextafter-1;
	if(m_curpaper<0)
	{
		if(ntextafter<=0)
		{
			m_curpaper=-1;
			m_dispmode.SetCurSel(0);
		}
		else
			m_curpaper=0;
	}
	if(m_curpaper>=0)
	{
		m_list1.SetSelectionMark(m_curpaper);
		CString dispaper;
		dispaper.Format("dispaper%d",m_curpaper);
		curdispmode=AfxGetApp()->GetProfileInt("paper",dispaper,-1);
		if(curdispmode<0)
		{
			AfxMessageBox("���ݳ���");
			return;
		}
		m_dispmode.SetCurSel(curdispmode);
		dispaper.Format("wallpaperpath%d",m_curpaper);
		strPicFile=AfxGetApp()->GetProfileString("paperpath",dispaper);
	}
	AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	MessageBox("ɾ���ɹ�!","��ʾ");
	delete [] a;
	delete [] b;
	delete [] deletenum;
	UpdateData(FALSE);
	OnPreviewPaper();
	num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
}

void CChwpDlg::OnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	AfxGetApp()->WriteProfileInt("papertime","updateday",m_paperday);
	AfxGetApp()->WriteProfileInt("papertime","updatehour",m_paperhour);
	AfxGetApp()->WriteProfileInt("papertime","updateminute",m_paperminute);
	AfxGetApp()->WriteProfileInt("papertime","updatesecond",m_papersecond);
	if(m_curpaper<0)
	{
		AfxMessageBox("�б�Ϊ�գ��޷�����ǽֽ��");
//		OnHideWindow();
		return;
	}
	int time=m_paperday*86400000+m_paperhour*3600000+m_paperminute*60000+m_papersecond*1000;
	if(time<1000)
	{
		AfxMessageBox("����ʱ�䲻��С��1�룡");
		return;
	}
	//if(m_paperday==0&&m_paperhour==0&&m_paperminute==0&&m_papersecond<10)
	//{
//		if(MessageBox("����ǰ���õ�ǽֽ����ʱ����10������,����ظ���ǽֽ��Ӵ�ϵͳ��Դռ��,ȷ����?","��ʾ",IDOK||IDCANCEL)==IDCANCEL)
//			return;
	//}
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_currentyear);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_currentday);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_currenthour);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_currentminute);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_currentsecond);

	m_lastupdateyear=AfxGetApp()->GetProfileInt("papertime","lastupdateyear",0);
	m_lastupdateday=AfxGetApp()->GetProfileInt("papertime","lastupdateday",0);
	m_lastupdatehour=AfxGetApp()->GetProfileInt("papertime","lastupdatehour",0);
	m_lastupdateminute=AfxGetApp()->GetProfileInt("papertime","lastupdateminute",0);
	m_lastupdatesecond=AfxGetApp()->GetProfileInt("papertime","lastupdatesecond",0);

	num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
//	m_list1.SetSelectionMark(-1);
	//m_timer=this->SetTimer(1,time,NULL);
	if(RUN)
	{
		pThread->SuspendThread();
		RUN=false;
	}
	Check=CheckRand;
	RunPaper=m_curpaper;
	RunTime=time;
	Papernum=num;
	str=strPicFile;
	CString dispaper;
	for(int i=0;i<=num;i++)
	{
		dispaper.Format("dispaper%d",i);
		ModeRam[i]=AfxGetApp()->GetProfileInt("paper",dispaper,0);
		dispaper.Format("wallpaperpath%d",i);
		StrRam[i]=AfxGetApp()->GetProfileString("paperpath",dispaper);

	}
	if(!RUN)
	{
		RUN=true;
		pThread->ResumeThread();
		//ResumeThread(hThread);
	}
//	OnHideWindow();
	MessageBox("�ɹ�Ӧ�õ�ϵͳ,��ʼ��������!","��ʾ");
}

// ����������
BOOL CChwpDlg::OnHideWindow(void)
{
	BOOL m_backvalue=SystemParametersInfo(SPI_SETDESKWALLPAPER,0,NULL,SPIF_UPDATEINIFILE);
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
	return TRUE;
}

void CChwpDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	if(RUN)
//	{
//		KillTimer(m_timer);	
//		RUN=false;
//		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
//	}
	int temp=m_list1.GetSelectionMark();
	if(temp<0)
		return;
	else
		m_curpaper=temp;
//	m_list1.SetHotItem(m_curpaper);
//	m_list1.GetFocus();
	num=m_list1.GetItemCount();
	CString dispaper;
	dispaper.Format("dispaper%d",m_curpaper);
	curdispmode=AfxGetApp()->GetProfileInt("paper",dispaper,-1);
	if(curdispmode<0)
	{
		AfxMessageBox("���ݳ���");
		m_dispmode.SetCurSel(0);
		return;
	}
	dispaper.Format("wallpaperpath%d",m_curpaper);
	strPicFile=AfxGetApp()->GetProfileStringA("paperpath",dispaper);
	m_dispmode.SetCurSel(curdispmode);
	OnPreviewPaper();
	*pResult = 0;
}
// ʵ��ѡ��ͼƬ��Ԥ��
BOOL CChwpDlg::OnPreviewPaper(void)
{
 	if(m_curpaper<0)
		return FALSE;
 	if(strPicFile=="")
		return FALSE;
///////////////////////////////////////////////////////////////
	if(curdispmode==0)
	{
		CClientDC DC(this);
		COLORREF   cr=GetSysColor(COLOR_BACKGROUND);//��ȡϵͳ��ǰ������ɫ
		CBrush brush;
		brush.CreateSolidBrush(cr);					//��������ɫ��ˢ
		DC.SelectObject(brush);
		DC.Rectangle(236,56,586,306);
		brush.DeleteObject();
		//return TRUE;
	}
///////////////////////////////////////////////////////////////
	HWND hWnd;
	GetDlgItem(IDC_PICTURE,&hWnd);				
	CWnd *pWnd=GetDlgItem(IDC_PICTURE);
	CDC *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetWindowRect(rect);
	int nScrWidth=rect.Width(),nScrHeight=rect.Height();
	HDC hDC_Temp=::GetDC(hWnd);
	IPicture *pPic;
	IStream *pStm;
	HANDLE hFile=NULL;
	DWORD dwFileSize,dwByteRead;
	hFile=CreateFile(strPicFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		dwFileSize=GetFileSize(hFile,NULL);
		if(dwFileSize==0xFFFFFFFF)
			return FALSE;
	}
	else
		return FALSE;
	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);
	LPVOID pvData=NULL;
	if(hGlobal==NULL)
	{
		AfxMessageBox("ͼ���ļ��������!");
		return FALSE;
	}
	if((pvData=GlobalLock(hGlobal))==NULL)
	{
		AfxMessageBox("�ڴ������������!");
		return FALSE;
	}
	ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);
	GlobalUnlock(hGlobal);
	if(CreateStreamOnHGlobal(hGlobal,TRUE,&pStm)!=S_OK)
	{
		AfxMessageBox("����ʼ��ʧ��!");
		return FALSE;
	}
	OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	double x,y;
	if(curdispmode==0)
	{
		x=(1-hmWidth/26.458/X)*350/2;
		y=(1-hmHeight/26.458/Y)*250/2;
		if(x<1)
			x=0;
		if(y<1)
			y=0;
		if(x>=350)
			x=350;
		if(y>=250)
			y=250;
		pPic->Render(hDC_Temp,x,y,nScrWidth-2*x,nScrHeight-2*y,0,hmHeight,hmWidth,-hmHeight,NULL);
	}
	else if(curdispmode==1)
	{
		x=hmWidth/26.458/X*350;
		y=hmHeight/26.458/Y*250;
		//if(x>=350&&y>=25
		if(x<1)
			x=0;
		if(y<1)
			y=0;
		if(x>=350)
			x=350;
		if(y>=250)
			y=250;
		int a=0,b=0,c=x,d=y;double e=1,f=1;
		bool temp=true;
		while(temp)
		{
			pPic->Render(hDC_Temp,a,b,c,d,0,hmHeight,hmWidth*e,-hmHeight*f,NULL);
			if(a+c>=350&&b+d>=250)
				temp=false;
			else if(a+c>=350)
			{
				a=0;
				e=1;
				c=x;
				b+=y;
				if(b+d>=250)
				{
					f=1-(b+d-250.0)/y;
					if(f>0.5)
						f/=1.1;
					d=250-b;
				}
			}
			else
			{
				a+=x;				
				if(a+c>=350)
				{
					e=1-(a+c-350.0)/x;
					if(e>0.5)
						e/=1.1;
					c=350-a;
				}
			}
		}
	}
	else if(curdispmode==2)
	{
		pPic->Render(hDC_Temp,0,0,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL);
	}
	CloseHandle(hFile);
	pPic->Release();
	GlobalFree(hGlobal);
	//HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),strPicFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	//m_picture.ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	//m_picture.SetBitmap(hbitmap);
	return TRUE;
	
}

/*
void CChwpDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if(nIDEvent==m_timer) //�жϴ��ݹ�����ʱ�Ӵ������Ƿ����Լ������ʱ�Ӵ�����
	{
		//��ʼ������m_date���õ���ǰ���ڲ������������
		if(!SetWallPaper())
			AfxMessageBox("��������ʧ�ܣ�");
		else
		{
			//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
			if(CheckRand&&num>1)
			{
				int ans;
				do
				{
					ans=rand()*num/RAND_MAX; 
				}while(ans==m_curpaper);
				m_curpaper=ans;
			}
			else
				++m_curpaper;
			if(m_curpaper>num)
				m_curpaper=0;
			CString m_curstring;
			m_curstring.Format("dispaper%d",m_curpaper);
			curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
			if(curdispmode<0)
			{
				AfxMessageBox("���ݳ���");
				return;
			}
			m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
			strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
			m_lastupdateyear=m_date.GetYear();
			m_lastupdateday=m_date.GetDayOfYear();
			m_lastupdatehour=m_date.GetHour();
			m_lastupdateminute=m_date.GetMinute();
			m_lastupdatesecond=m_date.GetSecond();
		}

	}
	CDialog::OnTimer(nIDEvent);
}
*/
void CChwpDlg::OnChangeMode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(RUN)
//	{
//		KillTimer(m_timer);	
//		RUN=false;
//		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
//	}
	UpdateData(TRUE);
	if(m_curpaper<0)
	{
		MessageBox("�ļ��б�Ϊ�գ�","ע��");
		return;
	}
	POSITION pos=m_list1.GetFirstSelectedItemPosition();
	if(!pos)
		return;
	CString dispaper;
	curdispmode=m_dispmode.GetCurSel();
	if(curdispmode<0)
		curdispmode=0;
	while(pos)
	{
		m_curpaper=m_list1.GetNextSelectedItem(pos);
		dispaper.Format("dispaper%d",m_curpaper);
		while(changing)
			Sleep(0);
		AfxGetApp()->WriteProfileInt("paper",dispaper,curdispmode);
	}
	dispaper.Format("wallpaperpath%d",m_curpaper);
	while(changing)
		Sleep(0);
	strPicFile=AfxGetApp()->GetProfileStringA("paperpath",dispaper);
	OnPreviewPaper();
}

// ��˫��֪ͨ���ϵ�ͼ��ʱ���õĺ���
void CChwpDlg::OnShowMainDialog(void)
{
//	if(RUN)
//	{
//		KillTimer(m_timer);	
//		RUN=false;
//		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
///		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
//		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
//	}
//	else
//	{
		m_curpaper=AfxGetApp()->GetProfileIntA("paper","currentpaper",-1);
		if(m_curpaper==-1)
		{
			MessageBox("�б�Ϊ�գ�","��ʾ");
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
		}
		else if(m_curpaper<0)
		{
			AfxMessageBox("���ݳ���");
			return;
		}
//	}
	CString m_curstring;
	m_curstring.Format("dispaper%d",m_curpaper);
	curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
	if(curdispmode<0)
	{
		AfxMessageBox("���ݳ���");
		return;
	}
	m_dispmode.SetCurSel(curdispmode);
	m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
	strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
} 

// ����������֪ͨ��ͼ��ʱ���õĺ���
void CChwpDlg::OnContextMenu2(CWnd * pWnd)
{
	CMenu menu;
	if(menu.LoadMenu(IDR_MENU1))
	{
		CMenu * popup=menu.GetSubMenu(0);
		ASSERT(popup!=NULL);
		CPoint mouse;
		GetCursorPos(& mouse);
		::SetForegroundWindow(data.hWnd);
		popup->TrackPopupMenu(TPM_LEFTALIGN,mouse.x,mouse.y,pWnd,NULL);
	}

}

// ����һ�����桱�˵�����Ӧ����
void CChwpDlg::OnNext(void)
{
	Sleep(0);
	if(m_curpaper<0)
	{
		AfxMessageBox("�б�Ϊ�գ���������ļ���");
		return;
	}
	if(!SetWallPaper())
		AfxMessageBox("��������ʧ�ܣ�");
	else
	{
		//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
		++m_curpaper;
		if(m_curpaper>num)
			m_curpaper=0;
		CString m_curstring;
		m_curstring.Format("dispaper%d",m_curpaper);
		while(changing)
			Sleep(0);
		curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
		m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
		while(changing)
			Sleep(0);
		strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
		m_lastupdateyear=m_date.GetYear();
		m_lastupdateday=m_date.GetDayOfYear();
		m_lastupdatehour=m_date.GetHour();
		m_lastupdateminute=m_date.GetMinute();
		m_lastupdatesecond=m_date.GetSecond();
		while(changing)
			Sleep(0);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	}
}

// ����һ�����桱�˵�����Ӧ����
void CChwpDlg::OnLast(void)
{
	Sleep(0);
	if(m_curpaper<0)
	{
		AfxMessageBox("�б�Ϊ�գ���������ļ���");
		return;
	}
	if(!SetWallPaper())
		AfxMessageBox("��������ʧ�ܣ�");
	else
	{
		//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
		--m_curpaper;
		if(m_curpaper<0)
			m_curpaper=num;
		CString m_curstring;
		m_curstring.Format("dispaper%d",m_curpaper);
		while(changing)
			Sleep(0);
		curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
		m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
		while(changing)
			Sleep(0);
		strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
		m_lastupdateyear=m_date.GetYear();
		m_lastupdateday=m_date.GetDayOfYear();
		m_lastupdatehour=m_date.GetHour();
		m_lastupdateminute=m_date.GetMinute();
		m_lastupdatesecond=m_date.GetSecond();
		while(changing)
			Sleep(0);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	}
}

// ����ͣ���˵�����Ӧ����
void CChwpDlg::OnPause(void)
{
	while(changing)
		Sleep(0);
	if(RUN)
	{
		//KillTimer(m_timer);
		pThread->SuspendThread();
		RUN=false;
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
	}
}

// �����˵�����Ӧ����
void CChwpDlg::OnContinue(void)
{
	Sleep(0);
	if(m_curpaper<0)
	{
		AfxMessageBox("�б�Ϊ�գ���������ļ���");
		return;
	}
	int time=m_paperday*86400000+m_paperhour*3600000+m_paperminute*60000+m_papersecond*1000;
	if(time<1000)
	{
		AfxMessageBox("����ʱ�䲻��С��1�룡");
		return;
	}
	if(!RUN)
	{
		pThread->ResumeThread();
		RUN=true;
	}
//	m_timer=this->SetTimer(1,time,NULL);
}

// ����ͼƬΪ���汳��
BOOL CChwpDlg::SetWallPaper()
{
	hr = CoCreateInstance (CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,IID_IActiveDesktop, (void**) &pIAD );
	if(!SUCCEEDED(hr)) 
		AfxMessageBox("�����ӿ�ʵ������");
	
	CString str2=strPicFile;
	//���ļ�����Ϊ���ַ���,����IActiveDesktop::SetWallpaper��Ҫ��
	WCHAR   wszWallpaper2 [MAX_PATH];
	LPTSTR lpStr2 = str2.GetBuffer(str2.GetLength() );
	MultiByteToWideChar(CP_ACP, 0, lpStr2, -1, wszWallpaper2, MAX_PATH);
	str2.ReleaseBuffer();
	//����ǽֽ����ʽ
	WALLPAPEROPT wpo2;
	wpo2.dwSize = sizeof(wpo2);
	wpo2.dwStyle = curdispmode;
	while(changing)
		Sleep(0);
	//����ǽֽ
	hr = pIAD->SetWallpaper(wszWallpaper2, 0);
	if(!SUCCEEDED(hr)) 
		return FALSE;
	while(changing)
		Sleep(0);
	hr = pIAD->SetWallpaperOptions(&wpo2, 0);
	if(!SUCCEEDED(hr))
		return FALSE;
	//Ӧ��ǽֽ������
	while(changing)
		Sleep(0);
	hr = pIAD->ApplyChanges(AD_APPLY_ALL);
	Sleep(0);
	if(!SUCCEEDED(hr))
		return FALSE;
	//��ȡǽֽ���ļ�������ӡ��debug������
	//hr = pIAD->GetWallpaper(wszWallpaper, MAX_PATH, 0);
	//CString strFile = wszWallpaper;
	//TRACE(str); //�������λͼ�Ļ�,�����������벻���ķ���
	//�ͷŽӿڵ�ʵ��
	pIAD->Release();
	
	return TRUE;
}
void CChwpDlg::OnDropFiles(HDROP hDropInfo)
{
	Sleep(0);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char szFilePathName[_MAX_PATH+1];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	UINT nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//�õ��ļ�����
	CString filename,filepath,fileext;
	int nums;
	int item;
	char c;
	CString stringpaper,stringpath,dispaper;
	for (UINT nIndex=0 ; nIndex< nNumOfFiles; ++nIndex)
	{
		Sleep(0);
		DragQueryFile(hDropInfo, nIndex, szFilePathName, _MAX_PATH); //�õ��ļ���
		filepath=szFilePathName;
		_splitpath(filepath,drive,dir,fname,ext);//����ļ�����������·�����Ϊ�ĸ����֣��ֱ���
		if(drive[0]>96&&drive[0]<123)
			drive[0]-=32;
		filename=fname;
		filename+=ext;
		fileext=ext;
		if(fileext!=".bmp"&&fileext!=".BMP"&&fileext!=".dib"&&fileext!=".DIB"&&fileext!=".jpg"&&fileext!=".JPG"&&fileext!=".jpeg"&&fileext!=".JPEG"&&fileext!=".jpe"&&fileext!=".JPE"&&fileext!=".jfif"&&fileext!=".JFIF"&&fileext!=".gif"&&fileext!=".GIF"&&fileext!=".png"&&fileext!=".PNG")
		{
			AfxMessageBox("�Բ��𣬱�����ݲ�֧�ָø�ʽ�ļ�������ʹ�ø��ļ�����ʹ�ø�ʽת�����ת���ļ���ʽ��");
			num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
			return;
		}
		nums=m_list1.GetItemCount();
		if(nums==1000)
		{
			AfxMessageBox("���ֻ�ܼ���1000���ļ���");
			num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
			return;
		}
		for(int i=0;i<nums;i++)
		{
			if(strcmp(m_list1.GetItemText(i,0),filename)==0)
			{
				AfxMessageBox("�ļ��Ѿ�����!");
				num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
				return;
			}
		}
		c=fileext[1];
		if(c=='b'||c=='B'||c=='d'||c=='D')
			item=0;
		else if(c=='j'||c=='J')
			item=1;
		else if(c=='g'||c=='G')
			item=2;
		else if(c=='p'||c=='P')
			item=3;
		else
		{
			AfxMessageBox("�ļ���������˲飡");
			num=AfxGetApp()->GetProfileInt("paper","papernum",-1);
			return;
		}
		m_list1.InsertItem(nums,filename,item);
		stringpaper.Format("wallpaper%d",nums);
		stringpath.Format("wallpaperpath%d",nums);
		dispaper.Format("dispaper%d",nums);
		//дע���
		curdispmode=m_dispmode.GetCurSel();
		if(curdispmode<0)
			curdispmode=0;
		AfxGetApp()->WriteProfileInt("paper",dispaper,curdispmode);
		AfxGetApp()->WriteProfileString("paper",stringpaper,filename);
		AfxGetApp()->WriteProfileString("paperpath",stringpath,filepath);
		AfxGetApp()->WriteProfileInt("paper","papernum",nums);
	}
	m_curpaper=nums;
	strPicFile=filepath;
	AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	AfxGetApp()->WriteProfileInt("paper","papernum",nums);
	num=nums;
	m_list1.SetSelectionMark(m_curpaper);
	DragFinish(hDropInfo);	
	OnPreviewPaper();
	CDialog::OnDropFiles(hDropInfo);
}
HBRUSH CChwpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	Sleep(0);
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//if(nCtlColor

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return m_brush;
}


// �̺߳���
UINT ThreadProc(LPVOID pParam)
{
	AfxOleInit();
	COleDateTime m_date2;
	changing=false;
	while(!IfExit)
	{
		Sleep(RunTime-300);

		m_date2=COleDateTime::GetCurrentTime();
		hr = CoCreateInstance (CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,IID_IActiveDesktop, (void**) &pIAD );
		if(!SUCCEEDED(hr)) 
			AfxMessageBox("�̺߳����д����ӿ�ʵ������");
		//theApp.m
		//HRESULT hr;
		//IActiveDesktop* pIAD;
		//�����ӿڵ�ʵ��
		//hr = CoCreateInstance (CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,IID_IActiveDesktop, (void**) &pIAD );
		//AfxMessageBox("���ڵ��ã�");
		//if(!SUCCEEDED(hr)) 
		//	continue;
		//���ļ�����Ϊ���ַ���,����IActiveDesktop::SetWallpaper��Ҫ��

		
		
		



	
		WCHAR   wszWallpaper2 [MAX_PATH];
		LPTSTR lpStr2 = str.GetBuffer(str.GetLength() );
		MultiByteToWideChar(CP_ACP, 0, lpStr2, -1, wszWallpaper2, MAX_PATH);
		str.ReleaseBuffer();
		//����ǽֽ
		Sleep(0);
		changing=true;
		hr = pIAD->SetWallpaper(wszWallpaper2, 0);
		if(!SUCCEEDED(hr)) 
			AfxMessageBox("����ǽֽ����");
		//����ǽֽ����ʽ
		WALLPAPEROPT wpo2;
		wpo2.dwSize = sizeof(wpo2);
		wpo2.dwStyle = mode;
		hr = pIAD->SetWallpaperOptions(&wpo2, 0);
		if(!SUCCEEDED(hr))
			AfxMessageBox("����ǽֽ����");
		//Ӧ��ǽֽ������
		Sleep(0);
		hr = pIAD->ApplyChanges(AD_APPLY_ALL);
		Sleep(0);
		if(!SUCCEEDED(hr))
			AfxMessageBox("����ǽֽ����");
		///��ȡǽֽ���ļ�������ӡ��debug������
		//hr = pIAD->GetWallpaper(wszWallpaper, MAX_PATH, 0);
		//CString strFile = wszWallpaper;
		//TRACE(str); //�������λͼ�Ļ�,�����������벻���ķ���
		//�ͷŽӿڵ�ʵ��
		pIAD->Release();
		changing=false;


		if(Check&&Papernum>1)
		{
			int ans;
			do
			{
				ans=rand()*Papernum/RAND_MAX; 
			}while(ans==RunPaper);
			RunPaper=ans;
		}
		else
			++RunPaper;
		if(RunPaper>Papernum)
			RunPaper=0;
		str=StrRam[RunPaper];
		mode=ModeRam[RunPaper];
		if(mode<0)
		{
			AfxMessageBox("���ݳ���");
			return 0;
		}
		m_lastupdateyear=m_date2.GetYear();
		m_lastupdateday=m_date2.GetDayOfYear();
		m_lastupdatehour=m_date2.GetHour();
		m_lastupdateminute=m_date2.GetMinute();
		m_lastupdatesecond=m_date2.GetSecond();
	}
	return 0;
}


void CAboutDlg::OnPaint()
{

	CPaintDC dc(this); // device context for painting
	CRect    rect;     
	GetClientRect(rect);     
	dc.FillSolidRect(rect,RGB(255,255,255));     
	CDialog::OnPaint();
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	Sleep(0);
	// TODO:  �ڴ˸��� DC ���κ�����
	CBrush m_brush2;
	m_brush2.CreateSolidBrush(RGB(0,0,0));

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brush2;
}

void CChwpDlg::OnBnClickedButtonhide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_curpaper<0)
		MessageBox("�б�Ϊ�գ�","��ʾ");
	OnHideWindow();
}

void CChwpDlg::OnBnClickedButtonpause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	while(changing)
		Sleep(0);
	if(RUN)
	{
		//KillTimer(m_timer);
		pThread->SuspendThread();
		RUN=false;
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
		MessageBox("��ͣ����!","��ʾ");
	}
	else
		AfxMessageBox("��δ��ʼ����!");
}

void CChwpDlg::OnBnClickedButtoncontinue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Sleep(0);
	if(m_curpaper<0)
	{
		AfxMessageBox("�б�Ϊ�գ���������ļ���");
		return;
	}
	int time=m_paperday*86400000+m_paperhour*3600000+m_paperminute*60000+m_papersecond*1000;
	if(time<1000)
	{
		AfxMessageBox("����ʱ�䲻��С��1�룡");
		return;
	}
	if(!RUN)
	{
		pThread->ResumeThread();
		RUN=true;
		MessageBox("��ʼ����!","��ʾ");
	}
	else
		AfxMessageBox("�Ѿ���������!");
}

void CChwpDlg::OnBnClickedButtonlast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Sleep(0);
	int temp=m_list1.GetSelectionMark();
	if(temp<0)
	{
		AfxMessageBox("δѡ���ļ���");
		return;
	}
	else
		m_curpaper=temp;
	if(!SetWallPaper())
		AfxMessageBox("��������ʧ�ܣ�");
	else
	{
		OnPreviewPaper();
		//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
		--m_curpaper;
		if(m_curpaper<0)
			m_curpaper=num;
		m_list1.SetSelectionMark(m_curpaper);
		CString m_curstring;
		m_curstring.Format("dispaper%d",m_curpaper);
		while(changing)
			Sleep(0);
		curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
		m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
		while(changing)
			Sleep(0);
		strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
		m_lastupdateyear=m_date.GetYear();
		m_lastupdateday=m_date.GetDayOfYear();
		m_lastupdatehour=m_date.GetHour();
		m_lastupdateminute=m_date.GetMinute();
		m_lastupdatesecond=m_date.GetSecond();
		while(changing)
			Sleep(0);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	}
}

void CChwpDlg::OnBnClickedButtonnext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Sleep(0);
	int temp=m_list1.GetSelectionMark();
	if(temp<0)
	{
		AfxMessageBox("δѡ���ļ���");
		return;
	}
	else
		m_curpaper=temp;
	if(!SetWallPaper())
		AfxMessageBox("��������ʧ�ܣ�");
	else
	{
		//��ǰǽֽ��ź��ƣ����ǽֽ�ĸ���
		OnPreviewPaper();
		++m_curpaper;
		if(m_curpaper>num)
			m_curpaper=0;
		m_list1.SetSelectionMark(m_curpaper);
		CString m_curstring;
		m_curstring.Format("dispaper%d",m_curpaper);
		while(changing)
			Sleep(0);
		curdispmode=AfxGetApp()->GetProfileInt("paper",m_curstring,-1);
		m_curstring.Format("wallpaperpath%d",m_curpaper);					//����ŵõ���Ӧ·����ע������
		while(changing)
			Sleep(0);
		strPicFile=AfxGetApp()->GetProfileString("paperpath",m_curstring);//����ע���õ���ǰǽֽ·��
		m_lastupdateyear=m_date.GetYear();
		m_lastupdateday=m_date.GetDayOfYear();
		m_lastupdatehour=m_date.GetHour();
		m_lastupdateminute=m_date.GetMinute();
		m_lastupdatesecond=m_date.GetSecond();
		while(changing)
			Sleep(0);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateyear",m_lastupdateyear);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateday",m_lastupdateday);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatehour",m_lastupdatehour);
		AfxGetApp()->WriteProfileInt("papertime","lastupdateminute",m_lastupdateminute);
		AfxGetApp()->WriteProfileInt("papertime","lastupdatesecond",m_lastupdatesecond);
		AfxGetApp()->WriteProfileInt("paper","currentpaper",m_curpaper);
	}
}
