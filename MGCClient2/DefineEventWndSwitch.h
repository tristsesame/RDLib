#pragma once

//定义窗口类型
enum enum_wnd_type
{
	enum_wnd_type_start_up = 0, //视频展示页
	enum_wnd_type_game_list, //视频游戏列表
	enum_wnd_type_game_fullscreen_play, //游戏视频播放
	enum_wnd_type_game_stop, //游戏确认结束
	enum_wnd_type_net_error_before_start, //断网报错(体验前)
	enum_wnd_type_op_login,	//运维登录
	enum_wnd_type_pay, //扫码付款
	enum_wnd_type_net_error_while_playing //断网提示(体验中)
};

