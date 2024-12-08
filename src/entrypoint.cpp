#include "entrypoint.h"
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
#include <LuaBridge/LuaBridge.h>
#include "ipclass.h"

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

IPExtension g_Ext;
CREATE_GLOBALVARS();

//////////////////////////////////////////////////////////////
/////////////////          Core Class          //////////////
////////////////////////////////////////////////////////////

EXT_EXPOSE(g_Ext);
bool IPExtension::Load(std::string& error, SourceHook::ISourceHook *SHPtr, ISmmAPI* ismm, bool late)
{
    SAVE_GLOBALVARS();
    if(!InitializeHooks()) {
        error = "Failed to initialize hooks.";
        return false;
    }

    return true;
}

bool IPExtension::Unload(std::string& error)
{
    UnloadHooks();
    return true;
}

void IPExtension::AllExtensionsLoaded()
{
}

void IPExtension::AllPluginsLoaded()
{

}

bool IPExtension::OnPluginLoad(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    if(kind == PluginKind_t::Lua) {
        lua_State* state = (lua_State*)pluginState;

        luabridge::getGlobalNamespace(state)
            .beginClass<PluginIPAPI>("IPAPI")
            .addConstructor<void (*)(std::string)>()
            .addFunction("GetIsoCode", &PluginIPAPI::GetIsoCode)
            .addFunction("GetContinent", &PluginIPAPI::GetContinent)
            .addFunction("GetCountry", &PluginIPAPI::GetCountry)
            .addFunction("GetRegion", &PluginIPAPI::GetRegion)
            .addFunction("GetCity", &PluginIPAPI::GetCity)
            .addFunction("GetTimezone", &PluginIPAPI::GetTimezone)
            .addFunction("GetLatitude", &PluginIPAPI::GetLatitude)
            .addFunction("GetLongitude", &PluginIPAPI::GetLongitude)
            .addFunction("GetASN", &PluginIPAPI::GetASN)
            .endClass();

        luaL_dostring(state, "ip = IPAPI(GetCurrentPluginName())");
    }
    return true;
}

bool IPExtension::OnPluginUnload(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    return true;
}

const char* IPExtension::GetAuthor()
{
    return "Swiftly Development Team";
}

const char* IPExtension::GetName()
{
    return "IP Address API";
}

const char* IPExtension::GetVersion()
{
#ifndef VERSION
    return "Local";
#else
    return VERSION;
#endif
}

const char* IPExtension::GetWebsite()
{
    return "https://swiftlycs2.net/";
}
