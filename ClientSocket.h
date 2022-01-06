#pragma once

// ClientSocket 명령 대상

class ClientSocket : public CSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();
	
	CAsyncSocket* m_pServerSocket = NULL;
	virtual void OnClose(int nErrorCode);
	void SetListenSocket(CAsyncSocket* pSocket);
	virtual void OnReceive(int nErrorCode);
};


