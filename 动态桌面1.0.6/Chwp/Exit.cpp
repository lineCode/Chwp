// Exit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chwp.h"
#include "ChwpDlg.h"
#include "Exit.h"

// CExit �Ի���

IMPLEMENT_DYNAMIC(CExit, CDialog)

CExit::CExit(CWnd* pParent /*=NULL*/)
	: CDialog(CExit::IDD, pParent)
	, IFEXIT(false)
{
	
}

CExit::~CExit()
{
}

void CExit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExit, CDialog)
	ON_BN_CLICKED(IDOK, &CExit::OnBnClickedOk)
END_MESSAGE_MAP()


// CExit ��Ϣ�������

void CExit::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IFEXIT=true;
	OnOK();
}

//void CExit::OnBnClickedButton1()
//{
//	IfExit=true;
//	OnOK();
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
