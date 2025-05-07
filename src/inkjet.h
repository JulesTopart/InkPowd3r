#pragma once
#include <inttypes.h>

extern uint16_t strip_buffer;

void hpc6602_init();
void nozzle_trigger(const uint16_t &strip_code);
void nozzle_trigger_individual(const uint8_t &strip_code);


