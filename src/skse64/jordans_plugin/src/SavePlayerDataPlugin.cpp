#include "SavePlayerDataPlugin.h"
#include "Utilities.h"

namespace SavePlayerDataPlugin
{
	bool SPDLoadData(PlayerCharacter* pc)
	{
		return true;
	}

	bool SPDSaveData(PlayerCharacter* pc)
	{
		auto items = GetContainerItems(pc);
		auto stats = GetPlayerStats(pc);
		spd_instance->;
		return true;
	}

	bool RegisterFuncs(VMClassRegistry* registry)
	{
		registry->RegisterFunction(
			new NativeFunction0<PlayerCharacter, bool>("SPDLoadData", "PlayerCharacter", SavePlayerData::SPDLoadData, registry)
		);
		registry->RegisterFunction(
			new NativeFunction0<PlayerCharacter, bool>("SPDSaveData", "PlayerCharacter", SavePlayerData::SPDSaveData, registry)
		);

		return true;
	}
}