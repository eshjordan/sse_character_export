#pragma once
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "skse64/GameExtraData.h"
#include "skse64/GameReferences.h"
#include "skse64_common/Utilities.h"

class SavePlayerData
{

public:
	typedef struct StatsData
	{
		tArray<BGSPerk*> perks;
		BGSPerkRanks addedPerks;
		//Actor::SpellArray addedSpells;
		ActorValueOwner actorValueOwner;
		PlayerSkills skills;
		tArray<BGSPerk*> ss_perks;
		UInt16 level;
	} StatsData;

private:
	EntryDataList inventory;
	StatsData stats;
	std::string _profile_name;
	std::fstream profile_stream;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _profile_name;
		ar& inventory;
		ar& stats;
	}

public:
	SavePlayerData() = default;

	SavePlayerData(std::string profile_name) : _profile_name(profile_name)
	{
		LoadProfile(profile_name);
	}

	bool GetContainerItems(TESObjectREFR* container) {
		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(container->extraData.GetByType(kExtraData_ContainerChanges));
		if (!containerChanges) {
			return false;
		}
		inventory = *(containerChanges->data->objList);
		return true;
	}

	bool SetContainerItems(TESObjectREFR* container)
	{
		ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(container->extraData.GetByType(kExtraData_ContainerChanges));
		if (!containerChanges) {
			return false;
		}
		containerChanges->data->objList = new EntryDataList(inventory);
		return true;
	}

	bool GetPlayerStats(PlayerCharacter* pc)
	{
		stats.perks.CopyFrom(&(pc->perks));
		stats.addedPerks.CopyFrom(&(pc->addedPerks));
		//stats.addedSpells = pc->addedSpells;
		stats.actorValueOwner = pc->actorValueOwner;
		stats.skills = *(pc->skills);
		stats.ss_perks.CopyFrom(&(pc->standingStonePerks));
		stats.level = CALL_MEMBER_FN(pc, GetLevel)();

		return true;
	}

	bool SetPlayerStats(PlayerCharacter* pc)
	{
		pc->perks.CopyFrom(&(stats.perks));
		pc->addedPerks.CopyFrom(&(stats.addedPerks));
		//stats.addedSpells = pc->addedSpells;
		pc->actorValueOwner = stats.actorValueOwner;
		*(pc->skills) = stats.skills;
		pc->standingStonePerks.CopyFrom(&(stats.ss_perks));
		stats.level = CALL_MEMBER_FN(pc, GetLevel)();

		return true;
	}

	UInt16 GetSavedLevel()
	{
		return stats.level;
	}

	bool SaveProfile(std::string profile_name)
	{
		bool result = false;
		std::string profile_file = GetRuntimeDirectory();
		if (!profile_file.empty())
		{
			profile_file = "\\?\\" + profile_file + "Data\\SKSE\\Plugins\\SavePlayerData\\";
			auto n_err = CreateDirectoryW((LPCWSTR)profile_file.c_str(), NULL);
			result = GetLastError() == ERROR_ALREADY_EXISTS || n_err;
			if (!result) return false;
			
			profile_file = profile_file.erase(0, 3) + profile_name + ".dat";
			profile_stream.open(profile_file, std::ios::out | std::ios::trunc | std::ios::binary);
			result &= profile_stream.is_open();
			if (!result) return false;

			profile_stream << this;
		}

		return result;
	}

};