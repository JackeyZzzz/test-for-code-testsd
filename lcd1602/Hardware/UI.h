/**
 * @file main.c
 * @author JackeyZ
 * @brief STM32F103C8T6 Template projects
 * @version 0.1
 * @date 2023-1-21
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#ifndef __ui_H
#define __ui_H
#include "stm32f10x.h"

typedef struct
{
	u8 Cur_Index;//当前索引项
	u8 previous;//上一页
	u8 next;//下一页
	u8 enter;//确认
	u8 back;//返回
	void (*current_operation)(void);//	当前索引执行的函数(界面)
}Main_Menu;

extern uint8_t taskIndex;	//任务调度序号
extern Main_Menu table[];


//各界面的索引值
typedef enum 
{
    uiNum_default = (u8)0, //空屏
    uiNum_opening, //开机界面
    uiNum_boxCode, //显示盒编号
	
	uiNum_onlinePlay, //联机播放
	uiNum_sdSlave, //脱机从机
    uiNum_sdMaster, //脱机主机
	uiNum_noSD, //脱机无卡

	uiNum_E0x, //出错代码

	uiNum_Lock, 	//锁定
	uiNum_LockExe, //加解密操作
	 
	/* 菜单-子菜单 */
	uiNum_menu, //菜单
	uiNum_TestAnimation, //测试效果
	uiNum_SWSetting, //IP/ID/分组
	uiNum_ArtNetSetting, //ArtNet设置
	uiNum_AutoIDMenu, //自动ID功能菜单
	uiNum_DMXSetting, //DMX设置
    uiNum_setMSmode, //主从设置
	uiNum_setBrightness, //亮度设置
	uiNum_setGamma, //Gamma设置
	uiNum_setLedOutputType, //设置LED驱动输出类型(TTL/RS485/自动)
    uiNum_setLanguage, //语言设置
	uiNum_addrFuncMenu, //编址功能
	//uiNum_setBaud, //波特率设置
	uiNum_RestoreSettings, //恢复出厂设置
	uiNum_RunInfo, //运行统计
    uiNum_version, //关于版本
	uiNum_menuMAX, //最大菜单数
	/****************/

	uiNum_IPSetting, //IP设置
	uiNum_AutoID, //自动ID

	uiNum_choiceIcType, //选择带灯芯片
	uiNum_AutoID_doing, //自动ID等待中/完成/出错
	
	uiNum_setMedium, //更改介质
	uiNum_copyBinFile, //拷贝文件
	
	/* 编址相关 */
    uiNum_OneKeyAddr, 	//一键编址
    uiNum_AddrCheck, 	//编址校验
	uiNum_NorAddrICMenu,	    //常规编址菜单
	uiNum_setEffectAfterAddrFlag, 	//编址确认
	
    //uiNum_SetNorAddrInc, //编址增量设置
	//uiNum_SetNorAddrStartAddr, //编址起始地址设置
	uiNum_AddrSetting,		//编址设置中
	uiNum_Addressing,		//编址中
	uiNum_AddrSelfChMenu, 	//自通道功能选择页面
	//uiNum_SetAddrSelfChNum, //设置自通道数
	uiNum_AddrSelfChNumWarn, //写自通道数警告页面
	//uiNum_AddrSelfChannelWriting,
	uiNum_AddrFinish,
	uiNum_AddrCheckSetInc,		//校验设置增量
	/****************/

	uiNum_FTP, 	//文件传输

	uiNum_SaveReply, //EN参数保存反馈

	uiNum_OnlinePlayWarning, //警告页面(联机播放下, 部分功能不允许使用)

	// uiNum_update, //升级界面
	// uiNum_wUID, //写UID操作界面
	// uiNum_updating, //正在升级
	// uiNum_updateConfirm, //升级确认
	
    uiNum_MAX, //最大uiNum

	uiNum_Null = 255, //空
}uiNum_e;

typedef struct
{
    uiNum_e uiNum; //@typdef uiNum_e
	//uiLanguage_e language; //@uiLanguage_e
	u8 clearFlag;
	u32 PressTmr;

	struct{
		u8 speed;
		u8 playMode;
		u8 modeNum;
	}sdMaster;

	struct{
		//uiLanguage_e tmpLanguage;
		u8 shineFlag;
	}setLanguage;

	struct{
		u16 id;
		u8 group;
		u8 item;
	}swSetting;

	struct{
		u8 StartU;
		u8 UQty;
		u16 icTypeIndex;
		u8 ChnQty;
		u8 item;
		u8 srcIP[4];
		u8 ipModifyFlag;
		u8 ipItem;
	}ArtNetSetting;

	struct{
		//u8 Qty;
		uiNum_e returnUiNum;//@typdef uiNum_e
		void (*SetIcTypeIndex)(u8);
		u8 item;
		u8 saveFlag;
	}choiceIcType;

	struct{
		u8 menuItem;
		u16 startID;
		u8 item;
	}AutoID;

	struct{
		u8 item;
	}addrMenu;

	struct{
		u8 item;
		u8 mode;
		u8 ChannelQty;
		u16 ICIndex;
	}AddrCheck;

	struct{
		u8 mode;
		u8 shineFlag;
	}setMSmode;

	struct{
		//u8 brightness[7];
		u8 brightnessQty;
		u8 item;
	}setBrightness;

	struct{
		u16 icType;
		u8 ChnQty;
		u8 speed;
		u8 mode;
		u8 modeQty;
		u8 ICIndex;
		u8 item;
	}TestAnimation;

	struct{
		u8 gamma;
		u8 shineFlag;
	}setGamma;

	struct{
		u8 ledOutputType;
		u8 shineFlag;
	}setLedOutputType;

	struct{
		uiNum_e returnUiNum;//@typdef uiNum_e
		u8 sta;
	}AutoIDdoing;
	
	struct{			
		u8 item;//@define FUNC_MENU_MAX
		u16 Addr;
		u8 ChnTypeIndex;
		//CONSOLE_TYPE_e ConsoleType;
	}DMXSetting;
	
	struct{			
		u8 item;//@define FUNC_MENU_MAX
	}menu;

	struct{
		uiNum_e returnUiNum;//@typdef uiNum_e
		int saveResult;
		volatile u32 atuoReturnTmr;
	}SaveReply;

	struct{
		uiNum_e returnUiNum;//@typdef uiNum_e
		volatile u32 atuoReturnTmr;
	}OnlinePlayWarning;

	struct{			
		u8 pageNum;
		u32 EnPressCnt;
	}RunInfo;

	struct{			
		u8 EnPressCnt;
	}Lock;

	struct{			
		volatile u32 atuoReturnTmr;
	}LockExe;

	struct{			
		volatile u32 EnPressCnt;
		u8 Flag;
	}Version;
}UiParam_t;

extern volatile UiParam_t ui;

//按键索引值
enum
{
	KEY_PREVIOUS=2,
	KEY_ENTER,
	KEY_NEXT,
	KEY_BACK
};

void UIdisplay_menu(void);
void UIdisplay_menuChoineLogo(uint8_t num);
void UIdisplay_sdMaster(void);
void UIdisplay_menu_fix( uint8_t num );
void GuiRefresh(void);
void UIdisplay_TestAnimation(void);
void UIdisplay_SetSubmenus(void);
void UIdisplay_SWSetting(void);
void UIdisplay_ArtNetSetting(void);
void UIdisplay_AutoIDMenu(void);
void UIdisplay_DMXSetting(void);
void UIdisplay_setMSmode(void);
void UIdisplay_setBrightness(void);
void UIdisplay_setGamma(void);
void UIdisplay_setLedOutputType(void);
void UIdisplay_setLanguage(void);
void UIdisplay_addrFuncMenu(void);
void UIdisplay_RestoreSettings(void);
void UIdisplay_RunInfo(void);
void UIdisplay_version(void);

void SetMainInfPage(uint8_t val);
uint8_t GetMainInfPage(void);


#endif
