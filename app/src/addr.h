#pragma once
#include "zxerror.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Return the number of items in the address view
zxerr_t addr_getNumItems(uint8_t *num_items);

/// Gets an specific item from the address view (including paging)
zxerr_t addr_getItem(int8_t displayIdx,
                     char *outKey, uint16_t outKeyLen,
                     char *outValue, uint16_t outValueLen,
                     uint8_t pageIdx, uint8_t *pageCount);

#ifdef __cplusplus
}
#endif
