#pragma once
#include <iostream>
#include <string>
#include <dataStructure.hpp>

extern "C" { // OK
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

extern "C" int printstacksize(lua_State *L){
    std::cout << "my int" << std::endl;
    
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

extern "C" int setPatern(lua_State *L){
    std::string arg = luaL_checkstring(L, 1);
    data.entrys[data.entrys.size()-1].pattern = arg;
    return 1;
}

lua_State *L;

int runLuaConfig()
{
    if (!L)
    {
        L = luaL_newstate();
        luaL_openlibs(L);

        lua_pushcfunction(L, printstacksize);
        lua_setglobal(L, "printstacksize");

        lua_pushcfunction(L, addEntry);
        lua_setglobal(L, "addEntry");

        lua_pushcfunction(L, setPatern);
        lua_setglobal(L, "setPatern");
    }
    
    if (luaL_dofile(L, "CCoMaS.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }


    lua_close(L);
    
    return 0;
}