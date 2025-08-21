#include "chain_config.h"
#include <zxmacros.h>

typedef struct {
    const uint32_t path;
    const char *hrp;
    const address_encoding_e encoding;
} chain_config_t;

// To enable custom config for a new chain, just add a new entry in this array with path, hrp and encoding
static const chain_config_t chainConfig[] = {
    {118, "creata", BECH32_CREATA},
    // {118, "cosmos", BECH32_CREATA},
    // {60, "inj", BECH32_ETH},
    // {60, "evmos", BECH32_ETH},
    // {60, "xpla", BECH32_ETH},
    // {60, "dym", BECH32_ETH},
    // {60, "zeta", BECH32_ETH},
    // {60, "bera", BECH32_ETH},
    // {60, "human", BECH32_ETH},
    // {118, "osmos", BECH32_CREATA},
    // {118, "dydx", BECH32_CREATA},
    // {118, "mantra", BECH32_CREATA},
    // {118, "xion", BECH32_CREATA},
    // {118, "celestia", BECH32_CREATA}
};

static const uint32_t chainConfigLen = sizeof(chainConfig) / sizeof(chainConfig[0]);

address_encoding_e checkChainConfig(uint32_t path, const char* hrp, uint8_t hrpLen) {
    // Always allowed for 118 (default Cosmos)
    if (path == HDPATH_1_DEFAULT) {
        return BECH32_CREATA;
    }

    // Check special cases
    for (uint32_t i = 0; i < chainConfigLen; i++) {
        if (path == (0x80000000u | chainConfig[i].path)) {
            const char* hrpPtr = (const char *) PIC(chainConfig[i].hrp);
            const uint16_t hrpPtrLen = strlen(hrpPtr);
            if (hrpPtrLen == hrpLen && memcmp(hrpPtr, hrp, hrpLen) == 0) {
                return chainConfig[i].encoding;
            }
        }
    }

    return UNSUPPORTED;
}
