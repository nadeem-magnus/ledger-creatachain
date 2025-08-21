#include "bignum.h"
#include "crypto.h"
#include "lib_standard_app/swap_lib_calls.h"
#include "swap.h"
#include "swap_utils.h"
#include "zxformat.h"

void handle_get_printable_amount(get_printable_amount_parameters_t *params) {
    if (params == NULL) {
        return;
    }

    uint8_t amount[COIN_AMOUNT_MAXSIZE] = {0};
    MEMZERO(amount, sizeof(amount));
    MEMZERO(params->printable_amount, sizeof(params->printable_amount));

    if (params->amount_length > COIN_AMOUNT_MAXSIZE) {
        return;
    }

    memcpy(amount + COIN_AMOUNT_MAXSIZE - params->amount_length, params->amount, params->amount_length);

    char tmp_amount[110] = {0};
    int8_t chain_index = find_chain_index_by_coin_config((char *)&params->coin_configuration[1], params->coin_configuration[0]);
    if (chain_index == -1) {
        return;
    }
    zxerr_t zxerr = bytesAmountToStringBalance(amount, sizeof(amount), tmp_amount, sizeof(tmp_amount), chain_index);

    if (zxerr != zxerr_ok || strnlen(tmp_amount, sizeof(tmp_amount)) > sizeof(params->printable_amount)) {
        return;
    }
    strncpy(params->printable_amount, tmp_amount, sizeof(params->printable_amount) - 1);
}
