#pragma once

// ServerSocket 명령 대상

class ServerSocket : public CAsyncSocket
{
public:
	ServerSocket();
	virtual ~ServerSocket();
	
	CPtrList m_ptrClientSocketList;
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendDataAll(char buf[256]);

};


