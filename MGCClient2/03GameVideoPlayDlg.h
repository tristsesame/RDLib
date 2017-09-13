#pragma once

#include "vlc/vlc.h"
#include "vlc/libvlc.h"

class C03GameVideoPlayDlg : public CDialogBase
{
public:
	C03GameVideoPlayDlg(void);
	virtual ~C03GameVideoPlayDlg(void);

	RDLIB_DEFAULT_METHOD( L"03GameVideoPlayDlg.xml", UI_CLASSSTYLE_FRAME, L"03GameVideoPlay_windowclass" )

	LRESULT OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	void	Init();
	//游戏标题，标签(以,分隔), 是否登录
	void SetData(LPCTSTR strTitle, LPCTSTR strTags, LPCTSTR strMediaFile, BOOL isLogin);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_pWnd;
	HWND m_pWnd2;
	CWndUI *m_pWndVideo;
	CLabelUI *m_pLabelTitle;
	CLabelUI *m_pLabelTags;
	CProgressUI *m_pProgress;
	BOOL m_bIsLogin;

	std::wstring m_strTitle;
	std::wstring m_strTags;
	std::wstring m_strMediaFile;

	std::string wstringToString(const std::wstring& wstr);

	//vlc
	libvlc_instance_t*		libvlc_inst;
	libvlc_media_player_t*	libvlc_mp;
	//libvlc_media_t*			libvlc_m;

	//pfnCallback           m_pfnPlaying;				//文件读取完毕，准备播放
	//pfnCallback           m_pfnPosChanged;			//文件位置改变时的回调函数
	//pfnCallback           m_pfnEndReached;			//文件播放完毕的回调函数

	static	C03GameVideoPlayDlg*	s_instance;
	static void		OnVLC_Event(const libvlc_event_t *event, void *data);

	void	vlcReleasePlayer();
	void	Play();
};

