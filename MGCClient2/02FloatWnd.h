#pragma once
class C02FloatWnd : public CWindowWnd
{
public:
	C02FloatWnd(void);
	virtual ~C02FloatWnd(void);

	virtual LPCTSTR GetWindowClassName() const { return L"mgc2_02float_windowclass"; }
	virtual UINT	GetClassStyle() const { return CS_HREDRAW | CS_VREDRAW | CS_IME | CS_DBLCLKS; }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	static void		Show( HWND hHostWnd, const CDUIPoint &pt );
	static bool		Hide();
	static void		Release();

protected:
	HWND			CreateThis( HWND hHostWnd );

	virtual void	thread_main();

private:
	void	Update();

	CDUIPoint	_ptNow;
	HWND		_hHostWnd;

	static	C02FloatWnd*	s_instance;

	static CStringW m_strName,m_strPhone,m_strLastTime,m_strPricePerSeconds,m_strPrice;


public:
	static void getInfo( CStringW &strName, CStringW &strPhone, CStringW &strLastTime, CStringW &strPricePerSeconds, CStringW &strPrice );
	static void setInfo( CStringW &strName, CStringW &strPhone, CStringW &strLastTime, CStringW &strPricePerSeconds, CStringW &strPrice );

};

