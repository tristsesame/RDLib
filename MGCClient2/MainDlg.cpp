#include "StdAfx.h"
#include "MainDlg.h"

//#include "VlcWindow.h"
//#include "WindowTip.h"
//
//#include "InfoWindow.h"
//#include "DlgConfirm.h"
//#include "ChargeWnd.h"
//#include "DlgPayment.h"


#include "SettingMgr.h"
#include "MainHelper.h"

#include "01WndScanEnter.h"
#include "02GamePadDlg.h"

#include "02FloatWnd.h"
#include "04ConfirmDlg.h"

#include "05NetErrorDlg.h"
#include "06AdminLoginDlg.h"

#include "07PayInfoDlg.h"
#include "08NetInterruptDlg.h"

#include "XTask.h"

#include "DataManager.h"

CMainDlg::CMainDlg(void)
	//: m_pDlgPayment( nullptr )
{
	m_gameDlg = nullptr;
	m_scanEnterDlg = nullptr;
	_pDlgCurrent = nullptr;
}


CMainDlg::~CMainDlg(void)
{
	PATerm();

	for( auto it = _mapDlgs.begin(); it != _mapDlgs.end(); ++it )
	{
		delete it->second;
	}

	_mapDlgs.clear();

	//ljf add
	if( m_dataManager )
	{
		delete m_dataManager;
	}
}

void CMainDlg::Init()
{
	::SetTimer( m_hWnd, 1, 1000, NULL );
	thStart();

	//ljf add 二期接口的数据模块
	//设置一些数据
	GlobalData::Instance()->setMainHwnd(this->GetHWND());

	//设置data manager
	CStringA  strWeb = (CStringA)SetMgr()->_strWeb;
	//find host and ip
	int pos = strWeb.Find(':',5);
	int len = strWeb.GetLength();

	CStringA strPort = strWeb.Right(len - pos - 1);
	CStringA strHost = strWeb.Left(pos);

	len = strHost.GetLength();
	pos = strHost.Find("http://");
	if(pos != -1 )
	{
		strHost = strHost.Right(len - pos - 7);
	}

	m_dataManager = new CDataManager(strHost.GetBuffer(0),strPort.ToInt());

	InitAllData();
	//ljf add end

	CControlUI	*pCtrl = FindCtrl(L"bn3");
	pCtrl->OnEvent += MakeDelegate(this, &CMainDlg::OnChildEvent);

	_task1.reset( new XTask );
	_task2.reset( new XTask );

	
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_SCAN_ENTER, new C01ScanEnterDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_GAME_PAD, new C02GamePadDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_CONFIRM, new C04ConfirmDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_NET_ERRON, new C05NetErrorDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_ADMIN_LOGIN, new C06AdminLoginDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_PAY_INFO, new C07PayInfoDlg ) );
	_mapDlgs.insert( make_pair( MGC_DEFINE_WIN_NET_INTERRUPT, new C08NetInterruptDlg ) );

	for( auto it = _mapDlgs.begin(); it != _mapDlgs.end(); ++it )
	{
		CDialogBase	*pDlg = it->second;
		pDlg->Create( m_hWnd, L"", WS_POPUPWINDOW, WS_EX_WINDOWEDGE );
		pDlg->ShowWindow( false );

		if( it->first == MGC_DEFINE_WIN_GAME_PAD )
		{
			m_gameDlg = pDlg;
		}
		if( it->first == MGC_DEFINE_WIN_SCAN_ENTER )
		{
			m_scanEnterDlg = pDlg;
		}	
	}

	m_nCurrentPage = MGC_DEFINE_WIN_GAME_PAD;
	onDlgShow(MGC_DEFINE_WIN_GAME_PAD);
}

bool CMainDlg::OnChildEvent( void* paramters )
{
	TEventUI* pEvent = (TEventUI*)paramters;	
	//if (pEvent->Type > UIEVENT__MOUSEBEGIN && pEvent->Type < UIEVENT__MOUSEEND)
	if( pEvent->Type == UIEVENT_MOUSEHOVER )
	{
		CControlUI	*pCtrl = FindCtrl(L"bn3");
		pCtrl->GetManager()->SendNotify( pCtrl, L"mouse_hover_on_button");
	}

	return true;
}

LRESULT CMainDlg::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	thShutdownUseEvent();

	PostQuitMessage( 0 );
	return 0;
}

CControlUI* CMainDlg::CreateControl( LPCTSTR pstrClass )
{
	return NULL;
}

void CMainDlg::Notify( TNotifyUI& msg )
{
	CStringW	strSenderName = msg.pSender->GetName();
	CStringW	strType = msg.sType;

	if( strType == L"click")
	{
		if( strSenderName == L"bn1" )
		{
			//m_nCurrentPage = 1;

			//if( C01WndScanEnter::IsShow() )
			//	C01WndScanEnter::Hide();
			//else
			//	C01WndScanEnter::Show( m_hWnd );

			//C01ScanEnterDlg	dlg;
			//dlg.DoModalNoCaption( m_hWnd );
			
			//onDlgShowModal(1);
			onDlgShow(1);
		}								   
		else if( strSenderName == L"bn2" )
		{
			//C02GamePadDlg		dlg;
			//dlg.DoModalNoCaption( m_hWnd );

			//onDlgShowModal(2);
			onDlgShow(2);
		}
		else if( strSenderName == L"bn3" )
		{
			MsgBox( L"Call sesame!");
		}
		else if( strSenderName == L"bn4" )
		{
			//C04ConfirmDlg		dlg;
			//dlg.DoModalNoCaption( m_hWnd );

			//dlg.Create( m_hWnd, L"", WS_POPUP|WS_MAXIMIZE, WS_EX_LAYERED );
			//dlg.ShowModal();

			//onDlgShowModal(4);
			onDlgShow(4);
		}
		else if( strSenderName == L"bn5" )
		{
			//C05NetErrorDlg		dlg;
			//dlg.DoModalNoCaption( m_hWnd );
			
			//onDlgShowModal(5);
			onDlgShow(5);
		}			
		else if( strSenderName == L"bn6" )
		{
			//C06AdminLoginDlg	dlg;
			//dlg.DoModalNoCaption( m_hWnd );

			//onDlgShowModal(6);
			onDlgShow(6);
		}
		else if( strSenderName == L"bn7" )
		{
			//C07PayInfoDlg		dlg;
			//dlg.DoModalNoCaption( m_hWnd );

			//onDlgShowModal(7);
			onDlgShow(7);
		}
		else if( strSenderName == L"bn8" )
		{
			//C08NetInterruptDlg dlg;
			//dlg.DoModalNoCaption( m_hWnd );
			////dlg.Create( m_hWnd, L"", WS_POPUP|WS_MAXIMIZE, WS_EX_LAYERED );
			////dlg.ShowModal();

			//onDlgShowModal(8);
			onDlgShow(8);
		}
		else if( strSenderName == L"bnTask1" )
		{
			_task1->startTask( TASKBINDFN( CMainDlg::fnTask1 ) );
		}	
		else if( strSenderName == L"bnTask2" )
		{
			_task2->startTask( TASKBINDFN( CMainDlg::fnTask2 ) );
		}
	}
	else if( L"mouse_hover_on_button" == strType )
	{
		ATLTRACE( L"hover\n" );
	}
}

LRESULT CMainDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( WM_TIMER == uMsg )
	{
		//m_nCurrentPage = 1;
		//CVlcWindow::Show( m_hWnd );

		//PAInit();

		////// 单独测试计费窗口
		////CChargeWnd::Show( m_hWnd );

		KillTimer( m_hWnd, 1 );
	}
	else if( WM_SHOW_WINDOW == uMsg )
	{
		//if( wParam == 1 && m_nCurrentPage == 2 )
		//	CVlcWindow::Show( m_hWnd );
		//else if( wParam == 2 && m_nCurrentPage == 1 )
		//	CInfoWindow::Show( m_hWnd );
		//else if( wParam == 3 )
		//{
		//	PATerm();
		//	CChargeWnd::Show( m_hWnd );
		//}
		//else if( wParam == 4 )
		//{
		//	//CDlgConfirm		dlg;
		//	//dlg.DoModalNoCaption( GetDesktopWindow() );
		//}
		//else if( wParam == 5 )
		//{
		//	//CDlgPayment		dlg;
		//	//dlg.DoModalNoCaption( GetDesktopWindow() );

		//	if( nullptr == m_pDlgPayment )
		//	{
		//		m_pDlgPayment = new CDlgPayment;
		//		m_pDlgPayment->Create( GetDesktopWindow(), L"", WS_POPUPWINDOW, WS_EX_WINDOWEDGE );
		//		m_pDlgPayment->CenterWindow();
		//	}

		//	m_pDlgPayment->ShowWindow();
		//}

		////m_nCurrentPage = wParam;
		//::InterlockedExchange( (LPLONG)&m_nCurrentPage, wParam );
	}
	else if( WM_LBUTTONDOWN == uMsg )
	{
		int x = LOWORD( wParam );
		int y = HIWORD( wParam );
	}
	else if( WM_CLOSE == uMsg )
	{
		int i = 0;
	}
	else if( WM_MCG_SCAN_EXIT == uMsg)
	{
		//扫码页退出，此时显示游戏列表页
		onDlgShow(MGC_DEFINE_WIN_GAME_PAD);

		/*
			HWND receiveWindow = ::FindWindow(NULL, L"testMiniPlayer");  
			if (receiveWindow == NULL)  
				return false; 

			const char* wc = "Hello World" ;
			COPYDATASTRUCT copyData = { 0 };
			copyData.lpData = (void*)wc;
			copyData.cbData = 11;

			::SendMessage(receiveWindow, WM_COPYDATA, (WPARAM)this->GetHWND(), (LPARAM)&copyData);
		*/
	}
	else if( WM_MCG_GAME_PAD_LOGIN == uMsg )
	{
		bool bIsLogin = lParam;
		//如果未登录,显示扫码登录页.
		//已登录，显示确认结束页
		if( bIsLogin )
		{
			onDlgShow(MGC_DEFINE_WIN_CONFIRM);
		}
		else
		{
			onDlgShow(MGC_DEFINE_WIN_SCAN_ENTER);			
		}
	}
	else if( WM_MCG_GAME_PAD_STAT_UPDATE == uMsg )
	{
		CSettingMgr		*s = SetMgr();
		//填充信息
		CStringW strLastTime, strPricePerSeconds,strPrice;
		int nDuration = _wtoi(s->_duration.GetBuffer(0));
		strLastTime.Format(L"%d小时%d分",nDuration / 60, nDuration % 60);
		strPricePerSeconds.Format(L"%s元/分钟",s->_charging);
		strPrice.Format(L"%s元",s->_cost);

		C02FloatWnd::setInfo(s->_user_nickname,s->_user_phone,strLastTime,strPricePerSeconds,strPrice);
	}
	else if( WM_MCG_CONFIRM_LOG_OUT == uMsg)
	{
		//下机确认页点击确定
		bool bOK = CMainHelper::web_offline();
		if( bOK )
		{
			//通知游戏列表页，更改相应状态
			int clientStatus = 1; //空闲中
			::PostMessageA(m_gameDlg->GetHWND(),WM_MCG_GAME_PAD_STAT_UPDATE,0,clientStatus);
			onDlgShow(MGC_DEFINE_WIN_PAY_INFO);
		}
		else
		{
			/*
			//如果当前面不是确认结束页，则不显示之。因为有可能是由微信端发起的下机操作
			//应该显示"下机失败，请重试",暂时仍显示下机确认页
			if( m_nCurrentPage == MGC_DEFINE_WIN_CONFIRM )
			{
				onDlgShow(MGC_DEFINE_WIN_CONFIRM);
			}
			*/
		}
	}
	else if( WM_MCG_CONFIRM_CANCEL == uMsg )
	{
		onDlgShow(MGC_DEFINE_WIN_GAME_PAD);
	}
	else if( WM_MCG_LOG_OUT_SUCCESS == uMsg )
	{
		onDlgShow(MGC_DEFINE_WIN_PAY_INFO);
	}
	//以下是二期的数据接口,取到消息后的响应
	else if( WM_MCG_DATA_GET_PHONE_RESULT == uMsg )
	{
		if( 1 == lParam )
		{
			m_dataManager->getPhoneData(m_dataPhoneResult);
		}
	}
	else if( WM_MCG_DATA_GET_GAME_FAMILY_RESULT == uMsg )
	{
		if( 1 == lParam )
		{
			m_dataManager->getGameFamilyResult(m_dataGameFamilyResult);
		}
	}
	else if( WM_MCG_DATA_GET_GAME_RESULT == uMsg )
	{
		if( 1 == lParam )
		{
			m_dataManager->getGameResult(m_dataGameResult);
		}
	}

	return CDialogBase::HandleMessage(uMsg, wParam, lParam);
}

void CMainDlg::thread_main()
{
	////while( 1 )
	////{
	////	///原来用于测试Idle时间
	////	//DWORD tNow = ::GetTickCount();
	////	//DWORD tLast = IdleTrackerGetLastTickCount();

	////	//CStringW	str;
	////	//str.Format( L"%d", tNow-tLast );
	////	//ShowInfo( str );

	////	//Sleep(1000);

	////}


	maps2s			m;
	maps2s_shell	ms( &m );
	CSettingMgr		*s = SetMgr();

	int			nTime = 0;
	while(1)
	{
		if( m_nCurrentPage == MGC_DEFINE_WIN_PAY_INFO )
		{
			int nRet = CMainHelper::web_orderStatus( m );
			if( nRet <= 0 || 0 == ms.intValue("data") )
			{
				mgTrace( L"获取订单状态 orderStatus fail! %d", nRet );
			}
			else
			{
				if( 1 == ms.intValue("orderStatus") )
				{
					//CMainHelper::Reboot();
					break;
				}
			}

			// 5s轮询一次
			if( WAIT_OBJECT_0 == thWaitEvent(5000) )
				break;
		}
		else
		{
			int	 clientStatus = -999; //忽略
			int nRet = CMainHelper::web_status_client( m );
			int nData = ms.intValue("data");
			if( nRet <= 0 || 0 == nData )
			{
				mgTrace( L"获取上机状态 status_client fail! %d", nRet );
			}
			else if( 2 == nData)
			{
				s->_duration = ms.stringValue( "duration" ).c_str();
				s->_charging = ms.stringValue( "charging" ).c_str();
				s->_cost = ms.stringValue( "cost" ).c_str();
				s->_user_nickname = ms.stringValue( "nickName" ).c_str();
				s->_user_phone = ms.stringValue( "phone" ).c_str();
				clientStatus = ms.intValue("clientStatus"); //1待上机 2上机中 3不可上机

				if( clientStatus == 2 )
				{   
					//记录下已登录状态
					GlobalData::Instance()->setLoginStatus(true);

					//if( m_nCurrentPage == MGC_DEFINE_WIN_GAME_PAD )
					{
						//通知mainDlg,需要更新计费信息
						PostMessage(WM_MCG_GAME_PAD_STAT_UPDATE,0,(LPARAM)clientStatus);
					}

					//如果扫码登录页仍在，则隐藏之
					if( m_scanEnterDlg && ::IsWindowVisible(m_scanEnterDlg->GetHWND( )) )
					{
						m_scanEnterDlg->ShowWindow(false);
					}

				}
				else
				{
					//记录下已登录状态
					GlobalData::Instance()->setLoginStatus(false);
				}
			}
			else
			{
				clientStatus = ms.intValue("clientStatus"); //1待上机 2上机中 3不可上机
				//设备空闲 data == 1
				s->_duration = L"0";
				s->_charging = L"0";
				s->_cost = L"0";
				s->_user_nickname = L"";
				s->_user_phone = L"";


				GlobalData::Instance()->setLoginStatus(false);
			}

			//通知游戏列表页，更改相应状态
			if( m_gameDlg )
			{
				::PostMessageA(m_gameDlg->GetHWND(),WM_MCG_GAME_PAD_STAT_UPDATE,0,clientStatus);
			}

			if( nTime >= 10 )
			{
				nTime = 0;
				// 每隔20s上报一次客户端状态
				CMainHelper::web_clientStatus();
			}

			nTime++;

			// 两秒轮询一次
			if( WAIT_OBJECT_0 == thWaitEvent(2000) )
				break;
		}
	}
}

void CMainDlg::ShowInfo( CStringW strInfo )
{
   CLabelUI	 *lb = FindCtrl<CLabelUI>( L"lb" );
   lb->SetText( strInfo );
}

void CMainDlg::fnTask1()
{
	int i = 0;
	while(1)
	{
		if( WAIT_OBJECT_0 == _task1->thWaitEvent( 5000 ) )
			break;

		//ATLTRACE( L"task1 %d\n", i++ );

		onDlgShowModal( 5 );
	}
}

void CMainDlg::fnTask2()
{
	int i = 0;
	while(1)
	{
		if( WAIT_OBJECT_0 == _task1->thWaitEvent( 3000 ) )
			break;

		ATLTRACE( L"task2 %d\n", i++ );
	}
}

void CMainDlg::onDlgShowModal( int id )
{
	auto	it = _mapDlgs.find( id );
	if( it == _mapDlgs.end() )
		return;

	CDialogBase *pDlg = it->second;

	if( _pDlgCurrent != pDlg )
	{
		if( _pDlgCurrent != nullptr )
			_pDlgCurrent->EndModal( 0 );

		_pDlgCurrent = pDlg;

		pDlg->Create( m_hWnd, L"", WS_POPUPWINDOW, WS_EX_WINDOWEDGE );
		pDlg->ShowModal();
		_pDlgCurrent = nullptr;
	}
}

void CMainDlg::onDlgShow( int id )
{
	auto	it = _mapDlgs.find( id );
	if( it == _mapDlgs.end() )
		return;

	CDialogBase *pDlg = it->second;

	if( _pDlgCurrent != pDlg || \
		_pDlgCurrent != nullptr  && \
			!::IsWindowVisible(_pDlgCurrent->GetHWND()) )
	{

		if( _pDlgCurrent != nullptr  && \
			_pDlgCurrent != m_gameDlg )
		{
			_pDlgCurrent->ShowWindow( false );
		}

		_pDlgCurrent = pDlg;
		if( _pDlgCurrent != m_gameDlg )
		{
			pDlg->ShowWindow( true ,true);
		}
		else
		{
			pDlg->ShowWindow( true);
		}

		if( id == MGC_DEFINE_WIN_PAY_INFO )
		{
			::SetWindowPos(pDlg->GetHWND(),HWND_TOPMOST,0,0,0,0,SWP_NOSIZE);
		}
		m_nCurrentPage = id; 

	}
}

void CMainDlg::InitAllData()
{
	//取电话号码
	m_dataManager->requestPhone();
	//取游戏列表
	m_dataManager->requestAllGameFamily();
	//取所有游戏
	m_dataManager->requestAllGame();
}