
// Socket_ClientDlg.h : 헤더 파일
//

#pragma once

#include "ClientSocket.h"
#include "afxwin.h"
#include "SqlDll_Interface.h"

#define WM_COUNT_RECV WM_USER+2

// CSocket_ClientDlg 대화 상자
class CSocket_ClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CClientSocket m_ClientSocket;

public:
	CListBox m_list_msg;
	CEdit m_edit_send;
	
protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnConnect();
	CEdit m_edit_ip;
	CEdit m_edit_port;
	CEdit m_edit_port2;
	CEdit m_edit_msg;
	CEdit m_edit_card;
	CEdit m_edit_bit;
	bool CountRecv(CDB_SQL* pDB_SQL);
	afx_msg void OnBnClickedBtnInspection();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	CString strtest = "./hispeedtest\n";
	CString strcount = "";
	CString strresult = "Fails";
	bool bInspectionflag = 0;

protected:
//	afx_msg LRESULT OnCountRecv(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnBnClickedBtnBitsend();
	afx_msg void OnBnClickedBtnTest();
};
