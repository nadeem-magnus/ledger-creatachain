#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "coin.h"

address_encoding_e checkChainConfig(uint32_t path, const char* hrp, uint8_t hrpLen);

#ifdef __cplusplus
}
#endif
