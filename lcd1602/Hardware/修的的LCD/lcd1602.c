#include"lcd1602.h"
void LCD1602_GPIO_Init_Out()//LCD1602端口初始化,配置为输出
{
	 GPIO_InitTypeDef GPIO_InitStructrue;
	 RCC_APB2PeriphClockCmd(LCD1602_Timer_GPIOA | LCD1602_Timer_GPIOB, ENABLE);//使能端口时钟
	 GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
	 GPIO_InitStructrue.GPIO_Pin = LCD1602_IO; 
	 GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_10MHz;//低速输出
	 GPIO_Init(LCD1602_GPIOA, &GPIO_InitStructrue);//初始化
	
	 GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
	 GPIO_InitStructrue.GPIO_Pin = LCD1602_RW |  LCD1602_E |  LCD1602_RS; 
	 GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_10MHz;// 低速输出
	 GPIO_Init(LCD1602_GPIOB, &GPIO_InitStructrue);//初始化
}

void LCD1602_GPIO_Init_Inupt()//LCD1602端口初始化,配置为输入
{
	 GPIO_InitTypeDef GPIO_InitStructrue;
	 RCC_APB2PeriphClockCmd(LCD1602_Timer_GPIOA, ENABLE);//使能端口时钟
	 
	
	 GPIO_InitStructrue.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//浮空输入
	 GPIO_InitStructrue.GPIO_Pin =  GPIO_Pin_7; 
	 GPIO_Init(LCD1602_GPIOA, &GPIO_InitStructrue);//初始化
}


void LCD1602_WaitReady(void)//用于LCD忙检测
{
	u8 sta = 0;
	LCD1602_GPIO_Init_Out();//LCD1602端口初始化,配置为输出
	GPIOA->ODR =0x00ff;
	LCD1602_RS_RESET();
	LCD1602_RW_SET();//读状态
	LCD1602_GPIO_Init_Inupt();//LCD1602端口初始化,配置为输入
	do{
		LCD1602_E_SET();
		sta = GPIO_ReadInputDataBit(LCD1602_GPIOA, GPIO_Pin_7);
		LCD1602_E_RESET();
		}
		while(sta);
		LCD1602_GPIO_Init_Out();//LCD1602端口初始化,配置为输出
}

void LCD1602_WriteCmd(u16 cmd)//用于写指令
{
	LCD1602_WaitReady();//等待液晶准备好
	LCD1602_RS_RESET();
	LCD1602_RW_RESET();//写指令
	GPIOB->ODR &= cmd;
	LCD1602_E_SET();
	LCD1602_E_RESET();//高脉冲

}

void LCD1602_WriteDate(u16 date)//用于写数据
{
	LCD1602_WaitReady();//等待液晶准备好
	LCD1602_RS_SET();
	LCD1602_RW_RESET();//写数据
	GPIOB->ODR &=date;
	LCD1602_E_SET();
	LCD1602_E_RESET();//高脉冲
}

void LCD1620_SetAddress(unsigned char x,unsigned char y)
{
	if(y == 0)
	LCD1602_WriteCmd(0x80 | x);//从第一行开始显示
	else 
	LCD1602_WriteCmd(0x80 | 0x40 | x);//从第二行开始显示
}

void LCD1602_ShowStr(unsigned char x,unsigned char y,unsigned char *str)//LCD1602显示字符串
{
	LCD1620_SetAddress(x,y);//设置数据地址指针
	while(*str != '\0')
	LCD1602_WriteDate(*str++);//写数据	
}

void LCD1602_ShowChar(unsigned char x,unsigned char y,unsigned char date)//LCD1602显示字符
{
	LCD1620_SetAddress(x,y);//设置数据地址指针
	LCD1602_WriteDate(date);//写数据	
}
               
void LCD1602_ShowNum(unsigned char x,unsigned char y,unsigned char *str,unsigned char i)//LCD1602显示数字
{
	// LCD1620_SetAddress(x,y);//设置数据地址指针
	// str = str+ i;
	// LCD1602_WriteDate(*str);//写数据
	// 	for (i = 0; i < Length; i++)		//遍历数字的每一位							
	// {
	// 	/*调用OLED_ShowChar函数，依次显示每个数字*/
	// 	/*Number / OLED_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
	// 	/*+ '0' 可将数字转换为字符格式*/
	// 	OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	// }
	LCD1620_SetAddress(x,y);//设置数据地址指针
	LCD1602_WriteDate(str + '0');

}

 void LCD1602_Init(void)//液晶初始化函数
{
	LCD1602_GPIO_Init_Out();
	LCD1602_WriteCmd(0x38);//设置16*2显示，5*7点阵，8位数据接口
	LCD1602_WriteCmd(0x0c);//开显示,显示光标，光标不闪烁
	LCD1602_WriteCmd(0x06);//光标加1，屏幕显示不移动
	LCD1602_WriteCmd(0x01);//清屏
}