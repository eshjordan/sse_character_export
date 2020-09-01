#include "skse64/PluginAPI.h"		// super
#include "skse64_common/skse_version.h"	// What version of SKSE is running?
#include <shlobj.h>				// CSIDL_MYCODUMENTS
#include <time.h>

#include "SkaarSpecialInventoryCrafting.h"
#include "SkaarSoulTrap.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;

extern "C"	{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)	{	// Called by SKSE to learn about this plugin and check that it's safe to load it
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim\\SKSE\\Skaar.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
#ifdef _DEBUG
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);
#else
		gLog.SetLogLevel(IDebugLog::kLevel_Message);
#endif

		_MESSAGE("Skaar SKSE Plugin");

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Skaar";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if (skse->isEditor) {
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		else if (skse->runtimeVersion != RUNTIME_VERSION_1_5_97) {
			_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

			return false;
		}

		// ### do not do anything else in this callback
		// ### only fill out PluginInfo and return true/false

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)	{	// Called by SKSE to load this plugin
		_MESSAGE("Skaar SKSE Plugin loaded");

		g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool registerInventoryCrafting = g_papyrus->Register(SkaarSpecialInventoryCrafting::RegisterFuncs);
		bool registerSoulTrap = g_papyrus->Register(SkaarSoulTrap::RegisterFuncs);

		if (registerInventoryCrafting && registerSoulTrap) {
			srand(time(NULL));
			_MESSAGE("Register Succeeded");
		}

		return true;
	}

};