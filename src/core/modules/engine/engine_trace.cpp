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

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "engine_trace.h"
#include "../export_main.h"
#include "eiface.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "core/sp_python.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// A global wrapped instance of IEngineTrace.
//---------------------------------------------------------------------------------
WrappedIEngineTrace wrappedenginetrace;

//---------------------------------------------------------------------------------
// Returns the [wrapped] engine instance.
//---------------------------------------------------------------------------------
WrappedIEngineTrace* GetTrace( void )
{
	return &wrappedenginetrace;
}

//---------------------------------------------------------------------------------
// Returns a down-cast of trace_t's m_pEnt.
//---------------------------------------------------------------------------------
IServerEntity* GetServerEntity(trace_t* pSelf)
{
	return (IServerEntity*)(pSelf->m_pEnt);
}

//---------------------------------------------------------------------------------
// Wraps Ray_t.
// Q: Why is this wrapped?
// A: Ray_t can't be directly exposed to Boost.Python, as some of its member
//    variables use the VectorAligned type, which is specially defined using
//	  ALIGN16.
//---------------------------------------------------------------------------------
WrappedRay_t::WrappedRay_t()
{
	m_pWrappedRay = new Ray_t();
}

WrappedRay_t::~WrappedRay_t()
{
	if (m_pWrappedRay)
	{
		delete m_pWrappedRay;
		m_pWrappedRay = NULL;
	}
}

void WrappedRay_t::Init(Vector const& start, Vector const& end)
{
	m_pWrappedRay->Init(start, end);
}

void WrappedRay_t::Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs )
{
	m_pWrappedRay->Init(start, end, mins, maxs);
}

Vector WrappedRay_t::InvDelta() const
{
	return m_pWrappedRay->InvDelta();
}

Ray_t* WrappedRay_t::WrappedInstance() const
{
	return m_pWrappedRay;
}

//---------------------------------------------------------------------------------
// Wraps IEngineTrace.
// Q: Why is this wrapped?
// A: Since Ray_t cannot be used directly, and IEngineTrace includes a few
//    functions that take const Ray_t& parameters, a wrap is needed so that
//    we can use the WrappedRay_t type instead.
//---------------------------------------------------------------------------------
int WrappedIEngineTrace::GetPointContents(const Vector &vecAbsPosition, int contentsMask /*= MASK_ALL*/, EntityCollection* ppEntity /*= NULL*/)
{
	if (ppEntity)
	{
#if( SOURCE_ENGINE >= 2 )
		return enginetrace->GetPointContents(vecAbsPosition, contentsMask, ppEntity->GetEntityCollection());
#else
		return enginetrace->GetPointContents(vecAbsPosition, ppEntity->GetEntityCollection());
#endif
	}

#if( SOURCE_ENGINE >= 2 )
	return enginetrace->GetPointContents(vecAbsPosition, contentsMask, NULL);
#else
	return enginetrace->GetPointContents(vecAbsPosition, NULL);
#endif
}
DECLARE_CLASS_METHOD_OVERLOAD(WrappedIEngineTrace, GetPointContents, 1, 3);

#if( SOURCE_ENGINE >= 2 )
int WrappedIEngineTrace::GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask /*= MASK_ALL*/)
{
	return enginetrace->GetPointContents_WorldOnly(vecAbsPosition, contentsMask);
}
DECLARE_CLASS_METHOD_OVERLOAD(WrappedIEngineTrace, GetPointContents_WorldOnly, 1, 2);
#endif

int	WrappedIEngineTrace::GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition)
{
	return enginetrace->GetPointContents_Collideable(pCollide, vecAbsPosition);
}

void WrappedIEngineTrace::ClipRayToEntity(const WrappedRay_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->ClipRayToEntity(*pUnwrappedRay, fMask, pEnt, pTrace);
}

void WrappedIEngineTrace::ClipRayToCollideable(const WrappedRay_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->ClipRayToCollideable(*pUnwrappedRay, fMask, pCollide, pTrace);
}

void WrappedIEngineTrace::TraceRay(const WrappedRay_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->TraceRay(*pUnwrappedRay, fMask, pTraceFilter, pTrace);
}

#if( SOURCE_ENGINE >= 2 )
void WrappedIEngineTrace::SetupLeafAndEntityListRay(const WrappedRay_t &ray, ITraceListData *pTraceData)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->SetupLeafAndEntityListRay(*pUnwrappedRay, pTraceData);
}

void WrappedIEngineTrace::SetupLeafAndEntityListBox(const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData)
{
	enginetrace->SetupLeafAndEntityListBox(vecBoxMin, vecBoxMax, pTraceData);
}

void WrappedIEngineTrace::TraceRayAgainstLeafAndEntityList(const WrappedRay_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->TraceRayAgainstLeafAndEntityList(*pUnwrappedRay, pTraceData, fMask, pTraceFilter, pTrace);
}
#endif

void WrappedIEngineTrace::SweepCollideable(ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd, 
										   const QAngle &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
{
	enginetrace->SweepCollideable(pCollide, vecAbsStart, vecAbsEnd, vecAngles, fMask, pTraceFilter, pTrace);
}

void WrappedIEngineTrace::EnumerateEntities(const WrappedRay_t &ray, bool triggers, IEntityEnumerator *pEnumerator)
{
	Ray_t* pUnwrappedRay = ray.WrappedInstance();
	enginetrace->EnumerateEntities(*pUnwrappedRay, triggers, pEnumerator);
}

void WrappedIEngineTrace::EnumerateEntities(const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator)
{
	enginetrace->EnumerateEntities(vecAbsMins, vecAbsMaxs, pEnumerator);
}

ICollideable* WrappedIEngineTrace::GetCollideable(IHandleEntity *pEntity)
{
	return enginetrace->GetCollideable(pEntity);
}

int WrappedIEngineTrace::GetStatByIndex(int index, bool bClear)
{
	return enginetrace->GetStatByIndex(index, bClear);
}

void WrappedIEngineTrace::GetBrushesInAABB(const Vector &vMins, const Vector &vMaxs, CUtlVector<int> *pOutput, int iContentsMask /*= 0xFFFFFFFF*/)
{
	enginetrace->GetBrushesInAABB(vMins, vMaxs, pOutput, iContentsMask);
}
DECLARE_CLASS_METHOD_OVERLOAD(WrappedIEngineTrace, GetBrushesInAABB, 3, 4);

CPhysCollide* WrappedIEngineTrace::GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs)
{
	return enginetrace->GetCollidableFromDisplacementsInAABB(vMins, vMaxs);
}

#if( SOURCE_ENGINE >= 2 )
int WrappedIEngineTrace::GetNumDisplacements()
{
	return enginetrace->GetNumDisplacements();
}

void WrappedIEngineTrace::GetDisplacementMesh(int nIndex, virtualmeshlist_t *pMeshTriList)
{
	enginetrace->GetDisplacementMesh(nIndex, pMeshTriList);
}
	
bool WrappedIEngineTrace::GetBrushInfo(int iBrush, CUtlVector<BrushSideInfo_t> *pBrushSideInfoOut, int *pContentsOut)
{
	return enginetrace->GetBrushInfo(iBrush, pBrushSideInfoOut, pContentsOut);
}
#endif

bool WrappedIEngineTrace::PointOutsideWorld(const Vector &ptTest)
{
	return enginetrace->PointOutsideWorld(ptTest);
}

int WrappedIEngineTrace::GetLeafContainingPoint(const Vector &ptTest)
{
	return enginetrace->GetLeafContainingPoint(ptTest);
}

#if( SOURCE_ENGINE >= 2 )
ITraceListData* WrappedIEngineTrace::AllocTraceListData()
{
	return enginetrace->AllocTraceListData();
}

void WrappedIEngineTrace::FreeTraceListData(ITraceListData *tracelistData)
{
	enginetrace->FreeTraceListData(tracelistData);
}

int WrappedIEngineTrace::GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior_t behavior)
{
	return enginetrace->GetSetDebugTraceCounter(value, behavior);
}
#endif

//---------------------------------------------------------------------------------
// A simple trace filter class, allows us to specify an entity not to collide with.
//---------------------------------------------------------------------------------
CTraceFilterSimple::CTraceFilterSimple()
{
	m_pPassEntity = NULL;
}

CTraceFilterSimple::CTraceFilterSimple(const IHandleEntity* pPassEntity)
{
	m_pPassEntity = pPassEntity;
}

bool CTraceFilterSimple::ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask)
{
	return pHandleEntity != m_pPassEntity;
}

const IHandleEntity* CTraceFilterSimple::GetEntity() const
{
	return m_pPassEntity;
}

void CTraceFilterSimple::SetEntity(const IHandleEntity* pPassEntity)
{
	m_pPassEntity = pPassEntity;
}

//---------------------------------------------------------------------------------
// A simple trace collection class, allows us to obtain information about multiple
// entities along a ray, using EnumerateEntities.
//---------------------------------------------------------------------------------
TraceCollideCollection::TraceCollideCollection(WrappedRay_t* pWrappedRay, IHandleEntity* pIgnoreEntity, unsigned int uiContentsMask, unsigned int uiMaxCount):
	m_pWrappedRay(pWrappedRay),
	m_pIgnoreEntity(pIgnoreEntity),
	m_uiContentsMask(uiContentsMask),
	m_uiCollidedEntitiesCount(uiMaxCount),
	m_iCollidedEntitiesLast(-1)
{
	//Create the array of entity pointers
	m_pCollidedEntities = new IServerUnknown*[m_uiCollidedEntitiesCount];
	memset(m_pCollidedEntities, 0, sizeof(IServerUnknown*) * m_uiCollidedEntitiesCount);
}

TraceCollideCollection::~TraceCollideCollection()
{
	//Delete the array
	delete[] m_pCollidedEntities;
}

bool TraceCollideCollection::EnumEntity(IHandleEntity* pHandleEntity)
{
	//Ignore if NULL or if it is the filtered entity
	if (pHandleEntity == m_pIgnoreEntity ||
		pHandleEntity == NULL)
	{
		return true;
	}

	//Cast to IServerUnknown, ignore if cannot cast safely
	IServerUnknown* pUnknown = dynamic_cast<IServerUnknown*>(pHandleEntity);
	if (!pUnknown)
	{
		return true;
	}

	//Get trace information, only add if along the ray
	trace_t traceOut;
	enginetrace->ClipRayToEntity(*m_pWrappedRay->WrappedInstance(), m_uiContentsMask, pHandleEntity, &traceOut);
	if ((traceOut.fraction < 1.0f ) || (traceOut.startsolid) || (traceOut.allsolid))
	{
		//Add the entity pointer to the array
		m_pCollidedEntities[++m_iCollidedEntitiesLast] = pUnknown;
	}

	return true;
}

IServerUnknown* TraceCollideCollection::GetEntity(unsigned int uiIndex)
{
	//Return the entity at the index
	if (static_cast<int>(uiIndex) > m_iCollidedEntitiesLast)
	{
		BOOST_RAISE_EXCEPTION(PyExc_IndexError, "Invalid index for this entity collection.");
		return NULL;
	}
	return m_pCollidedEntities[uiIndex];
}

int TraceCollideCollection::GetEntityCount()
{
	//Return the number of entities
	return m_iCollidedEntitiesLast + 1;
}

//---------------------------------------------------------------------------------
// A simple entity collection class, allows for using functions like
// GetPointContents.
//---------------------------------------------------------------------------------
EntityCollection::EntityCollection(int iMaxCount):
	m_iMaxCount(iMaxCount)
{
	m_pEntities = new IHandleEntity*[m_iMaxCount];
	memset(m_pEntities, 0, sizeof(IHandleEntity*) * m_iMaxCount);
}

EntityCollection::~EntityCollection()
{
	delete[] m_pEntities;
}

IHandleEntity** EntityCollection::GetEntityCollection()
{
	return m_pEntities;
}

IHandleEntity* EntityCollection::GetEntity(int iIndex)
{
	if (iIndex >= m_iMaxCount || iIndex < 0)
	{
		BOOST_RAISE_EXCEPTION(PyExc_IndexError, "Invalid index for this entity collection.");
		return NULL;
	}
	return m_pEntities[iIndex];
}

int EntityCollection::GetMaxCount()
{
	return m_iMaxCount;
}

//---------------------------------------------------------------------------------
// Wraps the IEngineTrace interface
//---------------------------------------------------------------------------------
void Export_EngineTrace( void )
{
	//Get the typedefs sorted
	typedef void (WrappedRay_t::*RayInitFn)(Vector const&, Vector const&);
	RayInitFn WrappedRay_t_InitFn = &WrappedRay_t::Init;

	typedef void (WrappedRay_t::*RayInitWithExtentsFn)(Vector const&, Vector const&, Vector const&, Vector const&);
	RayInitWithExtentsFn WrappedRay_t_InitWithExtentsFn = &WrappedRay_t::Init;

	typedef void (WrappedIEngineTrace::*TraceEnumerateEntitiesByRayFn)(WrappedRay_t const&, bool, IEntityEnumerator*);
	TraceEnumerateEntitiesByRayFn IEngineTraceEnumerateEntitiesByRayFn = &WrappedIEngineTrace::EnumerateEntities;

	typedef void (WrappedIEngineTrace::*TraceEnumerateEntitiesByAABB)(Vector const&, Vector const&, IEntityEnumerator*);
	TraceEnumerateEntitiesByAABB IEngineTraceEnumerateEntitiesByAABBFn = &WrappedIEngineTrace::EnumerateEntities;

	// ----------------------------------------------------------
	// WrappedRay_t class.
	// ----------------------------------------------------------
	class_<WrappedRay_t>("Ray_t")
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD_TYPEDEF(Init,
			WrappedRay_t_InitFn,
			"Initializes a ray using two vectors; the first indicating the starting point, and the second indicating the end of the ray.",
			args("start", "end")
		)

		CLASS_METHOD_TYPEDEF(Init,
			WrappedRay_t_InitWithExtentsFn,
			"Initializes a ray using two vectors and two extents.",
			args("start", "end", "mins", "maxs")
		)

		CLASS_METHOD(WrappedRay_t,
			InvDelta,
			"Computes and returns the inverse delta of the ray."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// ITraceFilter class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(ITraceFilter)
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(ITraceFilter,
			ShouldHitEntity,
			"Returns true if the trace should hit the specified entity.",
			args("pEntity", "contentsMask")
		)

		CLASS_METHOD(ITraceFilter,
			GetTraceType,
			"Returns the trace type of this trace filter."
		)			
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilter class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(CTraceFilter, ITraceFilter)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilterEntitiesOnly class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(CTraceFilterEntitiesOnly, ITraceFilter)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilterWorldOnly class.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS(CTraceFilterWorldOnly, ITraceFilter)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilterSimple class.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS(CTraceFilterWorldAndPropsOnly, ITraceFilter)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilterHitAll class.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS(CTraceFilterHitAll, CTraceFilter)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CTraceFilterSimple class.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS(CTraceFilterSimple, CTraceFilter)
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(IHandleEntity*)
		CLASS_METHOD(CTraceFilterSimple,
			ShouldHitEntity,
			"Returns true if the trace should hit the specified entity.",
			args("pEntity", "contentsMask")
		)

		CLASS_METHOD(CTraceFilterSimple,
			GetEntity,
			"Returns the entity that the trace should pass through.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(CTraceFilterSimple,
			SetEntity,
			"Sets the entity that the trace should pass through.",
			args("pPassEntity")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IEntityEnumerator class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IEntityEnumerator)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// TraceCollideCollection class.
	// ----------------------------------------------------------
	class_<TraceCollideCollection, bases<IEntityEnumerator> >("TraceCollideCollection", init<WrappedRay_t*, IHandleEntity*, int, int>())
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(TraceCollideCollection,
			GetEntity,
			"Gets the entity at the specified index.",
			args("iIndex"),
			reference_existing_object_policy()
		)

		.def("__getitem__",
			&TraceCollideCollection::GetEntity,
			"Gets the entity at the specified index.",
			args("iIndex"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(TraceCollideCollection,
			GetEntityCount,
			"Returns the number of entities in this collection."
		)

		.def("__len__",
			&TraceCollideCollection::GetEntityCount,
			"Returns the number of entities in this collection."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// CBaseTrace class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(CBaseTrace)
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(CBaseTrace,
			IsDispSurface,
			"Returns if the DISPSURF_FLAG_SURFACE is set."
		)

		CLASS_METHOD(CBaseTrace,
			IsDispSurfaceWalkable,
			"Returns if the DISPSURF_FLAG_WALKABLE is set."
		)

		CLASS_METHOD(CBaseTrace,
			IsDispSurfaceBuildable,
			"Returns if the DISPSURF_FLAG_BUILDABLE is set."
		)

		CLASS_METHOD(CBaseTrace,
			IsDispSurfaceProp1,
			"Returns if the DISPSURF_FLAG_SURFPROP1 is set."
		)

		CLASS_METHOD(CBaseTrace,
			IsDispSurfaceProp2,
			"Returns if the DISPSURF_FLAG_SURFPROP2 is set."
		)

		// ----------------------------------------------------------
		// Class members.
		// ----------------------------------------------------------
		CLASS_MEMBER(CBaseTrace,
			startpos,
			"The starting position of the trace."
		)

		CLASS_MEMBER(CBaseTrace,
			endpos,
			"The ending position of the trace."
		)

		CLASS_MEMBER(CBaseTrace,
			plane,
			"The surface normal at the point of impact."
		)

		CLASS_MEMBER(CBaseTrace,
			fraction,
			"The time completed to the collision point (i.e. the scalar value of the vector from the start point to the collision point with regards to the start and end points)."
		)

		CLASS_MEMBER(CBaseTrace,
			contents,
			"The contents on the other side of the surface hit."
		)

		CLASS_MEMBER(CBaseTrace,
			dispFlags,
			"The displacement flags for marking surfaces with data."
		)

		CLASS_MEMBER(CBaseTrace,
			allsolid,
			"If true, then the plane is not valid."
		)

		CLASS_MEMBER(CBaseTrace,
			startsolid,
			"If true, the initial point was in a solid area."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// trace_t / CGameTrace class.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS_NOCOPY(trace_t, CBaseTrace)
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(trace_t,
			DidHit,
			"Returns true if there was any kind of impact at all."
		)

		CLASS_METHOD_TYPEDEF(GetServerEntity,
			&GetServerEntity,
			"Returns the IServerEntity instance that was hit by the trace.",
			reference_existing_object_policy()
		)

		// ----------------------------------------------------------
		// Class members.
		// ----------------------------------------------------------
		CLASS_MEMBER(trace_t,
			fractionleftsolid,
			"The time we left a solid, only valid if we started in a solid."
		)

		CLASS_MEMBER(trace_t,
			surface,
			"The surface that we hit."
		)

		CLASS_MEMBER(trace_t,
			hitgroup,
			"The hitgroup that was hit by the trace. 0 is generic hitgroup, and non-zero is a specific body part."
		)

		CLASS_MEMBER(trace_t,
			physicsbone,
			"The physicsbone hit by the trace."
		)

#if( SOURCE_ENGINE >= 2 )
		CLASS_MEMBER(trace_t,
			worldSurfaceIndex,
			"The index of the msurface2_t, if applicable."
		)
#endif

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// EntityCollection class.
	// ----------------------------------------------------------
	class_<EntityCollection>("EntityCollection", init<int>())
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(EntityCollection,
			GetEntity,
			"Returns the entity at a specified index.",
			args("iIndex"),
			reference_existing_object_policy()
		)

		.def("__getitem__",
			&EntityCollection::GetEntity,
			"Gets the entity at the specified index.",
			args("iIndex"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(EntityCollection,
			GetMaxCount,
			"Returns the maximum number of entities in this collection."
		)

		.def("__len__",
			&EntityCollection::GetMaxCount,
			"Returns the maximum number of entities in this collection."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IEngineTrace interface.
	// ----------------------------------------------------------
	class_<WrappedIEngineTrace>("IEngineTrace")
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD_OVERLOAD(WrappedIEngineTrace,
			GetPointContents,
			"Gets the entity contents at a specific point in world space. Can return multiple entities into ppEntity.",
			args("vecAbsPosition", "contentsMask", "ppEntity")
		)

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD_OVERLOAD(WrappedIEngineTrace,
			GetPointContents_WorldOnly,
			"Gets the point contents at a specific point in world space, considering just the world.",
			args("vecAbsPosition", "contentsMask")
		)
#endif

		CLASS_METHOD(WrappedIEngineTrace,
			ClipRayToEntity,
			"Traces a ray against a particular entity and returns in the pTrace parameter information about what the ray first intersected with.",
			args("ray", "fMask", "pEnt", "pTrace")
		)

		CLASS_METHOD(WrappedIEngineTrace,
			ClipRayToCollideable,
			"Traces a ray against a particular entity and returns in the pTrace parameter information about what the ray first intersected with.",
			args("ray", "fMask", "pCollide", "pTrace")
		)

		CLASS_METHOD(WrappedIEngineTrace,
			TraceRay,
			"Traces a ray and returns into the pTrace parameter information about what the ray first intersected with.",
			args("ray", "fMask", "pTraceFilter", "pTrace")
		)

		CLASS_METHOD(WrappedIEngineTrace,
			SweepCollideable,
			"Sweeps a collideable through the world and returns in the pTrace parameter information about what the collideable first intersected with.",
			args("pCollide", "vecAbsStart", "vecAbsEnd", "vecAngles", "fMask", "pTraceFilter", "pTrace")
		)

		CLASS_METHOD_TYPEDEF(EnumerateEntitiesByRay,
			IEngineTraceEnumerateEntitiesByRayFn,
			"Traces a ray and enumerates over all entities along a ray with the pEnumerator instance.",
			args("ray", "triggers", "pEnumerator")
		)

		CLASS_METHOD_TYPEDEF(EnumerateEntitiesByAABB,
			IEngineTraceEnumerateEntitiesByAABBFn,
			"Traces an axis-aligned bounding box (AABB) and enumerates over all entities within the AABB with the pEnumerator instance.",
			args("vecAbsMins", "vecAbsMaxs", "pEnumerator")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the wrapped IEngineTrace instance
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetTrace, "Returns the global IEngineTrace instance.", reference_existing_object_policy());

	// ----------------------------------------------------------
	// Expose lots of BSP and trace related flags
	// ----------------------------------------------------------
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_EMPTY", CONTENTS_EMPTY);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_SOLID", CONTENTS_SOLID);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_WINDOW", CONTENTS_WINDOW);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_AUX", CONTENTS_AUX);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_GRATE", CONTENTS_GRATE);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_SLIME", CONTENTS_SLIME);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_WATER", CONTENTS_WATER);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_BLOCKLOS", CONTENTS_BLOCKLOS);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_OPAQUE", CONTENTS_OPAQUE);
	BOOST_GLOBAL_ATTRIBUTE("LAST_VISIBLE_CONTENTS", LAST_VISIBLE_CONTENTS);
	BOOST_GLOBAL_ATTRIBUTE("ALL_VISIBLE_CONTENTS", ALL_VISIBLE_CONTENTS);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_TESTFOGVOLUME", CONTENTS_TESTFOGVOLUME);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_UNUSED", CONTENTS_UNUSED);

	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_TEAM1", CONTENTS_TEAM1);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_TEAM2", CONTENTS_TEAM2);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_IGNORE_NODRAW_OPAQUE", CONTENTS_IGNORE_NODRAW_OPAQUE);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_MOVEABLE", CONTENTS_MOVEABLE);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_AREAPORTAL", CONTENTS_AREAPORTAL);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_PLAYERCLIP", CONTENTS_PLAYERCLIP);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_MONSTERCLIP", CONTENTS_MONSTERCLIP);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_0", CONTENTS_CURRENT_0);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_90", CONTENTS_CURRENT_90);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_180", CONTENTS_CURRENT_180);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_270", CONTENTS_CURRENT_270);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_UP", CONTENTS_CURRENT_UP);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_CURRENT_DOWN", CONTENTS_CURRENT_DOWN);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_ORIGIN", CONTENTS_ORIGIN);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_MONSTER", CONTENTS_MONSTER);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_DEBRIS", CONTENTS_DEBRIS);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_DETAIL", CONTENTS_DETAIL);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_TRANSLUCENT", CONTENTS_TRANSLUCENT);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_LADDER", CONTENTS_LADDER);
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_HITBOX", CONTENTS_HITBOX);
	BOOST_GLOBAL_ATTRIBUTE("SURF_LIGHT", SURF_LIGHT);
	BOOST_GLOBAL_ATTRIBUTE("SURF_SKY2D", SURF_SKY2D);
	BOOST_GLOBAL_ATTRIBUTE("SURF_SKY", SURF_SKY);
	BOOST_GLOBAL_ATTRIBUTE("SURF_WARP", SURF_WARP);
	BOOST_GLOBAL_ATTRIBUTE("SURF_TRANS", SURF_TRANS);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NOPORTAL", SURF_NOPORTAL);
	BOOST_GLOBAL_ATTRIBUTE("SURF_TRIGGER", SURF_TRIGGER);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NODRAW", SURF_NODRAW);
	BOOST_GLOBAL_ATTRIBUTE("SURF_HINT", SURF_HINT);
	BOOST_GLOBAL_ATTRIBUTE("SURF_SKIP", SURF_SKIP);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NOLIGHT", SURF_NOLIGHT);
	BOOST_GLOBAL_ATTRIBUTE("SURF_BUMPLIGHT", SURF_BUMPLIGHT);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NOSHADOWS", SURF_NOSHADOWS);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NODECALS", SURF_NODECALS);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NOCHOP", SURF_NOCHOP);
	BOOST_GLOBAL_ATTRIBUTE("SURF_HITBOX", SURF_HITBOX);
	BOOST_GLOBAL_ATTRIBUTE("MASK_ALL", MASK_ALL);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SOLID", MASK_SOLID);
	BOOST_GLOBAL_ATTRIBUTE("MASK_PLAYERSOLID", MASK_PLAYERSOLID);
	BOOST_GLOBAL_ATTRIBUTE("MASK_NPCSOLID", MASK_NPCSOLID);
	BOOST_GLOBAL_ATTRIBUTE("MASK_WATER", MASK_WATER);
	BOOST_GLOBAL_ATTRIBUTE("MASK_OPAQUE", MASK_OPAQUE);
	BOOST_GLOBAL_ATTRIBUTE("MASK_OPAQUE_AND_NPCS", MASK_OPAQUE_AND_NPCS);
	BOOST_GLOBAL_ATTRIBUTE("MASK_BLOCKLOS", MASK_BLOCKLOS);
	BOOST_GLOBAL_ATTRIBUTE("MASK_BLOCKLOS_AND_NPCS", MASK_BLOCKLOS_AND_NPCS);
	BOOST_GLOBAL_ATTRIBUTE("MASK_VISIBLE", MASK_VISIBLE);
	BOOST_GLOBAL_ATTRIBUTE("MASK_VISIBLE_AND_NPCS", MASK_VISIBLE_AND_NPCS);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SHOT", MASK_SHOT);	
	BOOST_GLOBAL_ATTRIBUTE("MASK_SHOT_HULL", MASK_SHOT_HULL);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SHOT_PORTAL", MASK_SHOT_PORTAL);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SOLID_BRUSHONLY", MASK_SOLID_BRUSHONLY);
	BOOST_GLOBAL_ATTRIBUTE("MASK_PLAYERSOLID_BRUSHONLY", MASK_PLAYERSOLID_BRUSHONLY);
	BOOST_GLOBAL_ATTRIBUTE("MASK_NPCSOLID_BRUSHONLY", MASK_NPCSOLID_BRUSHONLY);
	BOOST_GLOBAL_ATTRIBUTE("MASK_NPCWORLDSTATIC", MASK_NPCWORLDSTATIC);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SPLITAREAPORTAL", MASK_SPLITAREAPORTAL);
	BOOST_GLOBAL_ATTRIBUTE("MASK_CURRENT", MASK_CURRENT);
	BOOST_GLOBAL_ATTRIBUTE("MASK_DEADSOLID", MASK_DEADSOLID);

#if( SOURCE_ENGINE >= 2 )
	BOOST_GLOBAL_ATTRIBUTE("CONTENTS_BLOCKLIGHT", CONTENTS_BLOCKLIGHT);
	BOOST_GLOBAL_ATTRIBUTE("SURF_NOPAINT", SURF_NOPAINT);
	BOOST_GLOBAL_ATTRIBUTE("MASK_NPCFLUID", MASK_NPCFLUID);
	BOOST_GLOBAL_ATTRIBUTE("MASK_SHOT_BRUSHONLY", MASK_SHOT_BRUSHONLY);
	BOOST_GLOBAL_ATTRIBUTE("MASK_NPCWORLDSTATIC_FLUID", MASK_NPCWORLDSTATIC_FLUID);
#endif
}
