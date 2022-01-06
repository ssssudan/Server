// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "ClientSocket.h"
#include "ServerDlg.h"


// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// ClientSocket 멤버 함수

void ClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: 여기에 구현 코드 추가.
	m_pServerSocket = pSocket;
}

void ClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ServerSocket* pServerSocket = (ServerSocket*)m_pServerSocket;
	pServerSocket->CloseClientSocket(this);

	CSocket::OnClose(nErrorCode);
}



void ClientSocket::OnReceive(int nErrorCode)
{ 
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char szBuffer[256] = { 0, };
	
	CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
	ServerSocket* pServerSocket = (ServerSocket*)m_pServerSocket;

	if (Receive(szBuffer, 256) > 0)
	{
		if (szBuffer[0] == -84) {
			for (int i = 0; i <= 248; i++) {
				szBuffer[i] = szBuffer[i + 7];
			}
			pMain->m_strMessage = szBuffer;
			int cnt = pMain->m_List.GetCount();
			pMain->m_List.InsertString(cnt, pMain->m_strMessage);
			pServerSocket->SendDataAll(szBuffer);
		}
		else {
			pMain->m_strMessage = szBuffer;
			int cnt = pMain->m_List.GetCount();
			pMain->m_List.InsertString(cnt, pMain->m_strMessage);
			pServerSocket->SendDataAll(szBuffer);
		}
	}
	CSocket::OnReceive(nErrorCode);
}
