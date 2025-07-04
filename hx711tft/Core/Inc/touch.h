/*
 * touch.h
 *
 *  Created on: Apr 22, 2023
 *      Author: user
 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#include "sys.h"

#define TP_PRES_DOWN 0x80  //����������
#define TP_CATH_PRES 0x40  //�а���������
typedef struct
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;
	void (*adjust)(void);		//������У׼
	u16 x0;						//ԭʼ����(��һ�ΰ���ʱ������)
	u16 y0;
	u16 x; 						//��ǰ����(�˴�ɨ��ʱ,����������)
	u16 y;
	u8  sta;					//�ʵ�״̬
								//b7:����1/�ɿ�0;
	                            //b6:0,û�а�������;1,�а�������.
////////////////////////������У׼����/////////////////////////
	float xfac;
	float yfac;
	short xoff;
	short yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//�봥����оƬ��������
//�봥����оƬ��������

#define PEN    	   HAL_GPIO_ReadPin(T_IRQ_GPIO_Port,T_IRQ_Pin)   //T_PEN   T_IRQ
#define DOUT       HAL_GPIO_ReadPin(T_DO_GPIO_Port,T_DO_Pin)     //       T_MISO not use

#define TDIN(n)   (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET))     //T_MOSI
#define TCLK(n)   (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET))     //T_SCK
#define TCS(n)    (n?HAL_GPIO_WritePin(T_CS_GPIO_Port,T_CS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(T_CS_GPIO_Port,T_CS_Pin,GPIO_PIN_RESET))     //T_CS

void TP_Write_Byte(u8 num);						//�����оƬд��һ������
u16 TP_Read_AD(u8 CMD);							//��ȡADת��ֵ
u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//˫�����ȡ(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//��һ������У׼��
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//��һ�����
u8 TP_Scan(u8 tp);								//ɨ��
void TP_Save_Adjdata(void);						//����У׼����
u8 TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
u8 TP_Init(void);								//��ʼ��

void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//��ʾУ׼��Ϣ
#endif /* INC_TOUCH_H_ */
