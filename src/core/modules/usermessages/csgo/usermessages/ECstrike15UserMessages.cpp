#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;


namespace bpl = boost::python;

void make_ECstrike15UserMessages_bindings()
{
    bpl::enum_<ECstrike15UserMessages> binder("ECstrike15UserMessages");
    binder.value("CS_UM_VGUIMenu", CS_UM_VGUIMenu);
    binder.value("CS_UM_Geiger", CS_UM_Geiger);
    binder.value("CS_UM_Train", CS_UM_Train);
    binder.value("CS_UM_HudText", CS_UM_HudText);
    binder.value("CS_UM_SayText", CS_UM_SayText);
    binder.value("CS_UM_SayText2", CS_UM_SayText2);
    binder.value("CS_UM_TextMsg", CS_UM_TextMsg);
    binder.value("CS_UM_HudMsg", CS_UM_HudMsg);
    binder.value("CS_UM_ResetHud", CS_UM_ResetHud);
    binder.value("CS_UM_GameTitle", CS_UM_GameTitle);
    binder.value("CS_UM_Shake", CS_UM_Shake);
    binder.value("CS_UM_Fade", CS_UM_Fade);
    binder.value("CS_UM_Rumble", CS_UM_Rumble);
    binder.value("CS_UM_CloseCaption", CS_UM_CloseCaption);
    binder.value("CS_UM_CloseCaptionDirect", CS_UM_CloseCaptionDirect);
    binder.value("CS_UM_SendAudio", CS_UM_SendAudio);
    binder.value("CS_UM_RawAudio", CS_UM_RawAudio);
    binder.value("CS_UM_VoiceMask", CS_UM_VoiceMask);
    binder.value("CS_UM_RequestState", CS_UM_RequestState);
    binder.value("CS_UM_Damage", CS_UM_Damage);
    binder.value("CS_UM_RadioText", CS_UM_RadioText);
    binder.value("CS_UM_HintText", CS_UM_HintText);
    binder.value("CS_UM_KeyHintText", CS_UM_KeyHintText);
    binder.value("CS_UM_ProcessSpottedEntityUpdate", CS_UM_ProcessSpottedEntityUpdate);
    binder.value("CS_UM_ReloadEffect", CS_UM_ReloadEffect);
    binder.value("CS_UM_AdjustMoney", CS_UM_AdjustMoney);
    binder.value("CS_UM_UpdateTeamMoney", CS_UM_UpdateTeamMoney);
    binder.value("CS_UM_StopSpectatorMode", CS_UM_StopSpectatorMode);
    binder.value("CS_UM_KillCam", CS_UM_KillCam);
    binder.value("CS_UM_DesiredTimescale", CS_UM_DesiredTimescale);
    binder.value("CS_UM_CurrentTimescale", CS_UM_CurrentTimescale);
    binder.value("CS_UM_AchievementEvent", CS_UM_AchievementEvent);
    binder.value("CS_UM_MatchEndConditions", CS_UM_MatchEndConditions);
    binder.value("CS_UM_DisconnectToLobby", CS_UM_DisconnectToLobby);
    binder.value("CS_UM_PlayerStatsUpdate", CS_UM_PlayerStatsUpdate);
    binder.value("CS_UM_DisplayInventory", CS_UM_DisplayInventory);
    binder.value("CS_UM_WarmupHasEnded", CS_UM_WarmupHasEnded);
    binder.value("CS_UM_ClientInfo", CS_UM_ClientInfo);
    binder.value("CS_UM_XRankGet", CS_UM_XRankGet);
    binder.value("CS_UM_XRankUpd", CS_UM_XRankUpd);
    binder.value("CS_UM_SetPlayerEloDisplayBracket", CS_UM_SetPlayerEloDisplayBracket);
    binder.value("CS_UM_RequestEloBracketInfo", CS_UM_RequestEloBracketInfo);
    binder.value("CS_UM_SetEloBracketInfo", CS_UM_SetEloBracketInfo);
    binder.value("CS_UM_CallVoteFailed", CS_UM_CallVoteFailed);
    binder.value("CS_UM_VoteStart", CS_UM_VoteStart);
    binder.value("CS_UM_VotePass", CS_UM_VotePass);
    binder.value("CS_UM_VoteFailed", CS_UM_VoteFailed);
    binder.value("CS_UM_VoteSetup", CS_UM_VoteSetup);
    binder.value("CS_UM_ServerRankRevealAll", CS_UM_ServerRankRevealAll);
    binder.value("CS_UM_SendLastKillerDamageToClient", CS_UM_SendLastKillerDamageToClient);
    binder.value("CS_UM_ServerRankUpdate", CS_UM_ServerRankUpdate);
    binder.value("CS_UM_ItemPickup", CS_UM_ItemPickup);
    binder.value("CS_UM_ShowMenu", CS_UM_ShowMenu);
    binder.value("CS_UM_BarTime", CS_UM_BarTime);
    binder.value("CS_UM_AmmoDenied", CS_UM_AmmoDenied);
    binder.value("CS_UM_MarkAchievement", CS_UM_MarkAchievement);
    binder.value("CS_UM_MatchStatsUpdate", CS_UM_MatchStatsUpdate);
    binder.value("CS_UM_ItemDrop", CS_UM_ItemDrop);
;
}
