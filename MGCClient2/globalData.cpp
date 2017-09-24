#include "StdAfx.h"
#include "globalData.h"

GlobalData* GlobalData::_instance;
GlobalData::GlobalData()
{
	m_bUserLogin = false;
}

GlobalData::~GlobalData()
{
}

GlobalData * GlobalData::Instance()
{
	if( 0 == _instance)
	{
		_instance = new GlobalData();
	}
	return _instance;
};

void GlobalData::setLoginStatus(bool bIsLogin)
{
	m_bUserLogin = bIsLogin;
}
	//ÊÇ·ñµÇÂ¼
bool  GlobalData::bIsLogin()
{
	return m_bUserLogin;
}
