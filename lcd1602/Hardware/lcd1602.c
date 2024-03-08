#include  "LCD1602.h"
#include "delay.h"


uint8_t i;
uint8_t CGCODE[]={
   0x10,0x18,0x1C,0x1E,0x1E,0x1C,0x18,0x10,//">"����  0x00
   };
/******************************************************************************
 * ��������:void GPIO_Configuration()				      		*
 * ��������:LCD1602���ų�ʼ��						 					      		*
 * �������:��									      			*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
 ******************************************************************************/
/*******************�����Լ���Ӳ���������޸�*****************************************/
void GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//ѡ����Ƶ��
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;//���ù���ģʽ
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 						
	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;//���ù���ģʽ
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//ѡ����Ƶ��
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}
/******************************************************************************
 * ��������:void LCD1602_Init()				      		*
 * ��������:LCD1602��ʼ��						 					      		*
 * �������:��									      			*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Init()
{
	GPIO_Configuration();			//��ʼ������

	LCD1602_Write_Cmd( 0x38 );      //��ʾģʽ����
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x0c );      //��ʾ�����������
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x06 );      //��ʾ����ƶ�λ��
	Delay_ms( 5 );
	LCD1602_Write_Cmd( 0x01 );      //��ʾ����
	Delay_ms( 5 );	

	LCD1602_Write_Cmd(0x40);	
	for(i=0;i<8;i++)//ѭ��56��д��
	{
		LCD1602_Write_Dat(CGCODE[i]);   
	}
}
/******************************************************************************
 * ��������:void LCD1602_Write_Cmd(uint8_t cmd)				      		*
 * ��������:д�����							 					      		*
 * �������:	cmd ����										      			*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Write_Cmd( uint8_t cmd )
{
	LCD_RS_Clr();
	LCD_RW_Clr();
	LCD_EN_Set();

	GPIO_Write( GPIOA, (GPIO_ReadOutputData( GPIOA ) & 0xff00) | cmd );//�Ե�ƽ�Ķ�ȡ

	DATAOUT( cmd );
	Delay_ms( 5 );
	LCD_EN_Clr();
}

/******************************************************************************
 * ��������:void LCD1602_Write_Dat(uint8_t date)				      		*
 * ��������:д���ݺ���							 					      		*
 * �������:	date ����										      			*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_Write_Dat( uint8_t data )
{
	LCD_RS_Set();
	LCD_RW_Clr();
	LCD_EN_Set();

	GPIO_Write( GPIOA, (GPIO_ReadOutputData( GPIOA ) & 0xff00) | data );//�Ե�ƽ�Ķ�ȡ

	Delay_ms( 5 );
	LCD_EN_Clr();
}

/******************************************************************************
 * ��������:void LCD1602_ClearScreen()				      		*
 * ��������:1602��������							 					      		*
 * �������:��										      			*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
 ******************************************************************************/
void LCD1602_ClearScreen()
{
	LCD1602_Write_Cmd( 0x01 );
}

/******************************************************************************
 * ��������:void LCD1602_Set_Cursor(uint8_t x, uint8_t y)				      		*
 * ��������:����1602λ�ú���							 					      *
 * �������:x ������ y ������									      				*
 * ����ֵ  :��														          *
 * ����˵��:	 				 				     			  				*
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
	uint32_t Result = 1;	//���Ĭ��Ϊ1
	while (Y --)			//�۳�Y��
	{
		Result *= X;		//ÿ�ΰ�X�۳˵������
	}
	return Result;
}



void LCD1602_Show_Code(uint8_t x, uint8_t y, char index )
{
	LCD1602_Set_Cursor( x, y );
    
	LCD1602_Write_Dat(index);
}


/******************************************************************************
 * ��������:void LCD1602_Show_Str( uint8_t x, uint8_t y, uint8_t *str )				      		*
 * ��������:ָ��λ����ʾ�ַ�������							 					      *
 * �������:x ������ y ������		*str �ַ���							      *
 * ����ֵ  :	��													          *
 * ����˵��:	 				 				     			  				*
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
	LCD1602_Set_Cursor(x,y);//�������ݵ�ַָ��
	for (i = 0; i < Length; i++)		//�������ֵ�ÿһλ							
	{
		/*����OLED_ShowChar������������ʾÿ������*/
		/*Number / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
		/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
		//OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
		LCD1602_Write_Dat(Num / LCD1602_Pow(10,Length - i - 1) % 10 + '0');
	}
}