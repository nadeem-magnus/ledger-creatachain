#include <parser.h>
#include <sstream>
#include <string>
#include "common.h"
#include <tx_display.h>
#include <fmt/core.h>
#include "keccak.h"
#include "bech32.h"
#include "hexutils.h"
#include "gmock/gmock.h"
#include "coin.h"

std::vector<std::string> dumpUI(parser_context_t *ctx,
                                uint16_t maxKeyLen,
                                uint16_t maxValueLen) {
    auto answer = std::vector<std::string>();

    uint8_t numItems;
    parser_error_t err = parser_getNumItems(ctx, &numItems);
    if (err != parser_ok) {
        return answer;
    }

    for (uint16_t idx = 0; idx < numItems; idx++) {
        char keyBuffer[1000];
        char valueBuffer[1000];
        uint8_t pageIdx = 0;
        uint8_t pageCount = 1;

        while (pageIdx < pageCount) {
            std::stringstream ss;

            err = parser_getItem(ctx,
                                 idx,
                                 keyBuffer, maxKeyLen,
                                 valueBuffer, maxValueLen,
                                 pageIdx, &pageCount);

            ss << fmt::format("{} | {}", idx, keyBuffer);
            if (pageCount > 1) {
                ss << fmt::format(" [{}/{}]", pageIdx + 1, pageCount);
            }
            ss << " : ";

            if (err == parser_ok) {
                // Model multiple lines
                ss << fmt::format("{}", valueBuffer);
            } else {
                ss << parser_getErrorDescription(err);
            }

            auto output = ss.str();
            if (output.back() == ' ') {
                output = output.substr(0, output.size() - 1);
            }

            answer.push_back(output);

            pageIdx++;
        }
    }

    return answer;
}