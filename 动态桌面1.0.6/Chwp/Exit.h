#pragma once


// CExit �Ի���

class CExit : public CDialog
{
	DECLARE_DYNAMIC(CExit)

public:
	CExit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExit();

// �Ի�������
	enum { IDD = IDD_DIALOGEXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	bool IFEXIT;
};
