#pragma once

#include <stdint.h>
#include "parser_impl.h"
#include <common/parser_common.h>
#include "parser_txdef.h"
#include "coin.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    root_item_chain_id = 0,
    root_item_account_number,
    root_item_sequence,
    root_item_msgs,
    root_item_memo,
    root_item_fee,
    root_item_tip,
} root_item_e;

parser_error_t tx_is_expert_mode_or_not_default_chainid(bool *expert_or_default);

const char *get_required_root_item(root_item_e i);

parser_error_t tx_display_query(uint16_t displayIdx,
                                char *outKey, uint16_t outKeyLen,
                                uint16_t *ret_value_token_index);

parser_error_t tx_display_numItems(uint8_t *num_items);

parser_error_t tx_display_make_friendly();

parser_error_t tx_display_translation(char *dst, uint16_t dstLen, char *src, uint16_t srcLen);
//---------------------------------------------

#ifdef __cplusplus
}
#endif
