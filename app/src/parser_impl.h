#pragma once

#include "parser_common.h"
#include <zxmacros.h>
#include "zxtypes.h"
#include "json/json_parser.h"
#include "parser_txdef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const uint8_t *buffer;
    uint16_t bufferLen;
    uint16_t offset;
    parser_tx_t *tx_obj;
} parser_context_t;

typedef struct {
    const char *str1;
    const char *str2;
} key_subst_t;

typedef struct {
    char ascii_code;
    char str;
} ascii_subst_t;

extern parser_tx_t parser_tx_obj;

parser_error_t _read_json_tx(parser_context_t *c, parser_tx_t *v);
parser_error_t _read_text_tx(parser_context_t *c, parser_tx_t *v);

#ifdef __cplusplus
}
#endif
