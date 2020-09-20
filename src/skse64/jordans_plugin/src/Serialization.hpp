#pragma once
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "skse64/GameExtraData.h"
#include "skse64/GameReferences.h"

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

namespace boost::serialization {

	template<class Archive, class T>
	void serialize(Archive& ar, tArray<T> t_arr, const unsigned int version)
	{
		ar& t_arr.capacity& t_arr.pad0C& t_arr.count& t_arr.pad14;

		t_arr.Resize(t_arr.capacity)
		
		for (int i = 0; i < t_arr.count; i++)
		{
			ar& t_arr[i];
		}

	}

	template<class Archive>
	void serialize(Archive& ar, BaseFormComponent* frm, const unsigned int version)
	{
		// ar.template register_type<TESForm>();
		// ar.register_type(static_cast<TESForm*>(NULL));
		// ar.template register_type <TESDescription>();
		// ar.register_type(static_cast<TESDescription*>(NULL));
		// ar.template register_type <TESFullName>();
		// ar.register_type(static_cast<TESFullName*>(NULL));
		// ar.template register_type <TESTexture>();
		// ar.register_type(static_cast<TESTexture*>(NULL));
		
	}

	template<class Archive>
	void serialize(Archive& ar, TESForm frm, const unsigned int version)
	{
		ar& boost::serialization::base_object<BaseFormComponent>(frm);
		// ar.template register_type<BGSPerk>;
		// ar.register_type(static_cast<BGSPerk *>(NULL));
		ar& frm.flags;
		ar& frm.formID;
		ar& frm.formType;
		ar& frm.kFlagIsDeleted;
		ar& frm.kFlagPlayerKnows;
		ar& frm.kFlagUnk_0x800;
		ar& frm.kTypeID;
		ar& frm.pad;
		ar& frm.pad1B;
		//ar& frm.unk08;
		ar& frm.unk18;
	}

	template<class Archive>
	void serialize(Archive& ar, BGSPerk prk, const unsigned int version)
	{
		ar& boost::serialization::base_object<TESForm>(prk);
		ar& prk.conditions;
		ar& prk.description;
		ar& prk.flags;
		ar& prk.formID;
		ar& prk.formType;
		ar& prk.fullName;
		ar& prk.icon;
		ar& prk.nextPerk;
		ar& prk.pad;
		ar& prk.pad1B;
		ar& prk.pad55;
		ar& prk.perkEntries;
		//ar& prk.unk08;
		ar& prk.unk18;
		ar& prk.unk30;
		ar& prk.unk31;
		ar& prk.unk32;
		ar& prk.unk33;
		ar& prk.unk34;
	}

	template<class Archive>
	void serialize(Archive& ar, Condition cnd, const unsigned int version)
	{
		ar& cnd.next;
		ar& cnd.compareValue;
		ar& cnd.unk0C;
		ar& cnd.unk10;
		ar& cnd.unk14;
		ar& cnd.functionId;
		ar& cnd.unk1A;
		ar& cnd.unk1B;
		ar& cnd.pad1C;
		ar& cnd.param1;
		ar& cnd.param2;
		ar& cnd.comparisonType;
		ar& cnd.referenceType;
		ar& cnd.pad32;
	}

	template<class Archive>
	void serialize(Archive& ar, TESDescription dsc, const unsigned int version)
	{
		ar& boost::serialization::base_object<BaseFormComponent>(dsc);
		ar& dsc.unk08;
		ar& dsc.unk0C;
	}

	template<class Archive>
	void serialize(Archive& ar, TESFullName n, const unsigned int version)
	{
		ar& boost::serialization::base_object<BaseFormComponent>(n);
		ar& n.name;
	}

	template<class Archive>
	void serialize(Archive& ar, TESTexture tex, const unsigned int version)
	{
		// ar.template register_type <TESIcon>();
		// ar.register_type(static_cast<TESIcon*>(NULL));

		ar& boost::serialization::base_object<BaseFormComponent>(tex);
		ar& tex.str;
	}

	template<class Archive>
	void serialize(Archive& ar, TESIcon ico, const unsigned int version)
	{
		ar& boost::serialization::base_object<TESTexture>(ico);
		ar& ico.str;
	}

	template<class Archive>
	void serialize(Archive& ar, BGSPerkEntry pe, const unsigned int version)
	{
		ar& pe.pad0C;
		ar& pe.priority;
		ar& pe.rank;
		ar& pe.unk0A;
	}

	template<class Archive>
	void serialize(Archive& ar, ActorValueOwner avo, const unsigned int version)
	{
		ar& avo;
	}
	
	
		

}