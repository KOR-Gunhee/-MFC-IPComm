#pragma once

// CClientSocket ��� ����Դϴ�.

#define WM_CLIENT_RECV WM_USER+1

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	HWND m_hWnd;
	void SetWnd(HWND hWnd);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);


};


