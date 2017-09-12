#include "StdAfx.h"
#include "03GameVideoPlayDlg.h"

// libvlc.lib;libvlccore.lib;
#pragma comment( lib, "libvlc.lib" )
#pragma comment( lib, "libvlccore.lib" )

C03GameVideoPlayDlg*	C03GameVideoPlayDlg::s_instance = nullptr;

C03GameVideoPlayDlg::C03GameVideoPlayDlg(void)
{
	m_pLabelTitle = NULL;
	m_pLabelTags = NULL;
	m_pProgress = NULL;
	m_bIsLogin = false;
	m_pWndVideo = NULL;

	libvlc_inst = libvlc_new (0, NULL);
	libvlc_mp = nullptr;

	s_instance = this;
}


C03GameVideoPlayDlg::~C03GameVideoPlayDlg(void)
{
	libvlc_release (libvlc_inst);
	vlcReleasePlayer();
	//don't need delete controls
	/*
	if(m_pLabelTitle)
		delete m_pLabelTitle;

	if(m_pLabelTags)
		delete m_pLabelTags;

	if(m_pProgress)
		delete m_pProgress;
		*/
}

CControlUI* C03GameVideoPlayDlg::CreateControl( LPCTSTR pstrClass )
{
	return NULL;
}

LRESULT C03GameVideoPlayDlg::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	EndModal(1);
	return 0;
}

void C03GameVideoPlayDlg::Init()
{
	m_pLabelTitle = FindCtrl<CLabelUI>(_T ("labelTitle"));
    m_pLabelTags = FindCtrl<CLabelUI>(_T ("labelTags"));
	m_pProgress = FindCtrl<CProgressUI> (_T("ProgressBar"));

	if( m_pLabelTitle)
	{
		m_pLabelTitle->SetText(m_strTitle.c_str());
	}

	if( m_pLabelTags)
	{
		m_pLabelTags->SetText(m_strTags.c_str());
	}

	Play();
}


void C03GameVideoPlayDlg::SetData(LPCTSTR strTitle, LPCTSTR strTags,  LPCTSTR strMediaFile,BOOL isLogin)
{
	m_bIsLogin = isLogin;

	m_strTitle = (LPCTSTR)strTitle;
	m_strTags = (LPCTSTR)strTags;
	m_strMediaFile = (LPCTSTR)strMediaFile;
}

void C03GameVideoPlayDlg::Play()
{
	vlcReleasePlayer();

	// Create a new item
	//m = libvlc_media_new_location (libvlc_inst, "http://mycool.movie.com/test.mov");

	std::string strPath = wstringToString(m_strMediaFile);
	libvlc_media_t* libvlc_m = libvlc_media_new_path (libvlc_inst, strPath.c_str() );

	if( libvlc_m )
	{
		vlcReleasePlayer();

		// Create a media player playing environement
		libvlc_mp = libvlc_media_player_new_from_media (libvlc_m);

		//on windows
		libvlc_media_player_set_hwnd (libvlc_mp, m_hWnd );

		// play the media_player
		int x=libvlc_media_player_play (libvlc_mp);


		libvlc_event_manager_t *vlc_evt_man = libvlc_media_player_event_manager( libvlc_mp );
		libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEndReached, OnVLC_Event, s_instance );

		// No need to keep the media now
		libvlc_media_release (libvlc_m);
	}
	return;
}

void C03GameVideoPlayDlg::Notify( TNotifyUI& msg )
{
	CStringW	strSenderName = msg.pSender->GetName();
	CStringW	strType = msg.sType;

	if( strType == L"click")
	{

	}
}

LRESULT C03GameVideoPlayDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
		switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		{
		}
		break;
	case WM_LBUTTONUP:
		{
		}
		break;
	case WM_MOUSEMOVE:
		{
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
		}
		break;

	case WM_MOUSEHOVER:
		{

		}
		break;

	case WM_MOUSELEAVE:
		{

		}
		break;

	case WM_CREATE:
		{
		}
		break;

	case WM_PAINT:
		{
		}
		break;
	case WM_APP+100:
		{
			PostQuitMessage(0);
		}
		break;
	case WM_SHOWWINDOW:
		{

		}
		break;
	case WM_CLOSE:
		{
			//CMainHelper::ShowTrayWndAndStartWnd( true );
			PostQuitMessage(0);
		}
		break;
	}

	return CDialogBase::HandleMessage(uMsg, wParam, lParam);
}

std::string C03GameVideoPlayDlg::wstringToString(const std::wstring& wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0) 
	return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst) 
	return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;

	return str;
}

void C03GameVideoPlayDlg::OnVLC_Event( const libvlc_event_t *event, void *data )
{
	C03GameVideoPlayDlg *pThis = (C03GameVideoPlayDlg *)data;
	pThis->PostMessage( WM_APP+100 );
}

void C03GameVideoPlayDlg::vlcReleasePlayer()
{
	if( libvlc_mp )
	{
		libvlc_media_player_stop( libvlc_mp );
		libvlc_media_player_release( libvlc_mp );
		libvlc_mp = nullptr;
	}
}
