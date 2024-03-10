#pragma once
#include <string>


namespace Utils {
    bool string_contains_substring(std::string haystack, std::string needle);
    std::string str_to_lowercase(std::string sourceString);
    bool compare_to_filter(std::string original, std::string filter);
}