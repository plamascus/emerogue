Rogue_Boss_6_MapScripts::
	.byte 0


Rogue_Battle_Boss6::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, PlayerToBattleFieldBoss6
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CameraToBattleFieldBoss6
	waitmovement 0
	msgbox Rogue_Battle_Boss6_Text_0
	applymovement OBJ_EVENT_ID_PLAYER, PlayerToFightBoss6
	applymovement 6, BossLizaToFightBoss6
	applymovement 5, BossTateToFightBoss6
	waitmovement 0
	trainerbattle_single TRAINER_TATE_AND_LIZA_1, Rogue_Battle_Boss6_Text_1, Rogue_Battle_Boss6_Text_2, Rogue_BattleDefeated_Boss6
	return


Rogue_BattleDefeated_Boss6::
	message Rogue_BattleDefeated_Boss6_Text_0
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE02_GET
	setflag FLAG_ROGUE_DEFEATED_LIZA
	msgbox Rogue_BattleDefeated_Boss6_Text_1
	waitmessage
	special RemoveCameraObject
	warp MAP_ROGUE_HUB_TRANSITION, 0
	return


PlayerToBattleFieldBoss6:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

CameraToBattleFieldBoss6:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

PlayerToFightBoss6:
	walk_right
	face_right
	step_end

BossTateToFightBoss6:
	walk_left
	walk_down
	face_left
	step_end

BossLizaToFightBoss6:
	walk_left
	walk_up
	face_left
	step_end

Rogue_Battle_Boss6_Text_0:
	.string "LIZA: Look TATE!\n"
	.string "A new challenger!$"

Rogue_Battle_Boss6_Text_1:
	.string "TATE: Don't hold back now!$"

Rogue_Battle_Boss6_Text_2:
	.string "Well fought trainer!$"

Rogue_BattleDefeated_Boss6_Text_0:
	.string "{PLAYER} received the ?? BADGE!$"

Rogue_BattleDefeated_Boss6_Text_1:
	.string "Good luck in your future battles!$"