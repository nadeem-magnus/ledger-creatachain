#pragma once

#include "zxmacros.h"
#include <stdbool.h>
#include "zxerror.h"

#ifdef __cplusplus
extern "C" {
#endif

zxerr_t secret_enabled();

zxerr_t secret_getNumItems(uint8_t *num_items);

zxerr_t secret_getItem(int8_t displayIdx,
                       char *outKey, uint16_t outKeyLen,
                       char *outValue, uint16_t outValueLen,
                       uint8_t pageIdx, uint8_t *pageCount);

#ifdef __cplusplus
}
#endif
