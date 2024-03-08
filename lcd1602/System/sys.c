/**
 * @file sys.c
 * @author JackeyZ
 * @brief 
 * @version 0.1
 * @date 2023-1-21
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#include "sys.h"

uint8_t uid[SYSTEM_UID_SIZE];


void GetUID(uint8_t *uid)
{
	uint32_t CpuID[3];
	//��ȡCPUΨһID
	CpuID[0]=*(uint32_t*)(0x1ffff7e8);
	CpuID[1]=*(uint32_t*)(0x1ffff7ec);
	CpuID[2]=*(uint32_t*)(0x1ffff7f0);

	uid[0] = ((CpuID[0]) >> 24)|0x00;
	uid[1] = ((CpuID[0]) >> 16)|0x00;
	uid[2] = ((CpuID[0]) >>  8)|0x00;
	uid[3] = (CpuID[0])|0x00;
	uid[4] = ((CpuID[1]) >> 24)|0x00;
	uid[5] = ((CpuID[1]) >> 16)|0x00;
	uid[6] = ((CpuID[1]) >> 8)|0x00;
	uid[7] = (CpuID[1])|0x00;
	uid[8] = ((CpuID[2]) >> 24)|0x00;
	uid[9] = ((CpuID[2]) >> 16)|0x00;
	uid[10] = ((CpuID[2]) >> 8)|0x00;
	uid[11] = (CpuID[2])|0x00;
}



void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
// ����ջ����ַ
// addr:ջ����ַ
void MSR_MSP(u32 addr)
{
__ASM volatile("MSR MSP, r0");
__ASM volatile("BX r14");
}
