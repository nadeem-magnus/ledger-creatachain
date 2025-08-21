#include "os.h"
#include "cx.h"
#include "coin.h"
#include "app_main.h"
#include "tx.h"
#include "view.h"
#include "app_mode.h"

void secret_accept() {
#ifdef APP_SECRET_MODE_ENABLED
    app_mode_set_secret(true);
    view_idle_show(0, NULL);
#endif
}

//static char *secret_message = "";

zxerr_t secret_getNumItems(uint8_t *num_items) {
    *num_items = 0;
    return zxerr_no_data;
}

zxerr_t secret_getItem(int8_t displayIdx,
                       char *outKey, uint16_t outKeyLen,
                       char *outVal, uint16_t outValLen,
                       uint8_t pageIdx, uint8_t *pageCount) {
    UNUSED(displayIdx);
    UNUSED(outKey);
    UNUSED(outKeyLen);
    UNUSED(outVal);
    UNUSED(outValLen);
    UNUSED(pageIdx);
    UNUSED(pageCount);
    return zxerr_no_data;
}

zxerr_t secret_enabled() {
    return zxerr_no_data;
}
