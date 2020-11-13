
// Socket_ClientDlg.h : ��� ����
//

#pragma once

#include "ClientSocket.h"
#include "afxwin.h"
#include "SqlDll_Interface.h"

#define WM_COUNT_RECV WM_USER+2

// CSocket_ClientDlg ��ȭ ����
class CSocket_ClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
