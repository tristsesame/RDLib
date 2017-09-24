#pragma once

#include <Windows.h>

#define WM_MCG_SCAN_EXIT (WM_APP+2000)
//�����¼
#define WM_MCG_GAME_PAD_LOGIN (WM_APP+2100)
//�Ѿ���¼
#define WM_MCG_GAME_PAD_LOGIN_SUCESS (WM_APP+2101)
//δ��¼
#define WM_MCG_GAME_PAD_LOGIN_OUT_SUCESS (WM_APP+2102)
//��¼״̬
#define WM_MCG_GAME_PAD_STAT_UPDATE (WM_APP+2200) 

//ȷ��ҳ���ȷ��,�»�����
#define WM_MCG_CONFIRM_LOG_OUT (WM_APP + 2300)
//ȷ��ҳ��ȡ��
#define WM_MCG_CONFIRM_CANCEL (WM_APP + 2310)

//ȷ���»��ɹ�,��ʾ����ҳ��
#define WM_MCG_LOG_OUT_SUCCESS (WM_APP+2320)


//http ȡ���� ��Ϣ 
//��Զ��ڽӿ�
#define WM_MCG_DATA_GET_PHONE_RESULT (WM_APP+2400)
#define WM_MCG_DATA_GET_GAME_FAMILY_RESULT (WM_APP+2401)
#define WM_MCG_DATA_GET_GAME_RESULT (WM_APP+2402)

#define MGC_DEFINE_WIN_SCAN_ENTER (1)
#define MGC_DEFINE_WIN_GAME_PAD (2)
#define MGC_DEFINE_WIN_CONFIRM (4)
#define MGC_DEFINE_WIN_NET_ERRON (5)
#define MGC_DEFINE_WIN_ADMIN_LOGIN (6)
#define MGC_DEFINE_WIN_PAY_INFO (7)
#define MGC_DEFINE_WIN_NET_INTERRUPT (8)


#define MGC_DEFINE_WIN_FLOAT (20)


/*
enum mgc_enum_win_type
{
	e_wnd_scan_enter = 1,
	e_wnd_float,
	e_wnd_game_pad,
	e_wnd_confirm,
	e_wnd_admin_login,
	e_wnd_pay_info,
	e_wnd_net_interrupt,
	e_wnd_net_error
};

enum mgc_enum_win_event_type
{
	e_wnd_hide = 0,
	e_wnd_exit,
	e_wnd_show
};
*/

class GlobalData 
{
public:
	GlobalData(void);
	~GlobalData(void);

	static GlobalData * Instance();
	void setMainHwnd(HWND hwnd) {m_mainHwnd = hwnd;};
	HWND getMainHwnd() {return m_mainHwnd;};

	void setLoginStatus(bool bIsLogin);
	//�Ƿ��¼
	bool bIsLogin();

protected:
	static GlobalData* _instance;

private:
	HWND m_mainHwnd;
	int m_nCurrentPage;

	bool m_bUserLogin;

};