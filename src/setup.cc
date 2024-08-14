#include "py32f003x8.h"

volatile uint32_t time_ms = 0;

void ClockSetup();

void Setup() {
  ClockSetup();
  __enable_irq();
  NVIC_EnableIRQ(SysTick_IRQn);
}

void ClockSetup() {
  // set HSI to 24 Mhz
  const uint32_t hsi_trim = *(uint32_t *)0x1FFF0F10;
  RCC->ICSCR =
      (RCC->ICSCR & ~(RCC_ICSCR_HSI_FS_Msk | RCC_ICSCR_HSI_TRIM_Msk)) |
      ((0b100 << RCC_ICSCR_HSI_FS_Pos) | (hsi_trim << RCC_ICSCR_HSI_TRIM_Pos));
  // update systick to 1ms
  SysTick->LOAD = 24000 - 1;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
                  SysTick_CTRL_ENABLE_Msk;
  // enable GPIOA and GPIOB clocks
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN;
  // enable TIM14 and ADC clocks
  RCC->APBENR2 |= RCC_APBENR2_TIM14EN | RCC_APBENR2_ADCEN;
}
