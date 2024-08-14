#include <cstdint>
#include <random>

#include "py32f003x8.h"

uint32_t time_ms{0};

void Main() {}

void __attribute__((section(".ramfunc"))) SysTick_IRQHandler() { time_ms++; }
