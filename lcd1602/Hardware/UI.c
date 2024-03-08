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
#include "stm32f10x.h"
#include "sys.h"
#include "lcd1602.h"
#include "timer.h"
#include "KEY.h"
#include "Delay.h"
#include "UI.h"
#include "config.h"


uint8_t mainInf = 0;
volatile UiParam_t ui;
uint8_t taskIndex  = 0;	//初始任务

//索引表
Main_Menu table[20]=
{
   //Cur_Index,previous,next,enter,back,(*current_operation)(u8,u8)

	// 主界面
	{0,0,0,1,0,UIdisplay_sdMaster},
   
   // 菜单界面
   {1,0,0,2,0,UIdisplay_menu},

   // Anime
   {2,2,2,2,1,UIdisplay_SetSubmenus},

};

void UIdisplay_menuChoineLogo(uint8_t num)
{
   if(num % 2 == 1)
   {
      LCD1602_Show_Code(0,1,0);
      LCD1602_Show_Str(0,0," ");
   }
   else
   {
      LCD1602_Show_Code(0,0,0);
      LCD1602_Show_Str(0,1," ");
   }     
}

void UIdisplay_opening(void)
{
   LCD1602_Show_Str( 1, 1, "Network Init...");
}

void UIdisplay_sdMaster(void)
{
   uint8_t cur_pos = GetMainInfPage();

   LCD1602_Show_Str(0,0,"OFFLINE     ");
   if(cur_pos == 0)
   {
      LCD1602_Show_Str(13,0,"1/2");   
      LCD1602_Show_Str(0,1,"MOD:");
      LCD1602_Show_Num(4,1,1,2);
      LCD1602_Show_Str(9,1," SPD:");
      LCD1602_Show_Num(14,1,1,2);
      LCD1602_Show_Str(6,1,"   ");   
   }
   else if(cur_pos == 1)
   {
      LCD1602_Show_Str(13,0,"2/2");  
      LCD1602_Show_Str(0,1,"ID:");
      LCD1602_Show_Num(3,1,1,3);
      LCD1602_Show_Str(6,1,"  ");
      LCD1602_Show_Str(8,1,"Group:");
      LCD1602_Show_Num(14,1,1,2);
   }
}

void UIdisplay_menu(void)
{
   UIdisplay_menu_fix(ui.menu.item / 2 );
   UIdisplay_menuChoineLogo(ui.menu.item);
}

void UIdisplay_menu_fix( uint8_t num )
{
   LCD1602_Show_Str(14,0,"/7");    
   LCD1602_Show_Num(13,0,num + 1,1);
   switch (num)
   {
   case 0:
         LCD1602_Show_Str(1,0,"Debug Anime");
         LCD1602_Show_Str(1,1,"ID Group       ");

      break;
   case 1:
         LCD1602_Show_Str(1,0,"Artnet     ");
         LCD1602_Show_Str(1,1,"Auto ID       ");

      break;
   case 2:
         LCD1602_Show_Str(1,0,"Dmx Console");
         LCD1602_Show_Str(1,1,"SYNC Setting     ");         
      break;
   case 3:
         LCD1602_Show_Str(1,0,"Brightness ");
         LCD1602_Show_Str(1,1,"Gamma         ");          
      break;
   case 4:
         LCD1602_Show_Str(1,0,"LED Driver ");
         LCD1602_Show_Str(1,1,"LANGUAGE       ");  
      break;
   case 5:
         LCD1602_Show_Str(1,0,"Addressable");
         LCD1602_Show_Str(1,1,"Restore       ");  
      break;
   case 6:
         LCD1602_Show_Str(1,0,"Run Info    ");
         LCD1602_Show_Str(1,1,"Version        ");  
      break;
   default:
      break;
   }
}

void UIdisplay_SetSubmenus(void)
{
   uint8_t index = ui.menu.item;
   switch (index)
   {
      case 0:
         UIdisplay_TestAnimation();
         break;
       case 1:
          UIdisplay_SWSetting();     
          break;
      case 2:
         UIdisplay_ArtNetSetting();
         break;
      case 3:
         UIdisplay_AutoIDMenu();
         break;
      case 4:
         UIdisplay_DMXSetting();
         break;
      case 5:
         UIdisplay_setMSmode();
         break;
      case 6:
         UIdisplay_setBrightness();
         break;
      case 7:
         UIdisplay_setGamma();
         break;
      case 8:
         UIdisplay_setLedOutputType();
         break;
      case 9:
         UIdisplay_setLanguage();
         break;
      case 10:
         UIdisplay_addrFuncMenu();
         break;
      case 11:
         UIdisplay_RestoreSettings();
         break;
      case 12:
         UIdisplay_RunInfo();
         break;    
      case 13:
         UIdisplay_version();
         break;     
      default:
         break;
   }
}   

void UIdisplay_TestAnimation(void)
{
   uint8_t lamp = 0;
   uint8_t chn = 0;
   uint8_t bri = 0;
   uint8_t speed = 0;
   uint8_t mode = 0;

   if(ui.TestAnimation.item < 3)
   {
      LCD1602_Show_Str(0,0,"Lamp:");
      LCD1602_Show_Str(0,1," Chn:");
      LCD1602_Show_Str(8,1,"  Bri:");
      LCD1602_Show_Str(13,0,"1/2");
      LCD1602_Show_Str(7,1,"   ");
   }
   else if(ui.TestAnimation.item >= 3)
   {
      LCD1602_Show_Str(0,0,"Speed:");
      LCD1602_Show_Str(0,1," Mode:");
      LCD1602_Show_Str(13,0,"2/2");      
   }

   if(flickerFlag)
   {
      switch (ui.TestAnimation.item)
      {
         case 0:
            LCD1602_Show_Str(5,0,"TM1804 ");
            LCD1602_Show_Num(14, 1, bri, 2);
            LCD1602_Show_Num(5, 1, chn, 2);        
            break;
         case 1:
            LCD1602_Show_Str(5,0,"TM1804 ");
            LCD1602_Show_Num(14, 1, bri, 2);
            LCD1602_Show_Num(5, 1, chn, 2);        
            break;             
         case 2:
            LCD1602_Show_Str(5,0,"TM1804 ");
            LCD1602_Show_Num(14, 1, bri, 2);
            LCD1602_Show_Num(5, 1, chn, 2);        
            break;     
         case 3:
            if(speed == 0)
            {
               LCD1602_Show_Str(6,0,"fast  ");
            }
            else if(speed == 1)
            {
               LCD1602_Show_Str(6,0,"mid  ");
            }
            else if(speed == 2)
            {
               LCD1602_Show_Str(6,0,"slow  ");
            }

            if(mode == 0)
            {
               LCD1602_Show_Str(6,1,"CH1        ");
            }          
         break;   
         case 4:
            if(mode == 0)
            {
               LCD1602_Show_Str(6,1,"CH1        ");
            }

            if(speed == 0)
            {
               LCD1602_Show_Str(6,0,"fast ");
            }
            else if(speed == 1)
            {
               LCD1602_Show_Str(6,0,"mid  ");
            }
            else if(speed == 2)
            {
               LCD1602_Show_Str(6,0,"slow  ");
            }
         break;          
         default:
            break;
      }
   }
   else 
   {
      switch (ui.TestAnimation.item)
      {
         case 0:
            LCD1602_Show_Str(5,0,"       ");
            break;
         case 1:
            LCD1602_Show_Str(5,1,"  ");
            break;
         case 2:
            LCD1602_Show_Str(14, 1, "  ");
            break;
         case 3:
            if(speed == 0)
            {
               LCD1602_Show_Str(6,0,"     ");
            }
            else if(speed == 1)
            {
               LCD1602_Show_Str(6,0,"     ");
            }
            else if(speed == 2)
            {
               LCD1602_Show_Str(6,0,"      ");
            }
            break;      
         case 4:
            LCD1602_Show_Str(6,1,"        ");
            break; 
         default:
            break;      
      }
   }
}

void UIdisplay_SWSetting(void)
{
   uint8_t ID = 0;
   uint8_t Group = 0;

   LCD1602_Show_Str(0,0,"Group:         ");
   LCD1602_Show_Str(0,1,"   ID:       ");

   if(flickerFlag)
   {
      if(ui.swSetting.item == 0)
      {
         LCD1602_Show_Num(15, 0, Group, 1);
         LCD1602_Show_Num(13, 1, ID, 3);
      }
      else 
      {
         LCD1602_Show_Num(15, 0, Group, 1);
         LCD1602_Show_Num(13, 1, ID, 3);
      }
   }
   else
   {
      if(ui.swSetting.item == 0)
         LCD1602_Show_Str(15, 0, " ");
        
      else 
         LCD1602_Show_Str(13, 1, "   ");    
   }
}

void UIdisplay_ArtNetSetting(void)
{
   uint8_t ArtNetSettingPage_t = ui.ArtNetSetting.item;
   uint8_t startU = 0;
   uint8_t Qty = 0;
   uint8_t Lamp = 0;

   if(ArtNetSettingPage_t  < 2)
   {
      LCD1602_Show_Str(13,0,"1/2");
      LCD1602_Show_Str(0,0,"Start U:");
      LCD1602_Show_Str(0,1,"  U Qty:");
      LCD1602_Show_Str(0,12," ");
   }
   else if(ArtNetSettingPage_t >= 2 )
   {
      LCD1602_Show_Str(13,0,"2/2");
      LCD1602_Show_Str(0,0,"Lamp:");

      LCD1602_Show_Str(0,1,"             ");
   }

   if(flickerFlag)
   {
      if(ArtNetSettingPage_t == 0)
      {
         LCD1602_Show_Num(8, 0, startU, 4);
         LCD1602_Show_Num(8, 1, Qty, 4);
      }
      else if(ArtNetSettingPage_t == 1)
      {
         LCD1602_Show_Num(8, 0, startU, 4);
         LCD1602_Show_Num(8, 1, Qty, 4);
      }
      else if(ArtNetSettingPage_t == 2)
      {
         if(Lamp == 0)
         {
            LCD1602_Show_Str(5,0,"TM1804");
         }
      }
   }
   else
   {
      if(ArtNetSettingPage_t == 0)
      {
         LCD1602_Show_Str(8,0,"    ");
      }
      else if(ArtNetSettingPage_t == 1)
      {
         LCD1602_Show_Str(8,1,"    "); 
      }
      else if(ArtNetSettingPage_t == 2)
      {
         if(Lamp == 0)
         {
            LCD1602_Show_Str(5,0,"       ");
         }
      } 
   }   
}

void UIdisplay_AutoIDMenu(void)
{
   UIdisplay_menuChoineLogo(ui.AutoID.item);
   LCD1602_Show_Str(1,0,"Set ID         ");
   LCD1602_Show_Str(1,1,"Set ID&Group   ");
}

void UIdisplay_DMXSetting(void)
{
   uint8_t index = ui.DMXSetting.item;
   uint8_t Addr = 0;
   uint8_t Chn = 0;
   uint8_t Buf = 0;

   if(index < 2)
   {
      LCD1602_Show_Str(10,0," ");
      LCD1602_Show_Str(13,1,"   ");
      LCD1602_Show_Str(13,0,"1/2");
      LCD1602_Show_Str(0,0,"DMX Addr:");
      LCD1602_Show_Str(0,1,"DMX  Chn:");
   }
   else
   {
      LCD1602_Show_Str(13,0,"2/2");
      LCD1602_Show_Str(0,1,"DMX  Buf:");
   }


   if(flickerFlag)
   {
      if(index == 0)
      {
         LCD1602_Show_Str(11,0,"  ");
         LCD1602_Show_Num(9, 0, Addr, 1);
         if(Chn == 0)
         {
            LCD1602_Show_Str(9,1,"1to1");
         }
      }
      else if(index == 1)
      {
         LCD1602_Show_Num(9, 0, Addr, 1);
         if(Chn == 0)
         {
            LCD1602_Show_Str(9,1,"1to1");
         }
      }
      else if(index == 2)
      {
         if(Buf == 0)
         {
            LCD1602_Show_Str(0, 0,"             ");
            LCD1602_Show_Str(9,1,"Disable");
         }    
      }
   }
   else
   {
      switch (index)
      {
      case 0:
         LCD1602_Show_Str(9, 0, " ");
         break;
      case 1:
         LCD1602_Show_Str(9,1,"    ");
         break;
      case 2:
         LCD1602_Show_Str(9,1,"       ");
      default:
         break;
      }
   }
}

void UIdisplay_setMSmode(void)
{
   uint8_t mdoe = 0;
   LCD1602_Show_Str(0,0,"                ");


   if(flickerFlag)
   {
      if(mdoe == 0)
      {
         LCD1602_Show_Str(6,1,"Host");
         LCD1602_Show_Str(0,1,"      ");
         LCD1602_Show_Str(10,1,"     ");
      }
   }
   else
   {
      if(mdoe == 0)
      {
         LCD1602_Show_Str(6,1,"    ");  
      } 
   }   
}

void UIdisplay_setBrightness(void)
{
   uint8_t index = ui.setBrightness.item;
   uint8_t R  = 0;
   uint8_t G  = 0;
   uint8_t B  = 0;
   uint8_t W  = 0;
   uint8_t W2 = 0;
   uint8_t W3 = 0;
   uint8_t totalBrightness = 0;

   if(index < 4)
   {
      LCD1602_Show_Str(13,0,"1/2");
      LCD1602_Show_Str(1,0,"R:");
      LCD1602_Show_Str(6,0," ");
      LCD1602_Show_Str(7,0,"G:");
      LCD1602_Show_Str(1,1,"B:");
      LCD1602_Show_Str(6,1," ");
      LCD1602_Show_Str(7,1,"w:");   
   }
   else 
   {
      LCD1602_Show_Str(13,0,"2/2");
      LCD1602_Show_Str(0,0,"W2:");
      LCD1602_Show_Str(6,0,"W3:");
      LCD1602_Show_Str(0,1,"Total Bri:");     
   }

   if(flickerFlag)
   {
      switch (index)
      {
      case 0:
         LCD1602_Show_Num(3,0,R,3);
         LCD1602_Show_Num(9,0,G,3);
         LCD1602_Show_Num(3,1,B,3);
         if(W == 0)
         {
            LCD1602_Show_Str(9,1,"---");
         }
         break;
      case 1:
         LCD1602_Show_Num(3,0,R,3);
         LCD1602_Show_Num(9,0,G,3);
         LCD1602_Show_Num(3,1,B,3);
         if(W == 0)
         {
            LCD1602_Show_Str(9,1,"---");
         }
         break;
      case 2:
         LCD1602_Show_Num(3,0,R,3);
         LCD1602_Show_Num(9,0,G,3);
         LCD1602_Show_Num(3,1,B,3);
         if(W == 0)
         {
            LCD1602_Show_Str(9,1,"---");
         }
         break;
      case 3:
         LCD1602_Show_Num(3,0,R,3);
         LCD1602_Show_Num(9,0,G,3);
         LCD1602_Show_Num(3,1,B,3);
         if(W == 0)
         {
            LCD1602_Show_Str(9,1,"---");
         }   
         break;
      case 4:
         LCD1602_Show_Num(3,0,W,3);
         LCD1602_Show_Num(9,0,W2,3); 
         LCD1602_Show_Num(10,1,totalBrightness,3);          
         break;
      case 5:
         LCD1602_Show_Num(3,0,W,3);
         LCD1602_Show_Num(9,0,W2,3); 
         LCD1602_Show_Num(10,1,totalBrightness,3);  
         break;
      case 6:
         LCD1602_Show_Num(3,0,W,3);
         LCD1602_Show_Num(9,0,W2,3); 
         LCD1602_Show_Num(10,1,totalBrightness,3);  
         break;
      default:
         break;
      }
   }
   else
   {
     switch (index)
      {
         case 0:
            LCD1602_Show_Str(3,0,"   ");
            break;
         case 1:
            LCD1602_Show_Str(9,0,"   ");
            break;
         case 2:
            LCD1602_Show_Str(3,1,"   ");
            break;
         case 3:
            if(W == 0)
            {
               LCD1602_Show_Str(9,1,"   ");
            }   
            break;
         case 4:
            LCD1602_Show_Str(3,0,"   ");        
            break;
         case 5:
            LCD1602_Show_Str(9,0,"   "); 
            break;
         case 6:
            LCD1602_Show_Str(10,1,"   ");  
            break;
         default:
            break;    
      }  
   }     
}

void UIdisplay_setGamma(void)
{
   uint8_t highNum = 0;
   uint8_t lowNum = 0;       

   LCD1602_Show_Str(0,0,"                ");
   LCD1602_Show_Str(0,1,"       ");
   LCD1602_Show_Num(7, 1, highNum, 1);
   LCD1602_Show_Str(8,1,".");
   LCD1602_Show_Num(9, 1, lowNum, 1);
}

void UIdisplay_setLedOutputType(void)
{
   //uint8_t mode = 0;
   LCD1602_Show_Str(0,0,"                ");
   LCD1602_Show_Str(0,1,"      Auto      "); 
}

void UIdisplay_setLanguage(void)
{
   LCD1602_Show_Str(0,0,"                ");
   LCD1602_Show_Str(0,1,"    English      "); 
}

void UIdisplay_addrFuncMenu(void)
{
   uint8_t index = ui.addrMenu.item;
   UIdisplay_menuChoineLogo(index);

   LCD1602_Show_Str(1,0,"One Key Addr   ");
   LCD1602_Show_Str(1,1,"Addr Check     ");   
}

void UIdisplay_RestoreSettings(void)
{
   LCD1602_Show_Str(0,0,"Restore?        ");
   LCD1602_Show_Str(0,1,"(Long press EN) ");     
}

void UIdisplay_RunInfo(void)
{
   uint8_t index = ui.RunInfo.pageNum;
   LCD1602_Show_Str(13,0,"/12");
   LCD1602_Show_Num(11,0,index + 1,2);
   switch (index)
   {
   case 0:    
      LCD1602_Show_Str(0,0,"SD Param   ");
      LCD1602_Show_Str(0,1,"SDBI:");
      break;
   case 1:
      LCD1602_Show_Str(0,0,"PCBType");
      LCD1602_Show_Str(0,1,"Page/Frame");      
      break;
   default:
      break;
   }

}

void UIdisplay_version(void)
{
   uint8_t index = ui.Version.Flag;
   LCD1602_Show_Str(14,0,"/2");
   LCD1602_Show_Num(13,0,index + 1,1);  
   switch (index)
   {
   case 0:    
      LCD1602_Show_Str(0,0,"   AN-380  ");
      LCD1602_Show_Str(0,1,"  L380-IO2");
      break;
   case 1:
      LCD1602_Show_Str(0,0,"  L380-NO5");
      LCD1602_Show_Str(0,1,"               ");
      break;
   default:
      break;
   }
}

// void UIdisplay_PageFlicker(uint8_t num)
// {
//    if(num)
//    {

//    }
// }

void GuiRefresh(void)
{
   table[taskIndex].current_operation();
}

void SetMainInfPage(uint8_t val)
{
	mainInf = val;
}

uint8_t GetMainInfPage(void)
{
   return mainInf;
}