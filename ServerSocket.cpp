// ServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"
#include "ClientSocket.h"

// ServerSocket

ServerSocket::ServerSocket()
{
}

ServerSocket::~ServerSocket()
{
}


// ServerSocket 멤버 함수


void ServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ClientSocket* pClient = new ClientSocket;
	CString str;
	if (Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);

		CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd(); // CSocketServerDlg의 핸들을 가져옴
		str.Format(_T("Client (%d)"), (int)m_ptrClientSocketList.Find(pClient)); // 클라이언트 번호(POSITION(주소) 값)
		pMain->ClientList.AddString(str); // 클라이언트가 접속할때마다 리스트에 클라이언트 이름 추가
	}
	else {
		delete pClient;
		AfxMessageBox(_T("접속이 허용 되지 않았습니다."));
	}
	
	CAsyncSocket::OnAccept(nErrorCode);
}


void ServerSocket::CloseClientSocket(CSocket* pClient)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	if (pos != NULL) {
		if (pClient != NULL) {
			pClient->ShutDown();
			pClient->Close();
		}

		CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
		CString str1, str2;
		UINT indx = 0, posNum;
		pMain->ClientList.SetCurSel(0);

		// 접속 종료되는 클라이언트 찾기
		while (indx < pMain->ClientList.GetCount()) {
			posNum = (int)m_ptrClientSocketList.Find(pClient);
			pMain->ClientList.GetText(indx, str1);
			str2.Format(_T("%d"), posNum);
			// 소켓리스트, 클라이언트리스트를 비교해서 같은 클라이언트 번호(POSITION 값) 있으면 리스트에서 삭제
			if (str1.Find(str2) != -1) {  //리스트에서 연결종료된 client와 고유 번호가 같은 항목을 찾아
				AfxMessageBox(_T("클라이언트("+str1+")이 퇴장하셨습니다."));
				pMain->ClientList.DeleteString(indx);  //Client 리스트에서 삭제
				break;
			}
			indx++;
		}
		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}





void ServerSocket::SendDataAll(char buf[256])
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	ClientSocket* pClient = NULL;
	
	while (pos != NULL) {
		pClient = (ClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(buf, strlen(buf));
	}
}

