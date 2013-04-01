//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "stringregistry.h"
#include "ai_basenpc.h"
#include "ai_condition.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Given and condition name, return the condition ID
//-----------------------------------------------------------------------------
int CAI_BaseNPC::GetConditionID(const char* condName)
{
	return GetSchedulingSymbols()->ConditionSymbolToId(condName);
}

//-----------------------------------------------------------------------------
// Purpose: Register the default conditions
// Input  :
// Output :
//-----------------------------------------------------------------------------

#define ADD_CONDITION_TO_SR( _n ) idSpace.AddCondition( #_n, _n, "CAI_BaseNPC" )

void	CAI_BaseNPC::InitDefaultConditionSR(void)
{
	CAI_ClassScheduleIdSpace &idSpace = CAI_BaseNPC::AccessClassScheduleIdSpaceDirect();

	ADD_CONDITION_TO_SR( COND_NONE );
	ADD_CONDITION_TO_SR( COND_IN_PVS );
	ADD_CONDITION_TO_SR( COND_IDLE_INTERRUPT );
	ADD_CONDITION_TO_SR( COND_LOW_PRIMARY_AMMO );
	ADD_CONDITION_TO_SR( COND_NO_PRIMARY_AMMO );
	ADD_CONDITION_TO_SR( COND_NO_SECONDARY_AMMO );
	ADD_CONDITION_TO_SR( COND_NO_WEAPON );
	ADD_CONDITION_TO_SR( COND_SEE_HATE );
	ADD_CONDITION_TO_SR( COND_SEE_FEAR );
	ADD_CONDITION_TO_SR( COND_SEE_DISLIKE );
	ADD_CONDITION_TO_SR( COND_SEE_ENEMY );
	ADD_CONDITION_TO_SR( COND_LOST_ENEMY );
	ADD_CONDITION_TO_SR( COND_ENEMY_WENT_NULL );
	ADD_CONDITION_TO_SR( COND_HAVE_ENEMY_LOS );
	ADD_CONDITION_TO_SR( COND_HAVE_TARGET_LOS );
	ADD_CONDITION_TO_SR( COND_ENEMY_OCCLUDED );
	ADD_CONDITION_TO_SR( COND_TARGET_OCCLUDED );
	ADD_CONDITION_TO_SR( COND_ENEMY_TOO_FAR );
	ADD_CONDITION_TO_SR( COND_LIGHT_DAMAGE );
	ADD_CONDITION_TO_SR( COND_HEAVY_DAMAGE );
	ADD_CONDITION_TO_SR( COND_PHYSICS_DAMAGE );
	ADD_CONDITION_TO_SR( COND_REPEATED_DAMAGE );
	ADD_CONDITION_TO_SR( COND_CAN_RANGE_ATTACK1 );
	ADD_CONDITION_TO_SR( COND_CAN_RANGE_ATTACK2 );
	ADD_CONDITION_TO_SR( COND_CAN_MELEE_ATTACK1 );
	ADD_CONDITION_TO_SR( COND_CAN_MELEE_ATTACK2 );
	ADD_CONDITION_TO_SR( COND_PROVOKED );
	ADD_CONDITION_TO_SR( COND_NEW_ENEMY );
	ADD_CONDITION_TO_SR( COND_ENEMY_FACING_ME );
	ADD_CONDITION_TO_SR( COND_BEHIND_ENEMY );
	ADD_CONDITION_TO_SR( COND_ENEMY_DEAD );
	ADD_CONDITION_TO_SR( COND_ENEMY_UNREACHABLE );
	ADD_CONDITION_TO_SR( COND_SEE_PLAYER );
	ADD_CONDITION_TO_SR( COND_LOST_PLAYER );
	ADD_CONDITION_TO_SR( COND_SEE_NEMESIS );
	ADD_CONDITION_TO_SR( COND_TASK_FAILED );
	ADD_CONDITION_TO_SR( COND_SCHEDULE_DONE );
	ADD_CONDITION_TO_SR( COND_SMELL );
	ADD_CONDITION_TO_SR( COND_TOO_CLOSE_TO_ATTACK );
	ADD_CONDITION_TO_SR( COND_TOO_FAR_TO_ATTACK );
	ADD_CONDITION_TO_SR( COND_NOT_FACING_ATTACK );
	ADD_CONDITION_TO_SR( COND_WEAPON_HAS_LOS );
	ADD_CONDITION_TO_SR( COND_WEAPON_BLOCKED_BY_FRIEND );			// Friend between gun and target
	ADD_CONDITION_TO_SR( COND_WEAPON_PLAYER_IN_SPREAD );		// Player in shooting direction
	ADD_CONDITION_TO_SR( COND_WEAPON_PLAYER_NEAR_TARGET );	// Player near shooting position
	ADD_CONDITION_TO_SR( COND_WEAPON_SIGHT_OCCLUDED );
	ADD_CONDITION_TO_SR( COND_BETTER_WEAPON_AVAILABLE );
	ADD_CONDITION_TO_SR( COND_HEALTH_ITEM_AVAILABLE );
	ADD_CONDITION_TO_SR( COND_FLOATING_OFF_GROUND );
	ADD_CONDITION_TO_SR( COND_MOBBED_BY_ENEMIES );
	ADD_CONDITION_TO_SR( COND_GIVE_WAY );
	ADD_CONDITION_TO_SR( COND_WAY_CLEAR );
	ADD_CONDITION_TO_SR( COND_HEAR_DANGER );
	ADD_CONDITION_TO_SR( COND_HEAR_THUMPER );
	ADD_CONDITION_TO_SR( COND_HEAR_COMBAT );
	ADD_CONDITION_TO_SR( COND_HEAR_WORLD );
	ADD_CONDITION_TO_SR( COND_HEAR_PLAYER );
	ADD_CONDITION_TO_SR( COND_HEAR_BULLET_IMPACT );
	ADD_CONDITION_TO_SR( COND_HEAR_BUGBAIT );
	ADD_CONDITION_TO_SR( COND_HEAR_PHYSICS_DANGER );
	ADD_CONDITION_TO_SR( COND_HEAR_MOVE_AWAY );
	ADD_CONDITION_TO_SR( COND_NO_HEAR_DANGER );
	ADD_CONDITION_TO_SR( COND_PLAYER_PUSHING );
	ADD_CONDITION_TO_SR( COND_RECEIVED_ORDERS );
	ADD_CONDITION_TO_SR( COND_PLAYER_ADDED_TO_SQUAD );
	ADD_CONDITION_TO_SR( COND_PLAYER_REMOVED_FROM_SQUAD );
	ADD_CONDITION_TO_SR( COND_NPC_FREEZE );
	ADD_CONDITION_TO_SR( COND_NPC_UNFREEZE );
	ADD_CONDITION_TO_SR( COND_TALKER_RESPOND_TO_QUESTION );
	ADD_CONDITION_TO_SR( COND_NO_CUSTOM_INTERRUPTS );
	ADD_CONDITION_TO_SR( COND_BEHAVIOR_PARAMETERS_CHANGED );
}
