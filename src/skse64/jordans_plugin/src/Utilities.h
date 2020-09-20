#pragma once
#include "skse64/GameExtraData.h"
#include "skse64/GameReferences.h"

namespace SavePlayerDataPlugin {

	typedef struct StatsData
	{
		tArray<BGSPerk*> perks;
		BGSPerkRanks addedPerks;
		Actor::SpellArray addedSpells;
		ActorValueOwner actorValueOwner;
		PlayerSkills skills;
		tArray<BGSPerk*> ss_perks;
		UInt16 level;
	} StatsData;

	EntryDataList* GetContainerItems(TESObjectREFR* container);
	void SetContainerItems(TESObjectREFR* container, EntryDataList* items);
	StatsData GetPlayerStats(PlayerCharacter* pc);

}
