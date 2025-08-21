#include <stdio.h>
#include "coin.h"
#include "zxerror.h"
#include "zxmacros.h"
#include "zxformat.h"
#include "app_mode.h"
#include "crypto.h"

zxerr_t addr_getNumItems(uint8_t *num_items) {
    zemu_log_stack("addr_getNumItems");
    *num_items = 1;

    if (app_mode_expert() || encoding != BECH32_CREATA ) {
        zemu_log("num_items 2\n");
        *num_items = 2;
    } else {
        zemu_log("num_items 1\n");
    }
    return zxerr_ok;
}

zxerr_t addr_getItem(int8_t displayIdx,
                     char *outKey, uint16_t outKeyLen,
                     char *outVal, uint16_t outValLen,
                     uint8_t pageIdx, uint8_t *pageCount) {
    ZEMU_LOGF(200, "[addr_getItem] %d/%d\n", displayIdx, pageIdx)

    switch (displayIdx) {
        case 0:
            snprintf(outKey, outKeyLen, "Address");
            pageString(outVal, outValLen, (char *) (G_io_apdu_buffer + VIEW_ADDRESS_OFFSET_SECP256K1), pageIdx, pageCount);
            ZEMU_LOGF(200, "[addr_getItem] pageCount %d\n", *pageCount)
            return zxerr_ok;
        case 1: {
            if (!app_mode_expert() && encoding == BECH32_CREATA) {
                return zxerr_no_data;
            }

            char buffer[300];
            snprintf(outKey, outKeyLen, "Path");
            bip32_to_str(buffer, sizeof(buffer), hdPath, HDPATH_LEN_DEFAULT);
            pageString(outVal, outValLen, buffer, pageIdx, pageCount);
            ZEMU_LOGF(200, "[addr_getItem] pageCount %d\n", *pageCount)
            return zxerr_ok;
        }
        default:
            zemu_log("[addr_getItem] no data\n");
            return zxerr_no_data;
    }
}
