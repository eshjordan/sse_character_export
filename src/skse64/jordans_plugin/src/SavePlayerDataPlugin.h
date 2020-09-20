#pragma once
#include "SavePlayerData.hpp"

#include "skse64/GameReferences.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusVM.h"

namespace SavePlayerDataPlugin {

	static SavePlayerData* spd_instance;

	bool RegisterFuncs(VMClassRegistry* registry);

	bool SPDLoadData(PlayerCharacter* pc);
	bool SPDSaveData(PlayerCharacter* pc);

}