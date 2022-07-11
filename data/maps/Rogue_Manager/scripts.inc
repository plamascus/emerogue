Rogue_Manager_MapScripts::
	.byte 0


Rogue_PostBattle_Internal::
	msgbox Rogue_PostBattle_Internal_Text_0, MSGBOX_AUTOCLOSE
	return


Rogue_GiveItem_Internal::
	finditem VAR_0x8000, 3
	return


Rogue_Battle_BreederF::
	trainerbattle_single TRAINER_ROGUE_BREEDER_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_BreederM::
	trainerbattle_single TRAINER_ROGUE_BREEDER_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_RichF::
	trainerbattle_single TRAINER_ROGUE_RICH_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_RichM::
	trainerbattle_single TRAINER_ROGUE_RICH_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_CooltrainerF::
	trainerbattle_single TRAINER_ROGUE_COOLTRAINER_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_CooltrainerM::
	trainerbattle_single TRAINER_ROGUE_COOLTRAINER_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_PokefanF::
	trainerbattle_single TRAINER_ROGUE_POKEFAN_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_PokefanM::
	trainerbattle_single TRAINER_ROGUE_POKEFAN_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_SchoolkidF::
	trainerbattle_single TRAINER_ROGUE_SCHOOL_KID_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_SchoolkidM::
	trainerbattle_single TRAINER_ROGUE_SCHOOL_KID_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_TuberF::
	trainerbattle_single TRAINER_ROGUE_TUBER_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_TuberM::
	trainerbattle_single TRAINER_ROGUE_TUBER_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_PoshF::
	trainerbattle_single TRAINER_ROGUE_POSH_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_PoshM::
	trainerbattle_single TRAINER_ROGUE_POSH_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_MagmaF::
	trainerbattle_single TRAINER_ROGUE_MAGMA_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_MagmaM::
	trainerbattle_single TRAINER_ROGUE_MAGMA_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_AquaF::
	trainerbattle_single TRAINER_ROGUE_AQUA_F, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Battle_AquaM::
	trainerbattle_single TRAINER_ROGUE_AQUA_M, Rogue_Battle_BreederF_Text_0, Rogue_Battle_BreederF_Text_1
	call Rogue_PostBattle_Internal
	return


Rogue_Give_Item0::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM0
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item1::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM1
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item2::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM2
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item3::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM3
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item4::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM4
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item5::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM5
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item6::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM6
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item7::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM7
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item8::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM8
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item9::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM9
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item10::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM10
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item11::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM11
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item12::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM12
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item13::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM13
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item14::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM14
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item15::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM15
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item16::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM16
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item17::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM17
	call Rogue_GiveItem_Internal
	return


Rogue_Give_Item18::
	copyvar VAR_0x8000, VAR_ROGUE_ITEM18
	call Rogue_GiveItem_Internal
	return


Rogue_PostBattle_Internal_Text_0:
	.string "Good luck with your next battle!$"

Rogue_Battle_BreederF_Text_0:
	.string "Let's battle!$"

Rogue_Battle_BreederF_Text_1:
	.string "Well fought!$"