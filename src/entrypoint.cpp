#include "entrypoint.h"
#include <embedder/src/Embedder.h>
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
bool IPExtension::Load(std::string& error, SourceHook::ISourceHook* SHPtr, ISmmAPI* ismm, bool late)
{
    SAVE_GLOBALVARS();
    return true;
}

bool IPExtension::Unload(std::string& error)
{
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

    SetupScripting(state);

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
