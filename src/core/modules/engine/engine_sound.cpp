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
#include "../export_main.h"
#include "eiface.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "engine/IEngineSound.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IEngineSound* enginesound;

//---------------------------------------------------------------------------------
// Returns the engine instance.
//---------------------------------------------------------------------------------
IEngineSound* GetSound( void )
{
	return enginesound;
}

//---------------------------------------------------------------------------------
// Wraps the IEngineSound interface
//---------------------------------------------------------------------------------

//Declare method overloads to allow for default parameter options
DECLARE_CLASS_METHOD_OVERLOAD(IEngineSound, PrecacheSound, 1, 3);
#if( SOURCE_ENGINE >= 2 )
DECLARE_CLASS_METHOD_OVERLOAD(IEngineSound, EmitSound, 9, 17);
#else
DECLARE_CLASS_METHOD_OVERLOAD(IEngineSound, EmitSound, 6, 15);
#endif
DECLARE_CLASS_METHOD_OVERLOAD(IEngineSound, EmitSentenceByIndex, 7, 15);

void Export_EngineSound( void )
{
#if( SOURCE_ENGINE >= 2 )
	typedef int (IEngineSound::*EmitSoundFn)(IRecipientFilter&, int, int, const char*, unsigned int, const char*, float, float, int, int, int, const Vector*, const Vector*, CUtlVector<Vector>*, bool, float, int);
#else
	typedef void (IEngineSound::*EmitSoundFn)(IRecipientFilter&, int, int, const char*, float, float, int, int, int, const Vector*, const Vector*, CUtlVector<Vector>*, bool, float, int);
#endif
	EmitSoundFn	IEngineSound_EmitSoundFn = &IEngineSound::EmitSound;

	// ----------------------------------------------------------
	// IEngineSound interface.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IEngineSound)
		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD_OVERLOAD(IEngineSound, 
			PrecacheSound, 
			"Precaches a specific sound.",
			args("pSample", "bPreload", "bIsUISound")
		)

		CLASS_METHOD(IEngineSound, 
			IsSoundPrecached, 
			"Returns True if a specific sound is precached.", 
			args("pSample")
		)

		CLASS_METHOD(IEngineSound, 
			PrefetchSound, 
			"Prefetches a specific sound.", 
			args("pSample")
		)

		CLASS_METHOD(IEngineSound, 
			GetSoundDuration, 
			"Returns the duration of a specific sound, in seconds. NOTE: Will not currently work with *.mp3 files.", 
			args("pSample")
		)

#if( SOURCE_ENGINE >= 2 )
		//Had to define the hard way: A typedef AND default parameters all in one method!
		.def("EmitSound",
			IEngineSound_EmitSoundFn,
			IEngineSound_EmitSound(
				"Emits a sound from an entity.",
				args("filter", "iEntIndex", "iChannel", "pSoundEntry", "nSoundEntryHash", "pSample", "flVolume", "flAttenuation", "nSeed", "iFlags", "iPitch", "pOrigin", "pDirection", "pUtlVecOrigins", "bUpdatePositions", "soundtime", "speakerentity")
			)
		)
#else
		.def("EmitSound",
			IEngineSound_EmitSoundFn,
			IEngineSound_EmitSound(
				"Emits a sound from an entity.",
				args("filter", "iEntIndex", "iChannel", "pSample", "flVolume", "flAttenuation", "iFlags", "iPitch", "iSpecialDSP", "pOrigin", "pDirection", "pUtlVecOrigins", "bUpdatePositions", "soundtime", "speakerentity")
			)
		)
#endif

		CLASS_METHOD_OVERLOAD(IEngineSound, 
			EmitSentenceByIndex, 
			"Emits a sentence by a specific sentence index.",
			args("filter", "iEntIndex", "iChannel", "iSentenceIndex", "flVolume", "iSoundlevel", "nSeed", "iFlags", "iPitch", "pOrigin", "pDirection", "pUtlVecOrigins", "bUpdatePositions", "soundtime", "speakerentity")
		)

		CLASS_METHOD(IEngineSound,
			StopSound,
			"Stops a sound from being emitted from an entity.",
			args("iEntIndex", "iChannel", "pSample", "nSoundEntryHash")
		)

		CLASS_METHOD(IEngineSound,
			GetDistGainFromSoundLevel,
			"Returns the distance gain value from a sound level",
			args("soundlevel", "dist")
		)

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD(IEngineSound, 
			IsLoopingSound, 
			"Returns True if a specific sound is set to loop.", 
			args("pSample")
		)
#endif

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the IEngineSound instance
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetSound, "Returns the global IEngineSound instance.", reference_existing_object_policy());

	// ----------------------------------------------------------
	// Expose the sound flags
	// ----------------------------------------------------------

	BOOST_GLOBAL_ATTRIBUTE("VOL_NORM", VOL_NORM);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_NONE", ATTN_NONE);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_NORM", ATTN_NORM);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_IDLE", ATTN_IDLE);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_STATIC", ATTN_STATIC);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_RICOCHET", ATTN_RICOCHET);
	BOOST_GLOBAL_ATTRIBUTE("ATTN_GUNFIRE", ATTN_GUNFIRE);
	BOOST_GLOBAL_ATTRIBUTE("MAX_ATTENUATION", MAX_ATTENUATION);

	enum_<SoundFlags_t>("SoundFlags")
		.value("SND_NOFLAGS", SND_NOFLAGS)
		.value("SND_CHANGE_PITCH", SND_CHANGE_PITCH)
		.value("SND_STOP", SND_STOP)
		.value("SND_SPAWNING", SND_SPAWNING)
		.value("SND_DELAY", SND_DELAY)
		.value("SND_STOP_LOOPING", SND_STOP_LOOPING)
		.value("SND_SPEAKER", SND_SPEAKER)
		.value("SND_SHOULDPAUSE", SND_SHOULDPAUSE)
		.value("SND_IGNORE_PHONEMES", SND_IGNORE_PHONEMES)
		.value("SND_IGNORE_NAME", SND_IGNORE_NAME)
		;

	BOOST_GLOBAL_ATTRIBUTE("PITCH_NORM", PITCH_NORM);
	BOOST_GLOBAL_ATTRIBUTE("PITCH_LOW", PITCH_LOW);
	BOOST_GLOBAL_ATTRIBUTE("PITCH_HIGH", PITCH_HIGH);
	BOOST_GLOBAL_ATTRIBUTE("SOUND_FROM_WORLD", SOUND_FROM_WORLD);
}