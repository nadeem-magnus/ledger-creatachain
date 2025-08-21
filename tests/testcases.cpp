#include "testcases.h"
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <algorithm>

std::vector<testcase_t> GetJsonTestCases(const std::string &jsonFile) {
    auto answer = std::vector<testcase_t>();

    const Json::CharReaderBuilder builder;
    const std::shared_ptr<Json::Value> obj(new Json::Value());


    const std::string fullPathJsonFile = std::string(TESTVECTORS_DIR) + jsonFile;

    std::ifstream inFile(fullPathJsonFile);
    if (!inFile.is_open()) {
        return answer;
    }

    // Retrieve all test cases
    JSONCPP_STRING errs;
    Json::parseFromStream(builder, inFile, obj.get(), &errs);
    std::cout << "Number of testcases: " << obj->size() << std::endl;
    answer.reserve(obj->size());

    for (int i = 0; i < obj->size(); i++) {
        auto v = (*obj)[i];

        Json::StreamWriterBuilder wbuilder;
        wbuilder["commentStyle"] = "None";
        wbuilder["indentation"] = "";
        const std::string txStr = Json::writeString(wbuilder, v["tx"]);

        auto expected = std::vector<std::string>();
        for (const auto j : v["expected"]) {
            expected.push_back(j.asString());
        }

        bool expert = false;
        expert = v["expert"].asBool();

        answer.push_back(
                testcase_t{
                        0,
                        v["name"].asString(),
                        txStr,
                        v["parsingErr"].asString(),
                        v["validationErr"].asString(),
                        expected,
                        expected,
                        expert
                });
    }

    return answer;
}

std::vector<testcase_t> GetJsonTextualTestCases(const std::string &jsonFile) {
     auto answer = std::vector<testcase_t>();

    const Json::CharReaderBuilder builder;
    Json::Value obj;

    const std::string fullPathJsonFile = std::string(TESTVECTORS_DIR) + jsonFile;

    std::ifstream inFile(fullPathJsonFile);
    if (!inFile.is_open()) {
        return answer;
    }

    // Retrieve all test cases
    JSONCPP_STRING errs;
    Json::parseFromStream(builder, inFile, &obj, &errs);
    std::cout << "Number of testcases: " << obj.size() << std::endl;

    for (int i = 0; i < obj.size(); i++) {

        auto outputs = std::vector<std::string>();
        for (auto s : obj[i]["output"]) {
            outputs.push_back(s.asString());
        }

        auto outputs_expert = std::vector<std::string>();
        for (auto s : obj[i]["output_expert"]) {
            outputs_expert.push_back(s.asString());
        }

        answer.push_back(testcase_t{
                obj[i]["index"].asUInt64(),
                obj[i]["name"].asString(),
                obj[i]["blob"].asString(),
                "",
                "",
                outputs,
                outputs_expert,
                false
        });
    }
    return answer;
}
