#ifndef GLOBAL_INPUT_HANDLER_H
#define GLOBAL_INPUT_HANDLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void on_global_key_press(uint32_t key);
void on_global_key_released(uint32_t key);

#ifdef __cplusplus
}
#endif

#endif
