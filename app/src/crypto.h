#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <zxmacros.h>
#include "coin.h"
#include <stdbool.h>
#include <sigutils.h>
#include "zxerror.h"

#define MAX_BECH32_HRP_LEN      120u

extern uint32_t hdPath[HDPATH_LEN_DEFAULT];
extern char bech32_hrp[MAX_BECH32_HRP_LEN + 1];
extern uint8_t bech32_hrp_len;
extern address_encoding_e encoding;

zxerr_t crypto_fillAddress(uint8_t *buffer, uint16_t bufferLen, uint16_t *addrResponseLen);

zxerr_t crypto_sign(uint8_t *signature, uint16_t signatureMaxlen, uint16_t *signatureLen);

zxerr_t crypto_swap_fillAddress(uint32_t *hdPath_swap,
                                      uint8_t hdPathLen_swap,
                                      char *hrp,
                                      address_encoding_e encode_type,
                                      char *buffer,
                                      uint16_t bufferLen,
                                      uint16_t *addrResponseLen);
#ifdef __cplusplus
}
#endif
