#pragma once

#include "json/json_parser.h"
#include <stdint.h>
#include <common/parser_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Validate json transaction
/// \param parsed_transacton
/// \param transaction
/// \return
parser_error_t tx_validate(parsed_json_t *json);

#ifdef __cplusplus
}
#endif
