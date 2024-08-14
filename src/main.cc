#include <cstdint>
#include <random>

#include "py32f003x8.h"

extern volatile uint32_t time_ms;

void Main() {}

void __attribute__((section(".ramfunc"))) SysTick_IRQHandler() { time_ms++; }
