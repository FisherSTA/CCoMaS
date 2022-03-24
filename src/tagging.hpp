#pragma once
#include <dataStructure.hpp>
#include <json.hpp>
using json = nlohmann::json;
#include <fstream>
#include <luaStuff.hpp>

int tagCode()
{

    for (auto &it : data.entrys)
    {
        system(("ctags --output-format=json --fields=+i --c++-kinds=-Z-d-e-f-g-h-l-m-p+s+t-u-v-x-z-L-D+c-n-A-N-U -R GameContent/" + it.pattern + " > CCoMaSTemp").c_str());
        std::ifstream ifs("CCoMaSTemp");
        std::string line;
        while (std::getline(ifs, line))
        {
            json j = json::parse(line);
            if (it.filter != "")
            {
                if (!checkLuaFilter(j, it.filter)) continue;
            }
            it.members.insert(j["name"].get<std::string>());
            data.paths.insert(j["path"].get<std::string>());
        }
    }
    return 0;
}