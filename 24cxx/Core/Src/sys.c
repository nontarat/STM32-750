/*
 * sys.c
 *
 *  Created on: Apr 25, 2023
 *      Author: user
 */


void Cache_Enable(void)
{
    SCB_EnableICache();//ʹ��I-Cache
    SCB_EnableDCache();//ʹ��D-Cache
	SCB->CACR|=1<<2;   //ǿ��D-Cache͸д,�粻����,ʵ��ʹ���п���������������
}
