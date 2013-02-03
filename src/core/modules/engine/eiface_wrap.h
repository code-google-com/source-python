/**
* =============================================================================
* Source Python
* Copyright (C) 2012 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/
#ifndef _EIFACE_WRAP_H
#define _EIFACE_WRAP_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "eiface.h"

//---------------------------------------------------------------------------------
// Global externs we need.
//---------------------------------------------------------------------------------
extern IVEngineServer* engine;

//---------------------------------------------------------------------------------
// Purpose: Interface the engine exposes to the game DLL
//---------------------------------------------------------------------------------
class CEngineServer
{
public:
	virtual void change_level( const char *s1, const char *s2 ) {
		engine->ChangeLevel(s1, s2);
	}

	virtual int	is_map_valid( const char *filename ) {
		return engine->IsMapValid( filename );
	}

	virtual bool is_dedicated_server( void ) {
		return engine->IsDedicatedServer();
	}

	virtual int	is_in_edit_mode( void ) {
		return engine->IsInEditMode();
	}

	virtual KeyValues* get_launch_options( void ) {
		return engine->GetLaunchOptions();
	}

	virtual int	precache_model( const char *s, bool preload = false ) {
		return engine->PrecacheModel(s, preload);
	}

	virtual int	precache_sentence_file( const char *s, bool preload = false ) {
		return engine->PrecacheSentenceFile(s, preload);
	}

	virtual int	precache_decal( const char *name, bool preload = false ) {
		return engine->PrecacheDecal(name, preload);
	}

	virtual int	precache_generic( const char *s, bool preload = false ) {
		return engine->PrecacheGeneric(s, preload);
	}

	virtual bool is_model_precached( char const *s ) const {
		return engine->IsModelPrecached(s);
	}

	virtual bool is_decal_precached( char const *s ) const {
		return engine->IsDecalPrecached(s);
	}

	virtual bool is_generic_precached( char const *s ) const {
		return engine->IsGenericPrecached(s);
	}

	virtual int	get_cluster_for_origin( const Vector &org ) {
		return engine->GetClusterForOrigin(org);
	}

	virtual int	get_pvs_for_cluster( int cluster, int outputpvslength, unsigned char *outputpvs ) {
		return engine->GetPVSForCluster(cluster, outputpvslength, outputpvs);
	}

	virtual bool check_origin_in_pvs( const Vector &org, const unsigned char *checkpvs, int checkpvssize ) {
		return engine->CheckOriginInPVS(org, checkpvs, checkpvssize);
	}

	virtual bool check_box_in_pvs( const Vector &mins, const Vector &maxs, const unsigned char *checkpvs, int checkpvssize ) {
		return engine->CheckBoxInPVS(mins, maxs, checkpvs, checkpvssize);
	}

	virtual int	get_player_userid( const edict_t *e ) {
		return engine->GetPlayerUserId(e);
	}

	virtual const char* get_player_network_id_string( const edict_t *e ) {
		return engine->GetPlayerNetworkIDString(e);
	}

	virtual bool is_userid_in_user( int userID ) {
		return engine->IsUserIDInUse(userID);
	}

	virtual int get_loading_progress_for_userid( int userID ) {
		return engine->GetLoadingProgressForUserID(userID);
	}

	virtual int get_entity_count( void ) {
		return engine->GetEntityCount();
	}

	virtual INetChannelInfo* get_player_net_info( int playerIndex ) {
		return engine->GetPlayerNetInfo(playerIndex);
	}

	virtual edict_t	*create_edict( int iForceEdictIndex = -1 ) {
		return engine->CreateEdict(iForceEdictIndex);
	}

	virtual void remove_edict( edict_t *e ) {
		engine->RemoveEdict(e);
	}

	// Memory allocation for entity class data
	virtual void* pv_alloc_ent_private_data( long cb ) {
		return engine->PvAllocEntPrivateData(cb);
	}

	virtual void  free_ent_private_data( void *pEntity ) {
		engine->FreeEntPrivateData(pEntity);
	}

	virtual void *save_alloc_memory( size_t num, size_t size ) {
		return engine->SaveAllocMemory(num, size);
	}

	virtual void save_free_memory( void *pSaveMem ) {
		engine->SaveFreeMemory(pSaveMem);
	}

	virtual void emit_ambient_sound( int entindex, const Vector &pos, const char *samp, float vol, soundlevel_t soundlevel, int fFlags, int pitch, float delay = 0.0f ) {
		engine->EmitAmbientSound(entindex, pos, samp, vol, soundlevel, fFlags, pitch, delay);
	}

	virtual void fade_client_volume( const edict_t *pEdict, float fadePercent, float fadeOutSeconds, float holdTime, float fadeInSeconds ) {
		engine->FadeClientVolume(pEdict, fadePercent, fadeOutSeconds, holdTime, fadeInSeconds);
	}

	virtual int	sentence_group_pick( int groupIndex, char *name, int nameBufLen ) {
		return engine->SentenceGroupPick(groupIndex, name, nameBufLen);
	}

	virtual int	sentence_group_pick_sequential( int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset ) {
		return engine->SentenceGroupPickSequential(groupIndex, name, nameBufLen, sentenceIndex, reset);
	}

	virtual int	sentence_index_from_name( const char *pSentenceName ) {
		return engine->SentenceIndexFromName(pSentenceName);
	}

	virtual const char *sentence_name_from_index( int sentenceIndex ) {
		return engine->SentenceNameFromIndex(sentenceIndex);
	}

	virtual int	sentence_group_index_from_name( const char *pGroupName ) {
		return engine->SentenceGroupIndexFromName(pGroupName);
	}

	virtual const char *sentence_group_name_from_index( int groupIndex ) {
		return engine->SentenceGroupNameFromIndex(groupIndex);
	}
	
	virtual float sentence_length( int sentenceIndex ) {
		return engine->SentenceLength(sentenceIndex);
	}

	virtual void server_command( const char *str ) {
		engine->ServerCommand(str);
	}

	virtual void server_execute( void ) {
		engine->ServerExecute();
	}

	/**
	 * TODO: Look into figuring out variadic passing?
	 */
	virtual void client_command( edict_t *pEdict, const char *szCommand ) {
		engine->ClientCommand(pEdict, szCommand);
	}

	virtual void light_style( int style, const char *val ) {
		engine->LightStyle(style, val);
	}

	virtual void static_decal( const Vector &originInEntitySpace, int decalIndex, int entityIndex, int modelIndex, bool lowpriority ) {
		engine->StaticDecal(originInEntitySpace, decalIndex, entityIndex, modelIndex, lowpriority);
	}

	virtual void message_determine_multicast_recipients( bool usepas, const Vector& origin, CPlayerBitVec& playerbits ) {
		engine->Message_DetermineMulticastRecipients(usepas, origin, playerbits);
	}

	virtual bf_write* entity_message_begin( int ent_index, ServerClass * ent_class, bool reliable ) {
		return engine->EntityMessageBegin(ent_index, ent_class, reliable);
	}

	virtual void message_end( void ) {
		engine->MessageEnd();
	}

	virtual void send_user_message( IRecipientFilter &filter, int message, const google::protobuf::Message &msg ) {
		engine->SendUserMessage(filter, message, msg);
	}
	
	virtual void client_printf( edict_t *pEdict, const char *szMsg ) {
		engine->ClientPrintf(pEdict, szMsg);
	}

	virtual void con_nprintf( int pos, const char* szString ) {
		engine->Con_NPrintf(pos, szString);
	}

	virtual void con_nxprintf( const struct con_nprint_s *info, const char* szString ) {
		engine->Con_NXPrintf(info, szString);
	}

	virtual void set_view( const edict_t *pClient, const edict_t *pViewent ) {
		engine->SetView(pClient, pViewent);
	}

	virtual void crosshair_angle( const edict_t *pClient, float pitch, float yaw ) {
		engine->CrosshairAngle(pClient, pitch, yaw);
	}

	/**
	 * Python managed return type!
	 */
	virtual char* get_game_dir( int maxlength ) {
		char* szGetGameDir = new char[maxlength];
		engine->GetGameDir(szGetGameDir, maxlength);
		return szGetGameDir;
	}


	virtual int compare_file_time( const char *filename1, const char *filename2, int *iCompare ) {
		return engine->CompareFileTime(filename1, filename2, iCompare);
	}

	virtual bool lock_network_string_tables( bool lock ) {
		return engine->LockNetworkStringTables(lock);
	}

	virtual edict_t* create_fake_client( const char *netname ) {
		return engine->CreateFakeClient(netname);
	}

	virtual const char* get_client_convar_value( int clientIndex, const char *name ) {
		return engine->GetClientConVarValue(clientIndex, name);
	}

	virtual const char* parse_file( const char *data, char *token, int maxlen ) {
		return engine->ParseFile(data, token, maxlen);
	}

	virtual bool copy_file( const char *source, const char *destination ) {
		return engine->CopyFile(source, destination);
	}


	virtual void reset_pvs( byte *pvs, int pvssize ) {
		engine->ResetPVS(pvs, pvssize);
	}

	virtual void add_origin_to_pvs( const Vector &origin ) {
		engine->AddOriginToPVS(origin);
	}


	virtual void set_area_portal_state( int portalNumber, int isOpen ) {
		engine->SetAreaPortalState(portalNumber, isOpen);
	}

	virtual void playback_temp_entity( IRecipientFilter& filter, float delay, const void *pSender, const SendTable *pST, int classID  ) {
		engine->PlaybackTempEntity(filter, delay, pSender, pST, classID);
	}
	
	virtual int check_head_node_visible( int nodenum, const byte *pvs, int vissize ) {
		return engine->CheckHeadnodeVisible(nodenum, pvs, vissize);
	}

	virtual int	check_areas_connected( int area1, int area2 ) {
		return engine->CheckAreasConnected(area1, area2);
	}
	
	virtual int	get_area( const Vector &origin ) {
		return engine->GetArea(origin);
	}

	virtual void get_area_bits( int area, unsigned char *bits, int buflen ) {
		engine->GetAreaBits(area, bits, buflen);
	}

	virtual bool get_area_portal_plane( Vector const &vViewOrigin, int portalKey, VPlane *pPlane ) {
		return engine->GetAreaPortalPlane(vViewOrigin, portalKey, pPlane);
	}

	virtual bool load_game_state( char const *pMapName, bool createPlayers ) {
		return engine->LoadGameState(pMapName, createPlayers);
	}

	virtual void load_adjacent_ents( const char *pOldLevel, const char *pLandmarkName ) {
		engine->LoadAdjacentEnts(pOldLevel, pLandmarkName);
	}

	virtual void clear_save_dir() {
		engine->ClearSaveDir();
	}

	virtual const char*	get_map_entities_string() {
		return engine->GetMapEntitiesString();
	}

	virtual client_textmessage_t *text_message_get( const char *pName ) {
		return engine->TextMessageGet(pName);
	}

	virtual void log_print( const char *msg ) {
		engine->LogPrint(msg);
	}

	virtual bool is_log_enabled() {
		return engine->IsLogEnabled();
	}

	virtual void build_entity_cluster_list( edict_t *pEdict, PVSInfo_t *pPVSInfo ) {
		engine->BuildEntityClusterList(pEdict, pPVSInfo);
	}

	virtual void solid_moved( edict_t *pSolidEnt, ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin, bool testSurroundingBoundsOnly ) {
		engine->SolidMoved(pSolidEnt, pSolidCollide, pPrevAbsOrigin, testSurroundingBoundsOnly);
	}

	virtual void trigger_moved( edict_t *pTriggerEnt, bool testSurroundingBoundsOnly ) {
		engine->TriggerMoved(pTriggerEnt, testSurroundingBoundsOnly);
	}

	virtual ISpatialPartition *create_spatial_partition( const Vector& worldmin, const Vector& worldmax ) {
		return engine->CreateSpatialPartition(worldmin, worldmax);
	}

	virtual void destroy_spatial_partition( ISpatialPartition *partition ) {
		engine->DestroySpatialPartition( partition );
	}

	virtual void draw_map_to_scratch_pad( IScratchPad3D *pPad, unsigned long iFlags ) {
		engine->DrawMapToScratchPad(pPad, iFlags);
	}

	virtual const CBitVec<MAX_EDICTS>* get_entity_transmit_bits_for_client( int iClientIndex ) {
		return engine->GetEntityTransmitBitsForClient(iClientIndex);
	}

	virtual bool  is_paused() {
		return engine->IsPaused();
	}

	virtual float get_timescale() const {
		return engine->GetTimescale();
	}

	virtual void  force_exact_file( const char *s ) {
		engine->ForceExactFile(s);
	}

	virtual void  force_model_bounds( const char *s, const Vector &mins, const Vector &maxs ) {
		engine->ForceModelBounds(s, mins, maxs);
	}

	virtual void  clear_save_dir_after_client_load() {
		engine->ClearSaveDirAfterClientLoad();
	}

	virtual void  set_fake_client_convar_value( edict_t *pEntity, const char *cvar, const char *value ) {
		engine->SetFakeClientConVarValue(pEntity, cvar, value);
	}

	virtual void  force_simple_material( const char *s ) {
		engine->ForceSimpleMaterial(s);
	}

	virtual int   is_in_commentary_mode() {
		return engine->IsInCommentaryMode();
	}

	virtual bool  is_level_main_menu_background() {
		return engine->IsLevelMainMenuBackground();
	}

	virtual void  set_area_portal_states( const int *portalNumbers, const int *isOpen, int nPortals ) {
		engine->SetAreaPortalStates(portalNumbers, isOpen, nPortals);
	}

	virtual void  notify_edict_flags_change( int iEdict ) {
		engine->NotifyEdictFlagsChange(iEdict);
	}

	virtual const CCheckTransmitInfo* get_prev_check_transmit_info( edict_t *pPlayerEdict ) {
		return engine->GetPrevCheckTransmitInfo(pPlayerEdict);
	}

	virtual CSharedEdictChangeInfo* get_shared_edict_change_info() {
		return engine->GetSharedEdictChangeInfo();
	}

	virtual void   allow_immediate_edict_reuse() {
		engine->AllowImmediateEdictReuse();
	}

	virtual bool  is_internal_build() {
		return engine->IsInternalBuild();
	}

	virtual IChangeInfoAccessor *get_change_accessor( const edict_t *pEdict ) {
		return engine->GetChangeAccessor(pEdict);
	}

	virtual char const *get_most_recently_loaded_file_name() {
		return engine->GetMostRecentlyLoadedFileName();
	}

	virtual char const *get_save_file_name() {
		return engine->GetSaveFileName();
	}

	virtual void clean_up_entity_cluster_list( PVSInfo_t *pPVSInfo ) {
		engine->CleanUpEntityClusterList(pPVSInfo);
	}

	virtual void set_achievement_mgr( IAchievementMgr* mgr ) {
		engine->SetAchievementMgr(mgr);
	}

	virtual IAchievementMgr* get_achievement_mgr() {
		return engine->GetAchievementMgr();
	}

	virtual int     get_app_id() {
		return engine->GetAppID();
	}

	virtual bool is_low_violence() {
		return engine->IsLowViolence();
	}

	virtual bool is_any_client_low_violence() {
		return engine->IsAnyClientLowViolence();
	}

	virtual QueryCvarCookie_t start_query_cvar_value( edict_t *pPlayerEntity, const char *pName ) {
		return engine->StartQueryCvarValue(pPlayerEntity, pName);
	}

	virtual void insert_server_command( const char *str ) {
		engine->InsertServerCommand(str);
	}

	virtual bool get_player_info( int ent_num, player_info_t *pinfo ) {
		return engine->GetPlayerInfo(ent_num, pinfo);
	}

	virtual bool is_client_fully_authenticated( edict_t *pEdict ) {
		return engine->IsClientFullyAuthenticated(pEdict);
	}

	virtual void set_dedicated_server_benchmark_mode( bool bBenchmarkMode ) {
		engine->SetDedicatedServerBenchmarkMode(bBenchmarkMode);
	}

	virtual bool is_split_screen_player( int ent_num ) {
		return engine->IsSplitScreenPlayer(ent_num);
	}

	virtual edict_t *get_split_screen_player_attach_to_edict( int ent_num ) {
		return engine->GetSplitScreenPlayerAttachToEdict(ent_num);
	}

	virtual int     get_num_split_screen_users_attached_to_edict( int ent_num ) {
		return engine->GetNumSplitScreenUsersAttachedToEdict(ent_num);
	}

	virtual edict_t *get_split_screen_player_for_edict( int ent_num, int nSlot ) {
		return engine->GetSplitScreenPlayerForEdict(ent_num, nSlot);
	}

	virtual bool is_override_load_game_ents_on() {
		return engine->IsOverrideLoadGameEntsOn();
	}

	virtual void force_flush_entity( int iEntity ) {
		engine->ForceFlushEntity(iEntity);
	}

	virtual ISPSharedMemory *get_single_player_shared_memory_space( const char *szName, int ent_num = MAX_EDICTS ) {
		return engine->GetSinglePlayerSharedMemorySpace(szName, ent_num);
	}

	virtual void *alloc_level_static_data( size_t bytes ) {
		engine->AllocLevelStaticData(bytes);
	}

	virtual int get_cluster_count() {
		return engine->GetClusterCount();
	}

	virtual int get_all_cluster_bounds( bbox_t *pBBoxList, int maxBBox ) {
		return engine->GetAllClusterBounds(pBBoxList, maxBBox);
	}

	virtual bool is_creating_reslist() {
		return engine->IsCreatingReslist();
	}

	virtual bool is_creating_xbox_reslist() {
		return engine->IsCreatingXboxReslist();
	}

	virtual bool is_dedicated_server_for_xbox() {
		return engine->IsDedicatedServerForXbox();
	}

	virtual bool is_dedicated_server_for_ps3() {
		return engine->IsDedicatedServerForPS3();
	}

	virtual void pause( bool bPause, bool bForce = false ) {
		engine->Pause(bPause, bForce);
	}

	virtual void set_timescale( float flTimescale ) {
		engine->SetTimescale(flTimescale);
	}

	virtual void set_gamestats_data( CGamestatsData *pGamestatsData ) {
		engine->SetGamestatsData(pGamestatsData);
	}

	virtual CGamestatsData *get_gamestats_data() {
		return engine->GetGamestatsData();
	}

	virtual const CSteamID  *get_client_steamid( edict_t *pPlayerEdict ) {
		return engine->GetClientSteamID(pPlayerEdict);
	}

	virtual const CSteamID  *get_game_server_steamid() {
		return engine->GetGameServerSteamID();
	}

	virtual void host_validate_session() {
		engine->HostValidateSession();
	}

	virtual void refresh_screen_if_necessary() {
		engine->RefreshScreenIfNecessary();
	}

	virtual bool has_paintmap() {
		return engine->HasPaintmap();
	}

	virtual bool sphere_paint_surface( const model_t *pModel, const Vector & vPosition, unsigned char color, float flSphereRadius, float flPaintCoatPercent) {
		return engine->SpherePaintSurface(pModel, vPosition, color, flSphereRadius, flPaintCoatPercent);
	}

	virtual void sphere_trace_paint_surface( const model_t *pModel, const Vector & vPosition, const Vector & vContactNormal, float flSphereRadius, CUtlVector<unsigned char> & surfColors ) {
		engine->SphereTracePaintSurface(pModel, vPosition, vContactNormal, flSphereRadius, surfColors);
	}

	virtual void remove_all_paint() {
		engine->RemoveAllPaint();
	}

	virtual void paint_all_surfaces( unsigned char color) {
		engine->PaintAllSurfaces(color);
	}

	virtual void remove_paint( const model_t *pModel ) {
		engine->RemovePaint(pModel);
	}

	virtual void client_command_key_values( edict_t *pEdict, KeyValues *pCommand ) {
		engine->ClientCommandKeyValues(pEdict, pCommand);
	}

	virtual uint64 get_client_xuid( edict_t *pPlayerEdict ) {
		return engine->GetClientXUID(pPlayerEdict);
	}

	virtual bool is_active_app() {
		return engine->IsActiveApp();
	}

	virtual void set_no_clip_enabled( bool bEnabled ) {
		engine->SetNoClipEnabled(bEnabled);
	}

	virtual void get_paint_map_data_rle( CUtlVector<unsigned int> &mapdata ) {
		engine->GetPaintmapDataRLE(mapdata);
	}

	virtual void load_paint_map_data_rle( CUtlVector<unsigned int> &mapdata ) {
		engine->LoadPaintmapDataRLE(mapdata);
	}

	virtual void send_paint_map_data_to_client( edict_t *pEdict ) {
		engine->SendPaintmapDataToClient(pEdict);
	}

	virtual float get_latency_for_choreo_sounds() {
		return engine->GetLatencyForChoreoSounds();
	}

	virtual int get_client_cross_play_platform( int client_index ) {
		return engine->GetClientCrossPlayPlatform(client_index);
	}

	virtual void ensure_instance_baseline( int ent_num) {
		engine->EnsureInstanceBaseline(ent_num);
	}

	virtual bool reserver_server_for_queued_game( const char *szReservationPayload ) {
		return engine->ReserveServerForQueuedGame(szReservationPayload);
	}
};

#endif