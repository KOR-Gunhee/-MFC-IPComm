
// Socket_ClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"
#include "afxdialogex.h"
#include "SimpleFtp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define PORT 9999

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocket_ClientDlg ��ȭ ����



CSocket_ClientDlg::CSocket_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKET_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Control(pDX, IDC_EDIT_IP, m_edit_ip);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edit_port);
	DDX_Control(pDX, IDC_EDIT_PORT2, m_edit_port2);
	DDX_Control(pDX, IDC_EDIT_MSG, m_edit_msg);
	DDX_Control(pDX, IDC_EDIT_CARD, m_edit_card);
	DDX_Control(pDX, IDC_EDIT_BIT, m_edit_bit);
}

BEGIN_MESSAGE_MAP(CSocket_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_CLIENT_RECV, &CSocket_ClientDlg::OnClientRecv)
//	ON_MESSAGE(WM_COUNT_RECV, &CSocket_ClientDlg::OnCountRecv)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSocket_ClientDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CSocket_ClientDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_INSPECTION, &CSocket_ClientDlg::OnBnClickedBtnInspection)
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTN_BITSEND, &CSocket_ClientDlg::OnBnClickedBtnBitsend)
	ON_BN_CLICKED(IDC_BTN_TEST, &CSocket_ClientDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CSocket_ClientDlg �޽��� ó����

BOOL CSocket_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_edit_ip.SetWindowTextA(_T("192.168.4.1"));
	m_edit_ip.SetWindowTextA(_T("IP:192.168.4.2"));
	m_edit_port.SetWindowTextA(_T("8002"));
	m_edit_port2.SetWindowTextA(_T("8001"));
	m_edit_card.SetWindowTextA(_T("Test_200903#1"));
	m_edit_bit.SetWindowTextA(_T("./fpgautil -b /mnt/system.bit"));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSocket_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSocket_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CSocket_ClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_MSG)
		{
			if (str_mydata == "0")
			{
				pDC->SetTextColor(RGB(0, 255, 0));
			}
		}
	}
	
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

afx_msg LRESULT CSocket_ClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;
	CString str;
	
	str += "\n";

	if (bInspectionflag)
	{
		CDB_SQL* pDB_SQL = CDB_SQL::Create();

		strresult = "Fails";
		strcount = str_mydata;


		if (strstr(strcount, "0"))
		{
			strresult = "OK";
		}
		m_edit_msg.SetSel(-2, -1);
		m_edit_msg.ReplaceSel(strcount + str);

		CountRecv(pDB_SQL);

		delete pDB_SQL;
		pDB_SQL = NULL;
	}
	else
	{
		m_edit_msg.SetSel(-2, -1);
		m_edit_msg.ReplaceSel(str_mydata + str);
	}

	return 0;
}

void CSocket_ClientDlg::OnBnClickedBtnSend()
{
	// TODO: ���⿡ ��ƮV�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	UpdateData(TRUE);
	m_edit_send.GetWindowTextA(str);
	str += "\n";

	//m_edit_msg.SetWindowTextA(str);
	m_edit_msg.SetSel(-2, -1);
	m_edit_msg.ReplaceSel("[Send] : " + str);

	m_ClientSocket.Send(str, str.GetLength());
	//m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GemtLength() * 2);
	m_edit_send.SetWindowTextA(_T(""));
	UpdateData(FALSE);
}

void CSocket_ClientDlg::OnBnClickedBtnConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString IP;
	int Loacl,Target = 0;

	UpdateData(TRUE);

	m_edit_ip.GetWindowTextA(IP);
	Target = GetDlgItemInt(IDC_EDIT_PORT2);
	Loacl = GetDlgItemInt(IDC_EDIT_PORT);

	UpdateData(FALSE);

	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create(Loacl,SOCK_DGRAM);
		
	if (m_ClientSocket.Connect(IP, Target) == FALSE)
	{
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
	}
	else
	{
		AfxMessageBox(_T("CONNECT: Successed to connect Server"));
	}

	//if (m_ClientSocket.Connect((_T("127.0.0.1")), 9999) == FALSE)
	//{
	//	AfxMessageBox(_T("ERROR : Failed to connect Server"));
	//	PostQuitMessage(0);
	//}
}

void CSocket_ClientDlg::OnBnClickedBtnInspection()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	bInspectionflag = 1;
}

bool CSocket_ClientDlg::CountRecv(CDB_SQL* pDB_SQL)
{
	CString strcard, strbit, strWifi;

	pDB_SQL->Init(_T("WIFI"));

	m_edit_card.GetWindowTextA(strcard);
	m_edit_bit.GetWindowTextA(strbit);

	strWifi.Format(_T("Insert Into sda.Test values('%s','%s','%s','%s')"), strcard, strbit, strcount, strresult);

	return SQL_Execute(pDB_SQL, strWifi);
}

//afx_msg LRESULT CSocket_ClientDlg::OnCountRecv(WPARAM wParam, LPARAM lParam)
//{
//	CString strCard, strBin, strWifi;
//	
//	CDB_SQL* pDB_SQL = CDB_SQL::Create();
//	pDB_SQL->Init(_T("WIFI"));
//
//	m_edit_card.GetWindowTextA(strCard);
//	m_edit_bin.GetWindowTextA(strBin);
//
//	strWifi.Format(_T("Insert Into sda.Test values('%s','%s')"), strCard, strBin);
//
//	delete pDB_SQL;
//
//	pDB_SQL = NULL;
//
//	return SQL_Execute(pDB_SQL, strWifi);
//
//
//	//return 0;
//}

void CSocket_ClientDlg::OnBnClickedBtnBitsend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strbit;

	m_edit_bit.GetWindowTextA(strbit);

	m_ClientSocket.Send(strbit, strbit.GetLength());
}


void CSocket_ClientDlg::OnBnClickedBtnTest()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ClientSocket.Send(strtest, strtest.GetLength());
}
