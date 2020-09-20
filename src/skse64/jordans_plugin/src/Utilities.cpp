#pragma once
#include "Utilities.h"

namespace SavePlayerDataPlugin {

	EntryDataList* GetContainerItems(TESObjectREFR *container)
	{
		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(container->extraData.GetByType(kExtraData_ContainerChanges));
		if (!containerChanges) {
			return NULL;
		}
		return containerChanges->data->objList;
	}

	void SetContainerItems(TESObjectREFR* container, EntryDataList* items)
	{
		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(container->extraData.GetByType(kExtraData_ContainerChanges));
		if (!containerChanges) {
			return;
		}
		containerChanges->data->objList = items;
		return;
	}

	StatsData GetPlayerStats(PlayerCharacter* pc)
	{
		StatsData sd;
		sd.perks = pc->perks;
		sd.addedPerks = pc->addedPerks;
		sd.addedSpells = pc->addedSpells;
		sd.actorValueOwner = pc->actorValueOwner;
		sd.skills = *(pc->skills);
		sd.ss_perks = pc->standingStonePerks;
		sd.level = CALL_MEMBER_FN(pc, GetLevel)();
		return sd;
	}

}
