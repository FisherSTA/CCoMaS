#pragma once
#include <dataStructure.hpp>
#include <json.hpp>
using json = nlohmann::json;
#include <fstream>

int tagCode()
{
    for (auto &it : data.entrys)
    {
        system(("ctags --output-format=json --c++-kinds=-Z-d-e-f-g-h-l-m-p+s+t-u-v-x-z-L-D+c-n-A-N-U -R GameContent/" + it.pattern + " > CCoMaSTemp").c_str());
        std::ifstream ifs("CCoMaSTemp");
        std::string line;
        while (std::getline(ifs, line))
        {
            json j = json::parse(line);
            it.members.insert(j["name"].get<std::string>());
            data.paths.insert(j["path"].get<std::string>());
        }
    }
    return 0;
}