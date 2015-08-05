// ChwpDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


static HRESULT hr;
static IActiveDesktop* pIAD;

// �̴߳�����
//void ThreadProc(void);
//���ڴ��ǽֽ·����ȫ������
static CString StrRam[1000];
//���ڴ��ǽֽ��ʾģʽ��ȫ������
static int ModeRam[1000]={0};
//�̺߳����еĵ�ǰǽֽ���
static int RunPaper;
//�̺߳����еĸ���ʱ��
static int RunTime;
//ָʾ�����Ƿ�Ӧ�ý���
static bool IfExit=false;
//�̺߳����е�ǽֽ����
static int Papernum;
//�߳��е�ǽֽ��ʾģʽ
static int mode;
//ָʾ�߳��Ƿ����ڻ�����
static bool changing=false;
//�߳��еĵ�ǰǽֽ·��
static CString str;
//ָʾ���ģʽ�Ƿ�ѡ��
static BOOL Check;
	// �ϴθ���ʱ�����
static int m_lastupdateyear=0;
	// �ϴθ���ʱ������
static int m_lastupdateday=0;
	// �ϴθ��µ�ʱ��Сʱ��
static int m_lastupdatehour=0;
	// �ϴθ���ʱ�ķ�����
static int m_lastupdateminute=0;
	// �ϴθ���ʱ��������
static int m_lastupdatesecond=0;

// CChwpDlg �Ի���
class CChwpDlg : public CDialog
{
// ����
public:
	CChwpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHWP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExit();
protected:
	NOTIFYICONDATA data;
public:
	CSpinButtonCtrl m_spin1;
	CSpinButtonCtrl m_spin2;
	CSpinButtonCtrl m_spin3;
	CSpinButtonCtrl m_spin4;
	CListCtrl m_list1;
protected:
	CImageList m_image;
	LRESULT OnStatusIcon(WPARAM wparam, LPARAM lparam);
public:
	// ϵͳ��Ϣ��ͼ����Ҽ������˵�
	void OnContextMenu(CWnd* pWnd);
protected:
	// ����ʽ�˵���ʾ���ڶԻ���
	void OnMenuAbout(void);
	// ����ʽ�˵����˳���ť
	void OnMenuExit(void);
protected:
	afx_msg void OnAddpaper();
public:
	afx_msg void OnDeletepaper();
	// ��Ͽ�ӳ��ı�����ָʾǽֽ��ʾģʽ
	CComboBox m_dispmode;
protected:
	// ָʾ��ǰǽֽ�����
	int m_curpaper;
	// ����
	COleDateTime m_date;
public:
	// ��ǰ���ڣ��죩
	int m_currentday;
	// ��ǰʱ�䣨Сʱ��
	int m_currenthour;
	// ��ǰʱ�䣨���ӣ�
	int m_currentminute;
	// ��ǰʱ�䣨���ӣ�
	int m_currentsecond;
	// ���õĸ���ʱ���е�����
	int m_paperday;
	// ���õĸ���ʱ���Сʱ��
	int m_paperhour;
	// ���õĸ���ʱ���еķ�����
	int m_paperminute;
	// ���õĸ���ʱ���������
	int m_papersecond;
	// ��ǰʱ������
	int m_currentyear;

protected:
	afx_msg void OnOk();
	// ����������
	BOOL OnHideWindow(void);
protected:
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	// ͼƬ�����
	CStatic m_picture;
public:
	// ʵ��ѡ��ͼƬ��Ԥ��
	BOOL OnPreviewPaper(void);

//protected:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	// ʱ�Ӵ�����
//	UINT m_timer;

protected:
	afx_msg void OnChangeMode();
public:
	// ��ǰǽֽ����
	int num;
protected:
	// ��˫��֪ͨ���ϵ�ͼ��ʱ���õĺ���
	void OnShowMainDialog(void);
public:
	// ����������֪ͨ��ͼ��ʱ���õĺ���
	void OnContextMenu2(CWnd * pWnd);
protected:
	// ����һ�����桱�˵�����Ӧ����
	void OnNext(void);
	// ����һ�����桱�˵�����Ӧ����
	void OnLast(void);
	// ��ͣ�˵�����Ӧ����
	void OnPause(void);
	// �����˵�����Ӧ����
	void OnContinue(void);
	// ����ͼƬΪ���汳��

public:
	 BOOL SetWallPaper();
	// ��ǰǽֽ����ʾģʽ
	DWORD curdispmode;
	// ��ǰǽֽ��·��
	CString strPicFile;

public:
	// ָʾʱ�Ӵ������Ƿ���
	bool RUN;

protected:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	// ��ɫ��ˢ
	CBrush m_brush;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	// ָʾ�Ƿ�ѡ�����ģʽ
	BOOL CheckRand;
public:
	CWinThread *pThread;
	// ��ǰ��Ļ�ֱ��ʺ�����
	int X;
	// ��ǰ��Ļ�ֱ���������
	int Y;
	afx_msg void OnBnClickedButtonhide();
	afx_msg void OnBnClickedButtonpause();
	afx_msg void OnBnClickedButtoncontinue();
	afx_msg void OnBnClickedButtonlast();
	afx_msg void OnBnClickedButtonnext();
};
	UINT ThreadProc(LPVOID pParam);
