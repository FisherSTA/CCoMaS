#pragma once
#include <vector>
#include <unordered_set>
#include <string>

struct entry
{
    std::string pattern;
    std::string name;
    std::string filter;
    std::unordered_set<std::string> members;
};

struct {
    std::vector<entry> entrys;
    std::unordered_set<std::string> paths;
} data;