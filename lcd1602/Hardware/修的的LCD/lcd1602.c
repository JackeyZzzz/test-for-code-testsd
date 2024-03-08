#include"lcd1602.h"
void LCD1602_GPIO_Init_Out()//LCD1602�˿ڳ�ʼ��,����Ϊ���
{
	 GPIO_InitTypeDef GPIO_InitStructrue;
	 RCC_APB2PeriphClockCmd(LCD1602_Timer_GPIOA | LCD1602_Timer_GPIOB, ENABLE);//ʹ�ܶ˿�ʱ��
	 GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;//��©���
	 GPIO_InitStructrue.GPIO_Pin = LCD1602_IO; 
	 GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_10MHz;//�������
	 GPIO_Init(LCD1602_GPIOA, &GPIO_InitStructrue);//��ʼ��
	
	 GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;//��©���
	 GPIO_InitStructrue.GPIO_Pin = LCD1602_RW |  LCD1602_E |  LCD1602_RS; 
	 GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_10MHz;// �������
	 GPIO_Init(LCD1602_GPIOB, &GPIO_InitStructrue);//��ʼ��
}

void LCD1602_GPIO_Init_Inupt()//LCD1602�˿ڳ�ʼ��,����Ϊ����
{
	 GPIO_InitTypeDef GPIO_InitStructrue;
	 RCC_APB2PeriphClockCmd(LCD1602_Timer_GPIOA, ENABLE);//ʹ�ܶ˿�ʱ��
	 
	
	 GPIO_InitStructrue.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//��������
	 GPIO_InitStructrue.GPIO_Pin =  GPIO_Pin_7; 
	 GPIO_Init(LCD1602_GPIOA, &GPIO_InitStructrue);//��ʼ��
}


void LCD1602_WaitReady(void)//����LCDæ���
{
	u8 sta = 0;
	LCD1602_GPIO_Init_Out();//LCD1602�˿ڳ�ʼ��,����Ϊ���
	GPIOA->ODR =0x00ff;
	LCD1602_RS_RESET();
	LCD1602_RW_SET();//��״̬
	LCD1602_GPIO_Init_Inupt();//LCD1602�˿ڳ�ʼ��,����Ϊ����
	do{
		LCD1602_E_SET();
		sta = GPIO_ReadInputDataBit(LCD1602_GPIOA, GPIO_Pin_7);
		LCD1602_E_RESET();
		}
		while(sta);
		LCD1602_GPIO_Init_Out();//LCD1602�˿ڳ�ʼ��,����Ϊ���
}

void LCD1602_WriteCmd(u16 cmd)//����дָ��
{
	LCD1602_WaitReady();//�ȴ�Һ��׼����
	LCD1602_RS_RESET();
	LCD1602_RW_RESET();//дָ��
	GPIOB->ODR &= cmd;
	LCD1602_E_SET();
	LCD1602_E_RESET();//������

}

void LCD1602_WriteDate(u16 date)//����д����
{
	LCD1602_WaitReady();//�ȴ�Һ��׼����
	LCD1602_RS_SET();
	LCD1602_RW_RESET();//д����
	GPIOB->ODR &=date;
	LCD1602_E_SET();
	LCD1602_E_RESET();//������
}

void LCD1620_SetAddress(unsigned char x,unsigned char y)
{
	if(y == 0)
	LCD1602_WriteCmd(0x80 | x);//�ӵ�һ�п�ʼ��ʾ
	else 
	LCD1602_WriteCmd(0x80 | 0x40 | x);//�ӵڶ��п�ʼ��ʾ
}

void LCD1602_ShowStr(unsigned char x,unsigned char y,unsigned char *str)//LCD1602��ʾ�ַ���
{
	LCD1620_SetAddress(x,y);//�������ݵ�ַָ��
	while(*str != '\0')
	LCD1602_WriteDate(*str++);//д����	
}

void LCD1602_ShowChar(unsigned char x,unsigned char y,unsigned char date)//LCD1602��ʾ�ַ�
{
	LCD1620_SetAddress(x,y);//�������ݵ�ַָ��
	LCD1602_WriteDate(date);//д����	
}
               
void LCD1602_ShowNum(unsigned char x,unsigned char y,unsigned char *str,unsigned char i)//LCD1602��ʾ����
{
	// LCD1620_SetAddress(x,y);//�������ݵ�ַָ��
	// str = str+ i;
	// LCD1602_WriteDate(*str);//д����
	// 	for (i = 0; i < Length; i++)		//�������ֵ�ÿһλ							
	// {
	// 	/*����OLED_ShowChar������������ʾÿ������*/
	// 	/*Number / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
	// 	/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
	// 	OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	// }
	LCD1620_SetAddress(x,y);//�������ݵ�ַָ��
	LCD1602_WriteDate(str + '0');

}

 void LCD1602_Init(void)//Һ����ʼ������
{
	LCD1602_GPIO_Init_Out();
	LCD1602_WriteCmd(0x38);//����16*2��ʾ��5*7����8λ���ݽӿ�
	LCD1602_WriteCmd(0x0c);//����ʾ,��ʾ��꣬��겻��˸
	LCD1602_WriteCmd(0x06);//����1����Ļ��ʾ���ƶ�
	LCD1602_WriteCmd(0x01);//����
}