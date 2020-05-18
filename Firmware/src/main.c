#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIOSetup;
EXTI_InitTypeDef EXTISetup;
NVIC_InitTypeDef NVICSetup;

void GPIO_Configuration(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIOSetup.GPIO_Mode = 0x01;
	GPIOSetup.GPIO_OType = 0x00;
	GPIOSetup.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIOSetup.GPIO_PuPd = 0x00;
	GPIOSetup.GPIO_Speed = 0x00;
	GPIO_Init(GPIOD, &GPIOSetup);
	GPIOSetup.GPIO_Mode = 0x00;
	GPIOSetup.GPIO_OType = 0x00;
	GPIOSetup.GPIO_Pin = GPIO_Pin_0;
	GPIOSetup.GPIO_PuPd = 0x02;
	GPIOSetup.GPIO_Speed = 0x00;
	GPIO_Init(GPIOA, &GPIOSetup);
}
void EXT_Configuration (){
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EXTISetup.EXTI_Line = EXTI_Line0;
	EXTISetup.EXTI_LineCmd = ENABLE;
	EXTISetup.EXTI_Mode = 0x00;
	EXTISetup.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTISetup);
	NVICSetup.NVIC_IRQChannel = EXTI0_IRQn;
	NVICSetup.NVIC_IRQChannelCmd = ENABLE;
	NVICSetup.NVIC_IRQChannelPreemptionPriority = 0;
	NVICSetup.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVICSetup);
}

void delay(uint32_t t){
	while(t--);
}

void EXTI0_IRQHandler(){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void)
{
  GPIO_Configuration();
  EXT_Configuration();
  while (1)
  {
	  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
