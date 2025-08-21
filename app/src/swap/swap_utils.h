#pragma once

#include "stdbool.h"
#include "stdint.h"
#include "zxerror.h"

// Helper functions for swap handlers
int8_t find_chain_index_by_coin_config(const char *coin_config, uint8_t coin_config_len);
int8_t find_chain_index_by_chain_id(const char *chain_id);
zxerr_t bytesAmountToStringBalance(uint8_t *amount, uint8_t amount_len, char *out, uint8_t out_len, int8_t chain_index);
zxerr_t bytesAmountToExpertStringBalance(uint8_t *amount, uint8_t amount_len, char *out, uint8_t out_len, int8_t chain_index);
zxerr_t format_amount(uint8_t *amount, uint8_t amount_len, char *out, uint8_t out_len, int8_t chain_index);
zxerr_t readU32BE(uint8_t *input, uint32_t *output);
