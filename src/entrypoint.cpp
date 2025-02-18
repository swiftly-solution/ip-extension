#include "entrypoint.h"
#include <Embedder.h>
#include "ipclass.h"

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

IPExtension g_Ext;
CUtlVector<FuncHookBase *> g_vecHooks;
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
    EContext* state = (EContext*)pluginState;

    BeginClass<PluginIPAPI>("IPAPI", state)
        .addConstructor<std::string>()
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

    GetGlobalNamespace(state).addConstant("ip", PluginIPAPI(pluginName));

    return true;
}

bool IPExtension::OnPluginUnload(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    EContext* state = (EContext*)pluginState;
    
    GetGlobalNamespace(state).addConstant("ip", nullptr);
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
