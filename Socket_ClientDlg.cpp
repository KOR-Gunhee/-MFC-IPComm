
// Socket_ClientDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSocket_ClientDlg 대화 상자



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


// CSocket_ClientDlg 메시지 처리기

BOOL CSocket_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_edit_ip.SetWindowTextA(_T("192.168.4.1"));
	m_edit_ip.SetWindowTextA(_T("IP:192.168.4.2"));
	m_edit_port.SetWindowTextA(_T("8002"));
	m_edit_port2.SetWindowTextA(_T("8001"));
	m_edit_card.SetWindowTextA(_T("Test_200903#1"));
	m_edit_bit.SetWindowTextA(_T("./fpgautil -b /mnt/system.bit"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSocket_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CSocket_ClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

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
	
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
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
	// TODO: 여기에 컨트V롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strbit;

	m_edit_bit.GetWindowTextA(strbit);

	m_ClientSocket.Send(strbit, strbit.GetLength());
}


void CSocket_ClientDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientSocket.Send(strtest, strtest.GetLength());
}
