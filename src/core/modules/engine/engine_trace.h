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
#ifndef _ENGINE_TRACE_H
#define _ENGINE_TRACE_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "engine/IEngineTrace.h"
#include "gametrace.h"
#include "iserverunknown.h"

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IEngineTrace* enginetrace;

//---------------------------------------------------------------------------------
// Wraps Ray_t.
// Q: Why is this wrapped?
// A: Ray_t can't be directly exposed to Boost.Python, as some of its member
//    variables use the VectorAligned type, which is specially defined using
//	  ALIGN16.
//---------------------------------------------------------------------------------
struct WrappedRay_t
{
	WrappedRay_t();
	~WrappedRay_t();

	void Init(Vector const& start, Vector const& end);
	void Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs);

	Vector InvDelta() const;

	Ray_t* WrappedInstance() const;

private:
	Ray_t* m_pWrappedRay;
};

//---------------------------------------------------------------------------------
// A simple entity collection class, allows for using functions like
// GetPointContents.
//---------------------------------------------------------------------------------
class EntityCollection
{
public:
	EntityCollection(int iMaxCount);
	~EntityCollection();

	IHandleEntity** GetEntityCollection();
	IHandleEntity* GetEntity(int iIndex);
	int GetMaxCount();
private:
	IHandleEntity** m_pEntities;
	int m_iMaxCount;
};

//---------------------------------------------------------------------------------
// Wraps Ray_t.
// Q: Why is this wrapped?
// A: Since Ray_t cannot be used directly, and IEngineTrace includes a few
//    functions that take const Ray_t& parameters, a wrap is needed so that
//    we can use the WrappedRay_t type instead.
//---------------------------------------------------------------------------------
class WrappedIEngineTrace
{
public:
	int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, EntityCollection* ppEntity = NULL);	

#if( SOURCE_ENGINE >= 2 )
	int GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask = MASK_ALL);
#endif
	int	GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition);

	void ClipRayToEntity(const WrappedRay_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace);
	void ClipRayToCollideable(const WrappedRay_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace);

	void TraceRay(const WrappedRay_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);

#if( SOURCE_ENGINE >= 2)
	void SetupLeafAndEntityListRay(const WrappedRay_t &ray, ITraceListData *pTraceData);
	void SetupLeafAndEntityListBox(const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData);
	void TraceRayAgainstLeafAndEntityList(const WrappedRay_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);
#endif

	void SweepCollideable(ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd, 
						  const QAngle &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);

	void EnumerateEntities(const WrappedRay_t &ray, bool triggers, IEntityEnumerator *pEnumerator);
	void EnumerateEntities(const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator);

	ICollideable *GetCollideable(IHandleEntity *pEntity);

	int GetStatByIndex(int index, bool bClear);
	void GetBrushesInAABB(const Vector &vMins, const Vector &vMaxs, CUtlVector<int> *pOutput, int iContentsMask = 0xFFFFFFFF);
	CPhysCollide* GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs);

#if( SOURCE_ENGINE >= 2 )
	int GetNumDisplacements();
	void GetDisplacementMesh(int nIndex, virtualmeshlist_t *pMeshTriList);
	bool GetBrushInfo(int iBrush, CUtlVector<BrushSideInfo_t> *pBrushSideInfoOut, int *pContentsOut);
#endif
	bool PointOutsideWorld(const Vector &ptTest);

	int GetLeafContainingPoint(const Vector &ptTest);

#if( SOURCE_ENGINE >= 2 )
	ITraceListData *AllocTraceListData();
	void FreeTraceListData(ITraceListData *tracelistData);
	int GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior_t behavior);
#endif
};

//---------------------------------------------------------------------------------
// A simple trace filter class, allows us to specify an entity not to collide with.
//---------------------------------------------------------------------------------
class CTraceFilterSimple: public CTraceFilter
{
public:	
	CTraceFilterSimple();
	CTraceFilterSimple(const IHandleEntity* pPassEntity);

	virtual bool ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask);

	const IHandleEntity* GetEntity() const;
	void SetEntity(const IHandleEntity* pPassEntity);

private:
	const IHandleEntity* m_pPassEntity;
};

//---------------------------------------------------------------------------------
// A simple trace collection class, allows us to obtain information about multiple
// entities along a ray, using EnumerateEntities.
//---------------------------------------------------------------------------------
class TraceCollideCollection: public IEntityEnumerator
{
public:
	TraceCollideCollection(WrappedRay_t* pWrappedRay, IHandleEntity* pIgnoreEntity, int iContentsMask, int iMaxCount);
	~TraceCollideCollection();

	virtual bool EnumEntity(IHandleEntity* pHandleEntity);

	IServerUnknown* GetEntity(int iIndex);
	int GetEntityCount();

private:
	WrappedRay_t* m_pWrappedRay;
	IHandleEntity* m_pIgnoreEntity;
	IServerUnknown** m_pCollidedEntities;
	int m_iCollidedEntitiesCount;
	int m_iCollidedEntitiesLast;
	int m_iContentsMask;
};

#endif // _ENGINE_TRACE_H
