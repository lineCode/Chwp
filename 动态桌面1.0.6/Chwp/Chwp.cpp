// Chwp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Chwp.h"
#include "ChwpDlg.h"

#include <shlobj.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChwpApp

BEGIN_MESSAGE_MAP(CChwpApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChwpApp ����

CChwpApp::CChwpApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CChwpApp ����

CChwpApp theApp;


// CChwpApp ��ʼ��

BOOL CChwpApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	AfxOleInit();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
/////////////////////////////////////////////////////////

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(__argv[0],drive,dir,fname,ext);//����ļ�����������·�����Ϊ�ĸ����֣��ֱ���
	if(drive[0]>96&&drive[0]<123)
		drive[0]-=32;
	CString path(drive);
	path+=dir;
	path+="��̬����.exe";
	TCHAR m_path[MAX_PATH];
	wsprintf(m_path,path);

	//���ñ�����Ϊ��������
	HKEY hkey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\Currentversion\\Run",0,KEY_WRITE,& hkey);//��ע�����
	RegSetValueEx(hkey,"��̬����",0,REG_SZ,(LPBYTE)m_path,lstrlen(m_path)+1);//����ע����ֵ
	RegCloseKey(hkey);							//�ͷ�ָ��ע����ľ��
	SetRegistryKey(_T("��̬����"));//��ע�����д�뱾������
	LoadStdProfileSettings(1000);			//ȷ�����Ҽ������ʹ�õ��ļ�����������״̬
////////////////////////////////////////////
///////////////////////////////////////////
	CChwpDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
