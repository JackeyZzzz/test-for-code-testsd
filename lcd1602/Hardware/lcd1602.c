#include  "LCD1602.h"
#include "delay.h"


uint8_t i;
uint8_t CGCODE[]={
   0x10,0x18,0x1C,0x1E,0x1E,0x1C,0x18,0x10,//">"代码  0x00
   };
/******************************************************************************
 * 函数名称:void GPIO_Configuration()				      		*
 * 函数功能:LCD1602引脚初始化						 					      		*
 * 输入参数:无									      			*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
/*******************根据自己的硬件引脚做修改*****************************************/
void GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//选择工作频率
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;//设置工作模式
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 						
	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;//设置工作模式
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//选择工作频率
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}
/******************************************************************************
 * 函数名称:void LCD1602_Init()				      		*
 * 函数功能:LCD1602初始化						 					      		*
 * 输入参数:无									      			*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Init()
{
	GPIO_Configuration();			//初始化引脚

	LCD1602_Write_Cmd( 0x38 );      //显示模式设置
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x0c );      //显示开及光标设置
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x06 );      //显示光标移动位置
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x01 );      //显示清屏
	Delay_ms( 5 );	

	LCD1602_Write_Cmd(0x40);	
	for(i=0;i<8;i++)//循环56次写入
	{
		LCD1602_Write_Dat(CGCODE[i]);   
	}
}
/******************************************************************************
 * 函数名称:void LCD1602_Write_Cmd(uint8_t cmd)				      		*
 * 函数功能:写命令函数							 					      		*
 * 输入参数:	cmd 命令										      			*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Write_Cmd( uint8_t cmd )
{
	LCD_RS_Clr();
	LCD_RW_Clr();
	LCD_EN_Set();

	GPIO_Write( GPIOA, (GPIO_ReadOutputData( GPIOA ) & 0xff00) | cmd );//对电平的读取

	DATAOUT( cmd );
	Delay_ms( 5 );
	LCD_EN_Clr();
}

/******************************************************************************
 * 函数名称:void LCD1602_Write_Dat(uint8_t date)				      		*
 * 函数功能:写数据函数							 					      		*
 * 输入参数:	date 数据										      			*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Write_Dat( uint8_t data )
{
	LCD_RS_Set();
	LCD_RW_Clr();
	LCD_EN_Set();

	GPIO_Write( GPIOA, (GPIO_ReadOutputData( GPIOA ) & 0xff00) | data );//对电平的读取

	Delay_ms( 5 );
	LCD_EN_Clr();
}

/******************************************************************************
 * 函数名称:void LCD1602_ClearScreen()				      		*
 * 函数功能:1602清屏函数							 					      		*
 * 输入参数:无										      			*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_ClearScreen()
{
	LCD1602_Write_Cmd( 0x01 );
}

/******************************************************************************
 * 函数名称:void LCD1602_Set_Cursor(uint8_t x, uint8_t y)				      		*
 * 函数功能:设置1602位置函数							 					      *
 * 输入参数:x 横坐标 y 纵坐标									      				*
 * 返回值  :无														          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Set_Cursor( uint8_t x, uint8_t y )
{
	uint8_t addr;

	if ( y == 0 )
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_Cmd( addr | 0x80 );
}

uint32_t LCD1602_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//结果默认为1
	while (Y --)			//累乘Y次
	{
		Result *= X;		//每次把X累乘到结果上
	}
	return Result;
}



void LCD1602_Show_Code(uint8_t x, uint8_t y, char index )
{
	LCD1602_Set_Cursor( x, y );
    
	LCD1602_Write_Dat(index);
}


/******************************************************************************
 * 函数名称:void LCD1602_Show_Str( uint8_t x, uint8_t y, uint8_t *str )				      		*
 * 函数功能:指定位置显示字符串函数							 					      *
 * 输入参数:x 横坐标 y 纵坐标		*str 字符串							      *
 * 返回值  :	无													          *
 * 其他说明:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Show_Str( uint8_t x, uint8_t y, char *str )
{
	LCD1602_Set_Cursor( x, y );
	while ( *str != '\0' )
	{
		LCD1602_Write_Dat( *str++ );
	}
}

void LCD1602_Show_Num( uint8_t x, uint8_t y, uint8_t Num ,unsigned char Length)
{
	uint8_t i;
	LCD1602_Set_Cursor(x,y);//设置数据地址指针
	for (i = 0; i < Length; i++)		//遍历数字的每一位							
	{
		/*调用OLED_ShowChar函数，依次显示每个数字*/
		/*Number / OLED_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
		/*+ '0' 可将数字转换为字符格式*/
		//OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
		LCD1602_Write_Dat(Num / LCD1602_Pow(10,Length - i - 1) % 10 + '0');
	}
}