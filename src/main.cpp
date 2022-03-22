#include <iostream>
#include <string>
#include <luaStuff.hpp>
#include <tagging.hpp>
#include <outputCppFiles.hpp>
#include <dataStructure.hpp>

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string(argv[1]) == "-isinstall"){
        std::cout << "Hell Yeah!" << std::endl;
        return 0;
    }
    runLuaConfig();
    tagCode();
    outputCppFiles();
    if (argc > 1 && std::string(argv[1]) == "-v")
    {
        for (auto &it1 : data.entrys)
        {
            std::cout << it1.name << ":" << std::endl;
            for (auto &it2 : it1.members)
            {
                std::cout << "\\  " << it2 << std::endl;
            }
        }
    }
    
    return 0;
}
