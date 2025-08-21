#pragma once

#include "cbor.h"
#include <zxmacros.h>
#include <parser_txdef.h>
#include <common/parser_common.h>


parser_error_t parser_mapCborError(CborError err);

#define CHECK_CBOR_MAP_ERR(CALL) { \
    CborError err = CALL;  \
    if (err!=CborNoError) return parser_mapCborError(err);}

#define PARSER_ASSERT_OR_ERROR(CALL, ERROR) if (!(CALL)) return ERROR;

#define CHECK_CBOR_TYPE(type, expected) {if ((type)!=(expected)) return parser_unexpected_type;}

#define INIT_CBOR_PARSER(c, it)  \
    CborParser parser;           \
    CHECK_CBOR_MAP_ERR(cbor_parser_init((c)->buffer + (c)->offset, (c)->bufferLen - (c)->offset, 0, &parser, &(it)))

#define READ_STRING_PTR_SIZE(it, V_OUTPUT_PTR, V_OUTPUT_SIZE)                   \
    PARSER_ASSERT_OR_ERROR(cbor_value_is_text_string(it), parser_context_mismatch);  \
    it->flags = 0x64; \
    CHECK_CBOR_MAP_ERR(cbor_value_get_text_string_chunk(it,(const char **)&V_OUTPUT_PTR, &V_OUTPUT_SIZE, NULL));


typedef struct Cbor_container {
    size_t n_field;
    screen_arg_t screen;
} Cbor_container;

parser_error_t cbor_get_containerInfo(CborValue *data, Cbor_container *container);
parser_error_t cbor_check_expert(CborValue *data, Cbor_container *container);
