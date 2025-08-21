#pragma once
#include <json/json.h>
#include <fstream>

typedef struct {
    uint64_t index;                           //textual mode
    std::string name;                    
    std::string tx;
    std::string parsingErr;
    std::string validationErr;
    std::vector<std::string> expected;
    std::vector<std::string> expected_expert; //textual mode
    bool expert;
} testcase_t;

std::vector<testcase_t> GetJsonTestCases(const std::string& filename);
std::vector<testcase_t> GetJsonTextualTestCases(const std::string &jsonFile);
