#pragma once
#include <iostream>
#include <string>
#include <dataStructure.hpp>
#include <json.hpp>
using json = nlohmann::json;
#include <fstream>

extern "C" { // OK
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

extern "C" int printstacksize(lua_State *L){
    std::cout << "stack size" << std::endl;
    
    std::cout << lua_gettop(L) << std::endl;
    return 1;
}

extern "C" int addEntry(lua_State *L){
    std::string arg = luaL_checkstring(L, 1);
    entry myEntry;
    myEntry.name = arg; 
    data.entrys.push_back(myEntry);
    return 1;
}

extern "C" int setPattern(lua_State *L){
    std::string arg = luaL_checkstring(L, 1);
    data.entrys[data.entrys.size()-1].pattern = arg;
    return 1;
}

extern "C" int setFilter(lua_State *L)
{
    std::string arg = luaL_checkstring(L, 1);
    data.entrys[data.entrys.size()-1].filter = arg;
    return 1;
}

std::string inLuaLib = 
R"a(
split = function(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local t={}
    for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
        table.insert(t, str)
    end
    return t
end

inheritsFrom = function(table, class)
    if table["inherits"] ~= nil then
        for key, value in pairs(split(table["inherits"], ",")) do
            if value == class then
                return true
            end
        end
    end
    return false
end
)a";

lua_State *L;

int luaInit()
{
    if (!L)
    {
        L = luaL_newstate();
        luaL_openlibs(L);


        if (luaL_dostring(L, inLuaLib.c_str()) == LUA_OK)
        {
            lua_pop(L,lua_gettop(L));
        }
        else
        {
            std::cerr << "hekc: " << lua_tostring(L,-1) << std::endl;
        }

        lua_pushcfunction(L, printstacksize);
        lua_setglobal(L, "printstacksize");

        lua_pushcfunction(L, addEntry);
        lua_setglobal(L, "addEntry");

        lua_pushcfunction(L, setFilter);
        lua_setglobal(L, "setFilter");
        
        lua_pushcfunction(L, setPattern);
        lua_setglobal(L, "setPattern");
        return 0;
    }
    return 1;
}

int runLuaConfig()
{
    luaInit();
    if (luaL_dofile(L, "CCoMaS.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }
    return 0;
}

bool checkLuaFilter(json j, std::string filter)
{

    luaInit();
    lua_getglobal(L, "testFilter");
    lua_newtable(L);
    if (j.contains("inherits"))
    {
        lua_pushstring(L, "inherits");
        lua_pushstring(L, j["inherits"].get<std::string>().c_str());
        lua_settable(L, -3);
    }
    if (j.contains("name"))
    {
        lua_pushstring(L, "name");
        lua_pushstring(L, j["name"].get<std::string>().c_str());
        lua_settable(L, -3);
    }
    if (j.contains("path"))
    {
        lua_pushstring(L, "path");
        lua_pushstring(L, j["path"].get<std::string>().c_str());
        lua_settable(L, -3);
    }
    lua_call(L, 1, 1);
    bool result = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return result;
}