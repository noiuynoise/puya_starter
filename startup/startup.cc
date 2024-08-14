#include <stdint.h>

#include "py32f003x8.h"

extern uint8_t _sdata;
extern uint8_t _edata;
extern uint8_t _sbss;
extern uint8_t _ebss;
extern uint8_t _estack;
extern uint8_t _etext;
extern void (*_preinit_array_start[])();
extern void (*_preinit_array_end[])();
extern void (*_init_array_start[])();
extern void (*_init_array_end[])();


extern void SysTick_IRQHandler();

extern void Main();
extern void Setup();

[[noreturn]] void Loop() {
  __disable_irq();
  while(1){}
}

[[noreturn]] void Reset() {
  uint8_t* sbss = &_sbss;
  const uint8_t* ebss = &_ebss;
  while(sbss < ebss) {
    *sbss = 0;
    sbss++;
  }
  uint8_t* sdata = &_sdata;
  uint8_t* etext = &_etext;
  const uint8_t* edata = &_edata;
  while(sdata < edata) {
    *sdata = *etext;
    sdata++;
    etext++;
  }
  
  uint32_t len = _preinit_array_end - _preinit_array_start;
  for (uint32_t i = 0; i < len; i++) {
    _preinit_array_start[i]();
  }
  len = _init_array_end - _init_array_start;
  for (uint32_t i = 0; i < len; i++) {
    _init_array_start[i]();
  }

  Setup();

  Main();
  Loop();
}

void __attribute__((section (".vectors"))) (*vtable[39])() {
(void(*)())&_estack, // Stack pointer
&Reset, // Reset
&Loop, // NMI
&Loop, // Hard fault
&Loop, // SVCall
&Loop, // PendSV
&SysTick_IRQHandler, // SysTick
&SysTick_IRQHandler, // WWDG
&SysTick_IRQHandler, // PVD
&SysTick_IRQHandler, // RTC
&Loop, // FLASH
&Loop, // RCC
&Loop, // EXTI0_1
&Loop, // EXTI2_3
&SysTick_IRQHandler, // EXTI4_15
&SysTick_IRQHandler, // RESVD
&Loop, // DMA_CH1
&Loop, // DMA_CH2_3
&Loop, // RESVD
&Loop, // ADC_COMP
&Loop, // TIM1_BRK_UP_TRG_COM
&Loop, // TIM1_CC
&Loop, // RESVD
&Loop, // TIM3
&Loop, // LPTIM1
&Loop, // RESVD
&Loop, // TIM14
&Loop, // RESVD
&Loop, // TIM16
&Loop, // TIM17
&Loop, // I2C1
&Loop, // RESVD
&Loop, // SPI1
&Loop, // RESVD
&Loop, // USART1
&Loop, // USART2 but actually TIM14. did I count wrong?
&Loop, // RESVD
&Loop, // RESVD
&Loop, // RESVD
};