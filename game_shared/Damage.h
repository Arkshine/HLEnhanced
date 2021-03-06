#ifndef GAME_SHARED_DAMAGE_H
#define GAME_SHARED_DAMAGE_H

// used by suit voice to indicate damage sustained and repaired type to player

// instant damage

enum Damage
{
	DMG_GENERIC				= 0,			// generic damage was done
	DMG_CRUSH				= 1 << 0,		// crushed by falling or moving object
	DMG_BULLET				= 1 << 1,		// shot
	DMG_SLASH				= 1 << 2,		// cut, clawed, stabbed
	DMG_BURN				= 1 << 3,		// heat burned
	DMG_FREEZE				= 1 << 4,		// frozen
	DMG_FALL				= 1 << 5,		// fell too far
	DMG_BLAST				= 1 << 6,		// explosive blast damage
	DMG_CLUB				= 1 << 7,		// crowbar, punch, headbutt
	DMG_SHOCK				= 1 << 8,		// electric shock
	DMG_SONIC				= 1 << 9,		// sound pulse shockwave
	DMG_ENERGYBEAM			= 1 << 10,		// laser or other high energy beam 
	DMG_NEVERGIB			= 1 << 12,		// with this bit OR'd in, no damage type will be able to gib victims upon death
	DMG_ALWAYSGIB			= 1 << 13,		// with this bit OR'd in, any damage type can be made to gib victims upon death.
	DMG_DROWN				= 1 << 14,		// Drowning
// time-based damage
	DMG_TIMEBASED			= ~( 0x3fff ),	// mask for time-based damage

	DMG_PARALYZE			= 1 << 15,		// slows affected creature down
	DMG_NERVEGAS			= 1 << 16,		// nerve toxins, very bad
	DMG_POISON				= 1 << 17,		// blood poisioning
	DMG_RADIATION			= 1 << 18,		// radiation exposure
	DMG_DROWNRECOVER		= 1 << 19,		// drowning recovery
	DMG_ACID				= 1 << 20,		// toxic chemicals or acid burns
	DMG_SLOWBURN			= 1 << 21,		// in an oven
	DMG_SLOWFREEZE			= 1 << 22,		// in a subzero freezer
	DMG_MORTAR				= 1 << 23,		// Hit by air raid (done to distinguish grenade from mortar)

	// these are the damage types that are allowed to gib corpses
	DMG_GIB_CORPSE			= ( DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB ),

	// these are the damage types that have client hud art
	DMG_SHOWNHUD			= ( DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK ),

	//TF ADDITIONS
	DMG_IGNITE				= 1 << 24,		// Players hit by this begin to burn
	DMG_RADIUS_MAX			= 1 << 25,		// Radius damage with this flag doesn't decrease over distance
	DMG_RADIUS_QUAKE		= 1 << 26,		// Radius damage is done like Quake. 1/2 damage at 1/2 radius.
	DMG_IGNOREARMOR			= 1 << 27,		// Damage ignores target's armor
	DMG_AIMED				= 1 << 28,		// Does Hit location damage
	DMG_WALLPIERCING		= 1 << 29,		// Blast Damages ents through walls

	DMG_CALTROP				= 1 << 30,
	DMG_HALLUC				= 1 << 31,

	// TF Healing Additions for TakeHealth
	DMG_IGNORE_MAXHEALTH	= DMG_IGNITE,

	// TF Redefines since we never use the originals
	DMG_NAIL				= DMG_SLASH,
	DMG_NOT_SELF			= DMG_FREEZE,
	
	DMG_TRANQ				= DMG_MORTAR,
	DMG_CONCUSS				= DMG_SONIC,
};

#endif //GAME_SHARED_DAMAGE_H