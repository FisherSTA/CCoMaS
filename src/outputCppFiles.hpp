#include <fstream>
#include <string>
#include <iostream>
#include <dataStructure.hpp>

int outputCppFiles()
{
    std::ofstream output("CCoMaS/CCoMaS.hpp");
    for (auto &it : data.paths)
    {
        output << "#include <" << it << ">" << std::endl;
    }
    output << std::endl;

    for (auto &entryit : data.entrys){
        output << "#define " << entryit.name << " ";
        bool first = true;
        for (auto &memberit : entryit.members){
            if (!first) output << ",";
            output << memberit;
            first = false;
        }
        output << std::endl;
    }
    return 0;
}