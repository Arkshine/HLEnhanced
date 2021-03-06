/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef WEAPONS_H
#define WEAPONS_H

#include "weaponinfo.h"

#include "effects.h"

#include "CMultiDamage.h"

#include "entities/weapons/CAmmoTypes.h"

class CBasePlayer;
extern int gmsgWeapPickup;

void DeactivateSatchels( CBasePlayer *pOwner );

// Contact Grenade / Timed grenade / Satchel Charge
class CGrenade : public CBaseMonster
{
public:
	DECLARE_CLASS( CGrenade, CBaseMonster );

	void Spawn( void ) override;

	typedef enum { SATCHEL_DETONATE = 0, SATCHEL_RELEASE } SATCHELCODE;

	static CGrenade *ShootTimed( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time );
	static CGrenade *ShootContact( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity );
	static CGrenade *ShootSatchelCharge( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity );
	static void UseSatchelCharges( entvars_t *pevOwner, SATCHELCODE code );

	void Explode( Vector vecSrc, Vector vecAim );
	void Explode( TraceResult *pTrace, int bitsDamageType );
	void EXPORT Smoke( void );

	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT SlideTouch( CBaseEntity *pOther );
	void EXPORT ExplodeTouch( CBaseEntity *pOther );
	void EXPORT DangerSoundThink( void );
	void EXPORT PreDetonate( void );
	void EXPORT Detonate( void );
	void EXPORT DetonateUse( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
	void EXPORT TumbleThink( void );

	virtual void BounceSound( void );
	virtual int	BloodColor() const override { return DONT_BLEED; }
	virtual void Killed( entvars_t *pevAttacker, GibAction gibAction ) override;

	bool m_fRegisteredSound;// whether or not this grenade has issued its DANGER sound to the world sound list yet.
};


// constant items
#define ITEM_HEALTHKIT		1
#define ITEM_ANTIDOTE		2
#define ITEM_SECURITY		3
#define ITEM_BATTERY		4

#define WEAPON_NONE				0
#define WEAPON_CROWBAR			1
#define	WEAPON_GLOCK			2
#define WEAPON_PYTHON			3
#define WEAPON_MP5				4
#define WEAPON_CHAINGUN			5
#define WEAPON_CROSSBOW			6
#define WEAPON_SHOTGUN			7
#define WEAPON_RPG				8
#define WEAPON_GAUSS			9
#define WEAPON_EGON				10
#define WEAPON_HORNETGUN		11
#define WEAPON_HANDGRENADE		12
#define WEAPON_TRIPMINE			13
#define	WEAPON_SATCHEL			14
#define	WEAPON_SNARK			15
#define WEAPON_SNIPERRIFLE		16

#define WEAPON_ALLWEAPONS		(~(1<<WEAPON_SUIT))

#define WEAPON_SUIT				31	// ?????

#define MAX_NORMAL_BATTERY	100


// weapon weight factors (for auto-switching)   (-1 = noswitch)
#define CROWBAR_WEIGHT		0
#define GLOCK_WEIGHT		10
#define PYTHON_WEIGHT		15
#define MP5_WEIGHT			15
#define SHOTGUN_WEIGHT		15
#define CROSSBOW_WEIGHT		10
#define RPG_WEIGHT			20
#define GAUSS_WEIGHT		20
#define EGON_WEIGHT			20
#define HORNETGUN_WEIGHT	10
#define HANDGRENADE_WEIGHT	5
#define SNARK_WEIGHT		5
#define SATCHEL_WEIGHT		-10
#define TRIPMINE_WEIGHT		-10
#define SNIPERRIFLE_WEIGHT	10


// weapon clip/carry ammo capacities
#define URANIUM_MAX_CARRY		100
#define	_9MM_MAX_CARRY			250
#define _357_MAX_CARRY			36
#define BUCKSHOT_MAX_CARRY		125
#define BOLT_MAX_CARRY			50
#define ROCKET_MAX_CARRY		5
#define HANDGRENADE_MAX_CARRY	10
#define SATCHEL_MAX_CARRY		5
#define TRIPMINE_MAX_CARRY		5
#define SNARK_MAX_CARRY			15
#define HORNET_MAX_CARRY		8
#define M203_GRENADE_MAX_CARRY	10
#define NATO762_MAX_CARRY		15

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP			-1

//#define CROWBAR_MAX_CLIP		WEAPON_NOCLIP
#define GLOCK_MAX_CLIP			17
#define PYTHON_MAX_CLIP			6
#define MP5_MAX_CLIP			50
#define MP5_DEFAULT_AMMO		25
#define SHOTGUN_MAX_CLIP		8
#define CROSSBOW_MAX_CLIP		5
#define RPG_MAX_CLIP			1
#define GAUSS_MAX_CLIP			WEAPON_NOCLIP
#define EGON_MAX_CLIP			WEAPON_NOCLIP
#define HORNETGUN_MAX_CLIP		WEAPON_NOCLIP
#define HANDGRENADE_MAX_CLIP	WEAPON_NOCLIP
#define SATCHEL_MAX_CLIP		WEAPON_NOCLIP
#define TRIPMINE_MAX_CLIP		WEAPON_NOCLIP
#define SNARK_MAX_CLIP			WEAPON_NOCLIP
#define SNIPERRIFLE_MAX_CLIP	5


// the default amount of ammo that comes with each gun when it spawns
#define GLOCK_DEFAULT_GIVE			17
#define PYTHON_DEFAULT_GIVE			6
#define MP5_DEFAULT_GIVE			25
#define MP5_DEFAULT_AMMO			25
#define MP5_M203_DEFAULT_GIVE		0
#define SHOTGUN_DEFAULT_GIVE		12
#define CROSSBOW_DEFAULT_GIVE		5
#define RPG_DEFAULT_GIVE			1
#define GAUSS_DEFAULT_GIVE			20
#define EGON_DEFAULT_GIVE			20
#define HANDGRENADE_DEFAULT_GIVE	5
#define SATCHEL_DEFAULT_GIVE		1
#define TRIPMINE_DEFAULT_GIVE		1
#define SNARK_DEFAULT_GIVE			5
#define HIVEHAND_DEFAULT_GIVE		8
#define SNIPERRIFLE_DEFAULT_GIVE	5

// The amount of ammo given to a player by an ammo item.
#define AMMO_URANIUMBOX_GIVE	20
#define AMMO_GLOCKCLIP_GIVE		GLOCK_MAX_CLIP
#define AMMO_357BOX_GIVE		PYTHON_MAX_CLIP
#define AMMO_MP5CLIP_GIVE		MP5_MAX_CLIP
#define AMMO_CHAINBOX_GIVE		200
#define AMMO_M203BOX_GIVE		2
#define AMMO_BUCKSHOTBOX_GIVE	12
#define AMMO_CROSSBOWCLIP_GIVE	CROSSBOW_MAX_CLIP
#define AMMO_RPGCLIP_GIVE		RPG_MAX_CLIP
#define AMMO_URANIUMBOX_GIVE	20
#define AMMO_SNARKBOX_GIVE		5
#define AMMO_SNIPERRIFLE_GIVE	5

// bullet types
typedef	enum
{
	BULLET_NONE = 0,
	BULLET_PLAYER_9MM, // glock
	BULLET_PLAYER_MP5, // mp5
	BULLET_PLAYER_357, // python
	BULLET_PLAYER_BUCKSHOT, // shotgun
	BULLET_PLAYER_CROWBAR, // crowbar swipe

	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,

	//TODO: fill in the rest - Solokiller
	BULLET_PLAYER_762 = 10,
} Bullet;


#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16 // A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET 0x40

typedef struct
{
	int		iSlot;
	int		iPosition;
	const char	*pszAmmo1;	// ammo 1 type
	const char	*pszAmmo2;	// ammo 2 type
	const char	*pszName;
	int		iMaxClip;
	int		iId;
	int		iFlags;
	int		iWeight;// this value used to determine this weapon's importance in autoselection.
} ItemInfo;

// Items that the player has in their inventory that they can use
class CBasePlayerItem : public CBaseAnimating
{
public:
	DECLARE_CLASS( CBasePlayerItem, CBaseAnimating );
	DECLARE_DATADESC();

	virtual void SetObjectCollisionBox( void ) override;

	virtual bool AddToPlayer( CBasePlayer *pPlayer );	// return true if the item you want the item added to the player inventory
	virtual bool AddDuplicate( CBasePlayerItem *pItem ) { return false; }	// return true if you want your duplicate removed from world
	void EXPORT DestroyItem( void );
	void EXPORT DefaultTouch( CBaseEntity *pOther );	// default weapon touch
	void EXPORT FallThink ( void );// when an item is first spawned, this think is run to determine when the object has hit the ground.
	void EXPORT Materialize( void );// make a weapon visible and tangible
	void EXPORT AttemptToMaterialize( void );  // the weapon desires to become visible and tangible, if the game rules allow for it
	CBaseEntity* Respawn ( void ) override;// copy a weapon
	void FallInit( void );
	void CheckRespawn( void );
	virtual bool GetItemInfo( ItemInfo* p ) { return false; } // returns false if struct not filled out
	virtual bool CanDeploy() const { return true; }
	// returns if deploy was successful
	virtual bool Deploy() { return true; }

	virtual bool CanHolster() { return true; } // can this weapon be put away right now?
	virtual void Holster( int skiplocal = 0 );
	virtual void UpdateItemInfo( void ) { return; };

	virtual void ItemPreFrame( void )	{ return; }		// called each frame by the player PreThink
	virtual void ItemPostFrame( void ) { return; }		// called each frame by the player PostThink

	virtual void Drop( void );
	virtual void Kill( void );
	virtual void AttachToPlayer ( CBasePlayer *pPlayer );

	virtual int PrimaryAmmoIndex() const { return -1; }
	virtual int SecondaryAmmoIndex() const { return -1; }

	virtual bool UpdateClientData( CBasePlayer *pPlayer ) { return false; }

	virtual CBasePlayerItem *GetWeaponPtr( void ) { return NULL; };

	static ItemInfo ItemInfoArray[ MAX_WEAPONS ];

	CBasePlayer	*m_pPlayer;
	CBasePlayerItem *m_pNext;
	int		m_iId;												// WEAPON_???

	virtual int iItemSlot( void ) { return 0; }			// return 0 to MAX_ITEMS_SLOTS, used in hud

	int			iItemPosition() const { return ItemInfoArray[ m_iId ].iPosition; }
	const char	*pszAmmo1() const	{ return ItemInfoArray[ m_iId ].pszAmmo1; }
	const char	*pszAmmo2() const	{ return ItemInfoArray[ m_iId ].pszAmmo2; }
	const char	*pszName() const	{ return ItemInfoArray[ m_iId ].pszName; }
	int			iMaxClip() const	{ return ItemInfoArray[ m_iId ].iMaxClip; }
	int			iWeight() const		{ return ItemInfoArray[ m_iId ].iWeight; }
	int			iFlags() const		{ return ItemInfoArray[ m_iId ].iFlags; }

	// int		m_iIdPrimary;										// Unique Id for primary ammo
	// int		m_iIdSecondary;										// Unique Id for secondary ammo
};


// inventory items that 
class CBasePlayerWeapon : public CBasePlayerItem
{
public:
	DECLARE_CLASS( CBasePlayerWeapon, CBasePlayerItem );
	DECLARE_DATADESC();

	CBasePlayerWeapon()
		: m_iSecondaryAmmoType( -1 ) //Default to -1 to achieve SDK behavior - Solokiller
	{
	}

	virtual void OnCreate() override
	{
		BaseClass::OnCreate();

		ItemInfo II;

		memset( &II, 0, sizeof( II ) );

		//Set up the ammo types. - Solokiller
		if( GetItemInfo( &II ) )
		{
			m_pPrimaryAmmo = g_AmmoTypes.GetAmmoTypeByName( II.pszAmmo1 );
			m_pSecondaryAmmo = g_AmmoTypes.GetAmmoTypeByName( II.pszAmmo2 );
		}
	}

	// generic weapon versions of CBasePlayerItem calls
	virtual bool AddToPlayer( CBasePlayer *pPlayer ) override;
	virtual bool AddDuplicate( CBasePlayerItem *pItem ) override;

	virtual bool ExtractAmmo( CBasePlayerWeapon *pWeapon ); //{ return true; }			// Return true if you can add ammo to yourself when picked up
	virtual bool ExtractClipAmmo( CBasePlayerWeapon *pWeapon );// { return true; }			// Return true if you can add ammo to yourself when picked up

	virtual bool AddWeapon() { ExtractAmmo( this ); return true; }	// Return true if you want to add yourself to the player

	// generic "shared" ammo handlers
	bool AddPrimaryAmmo( int iCount, const char *szName, int iMaxClip );
	bool AddSecondaryAmmo( int iCount, const char *szName );

	virtual void UpdateItemInfo( void ) override {};	// updates HUD state

	bool m_bPlayEmptySound;
	bool m_bFireOnEmpty;		// True when the gun is empty and the player is still holding down the
							// attack key(s)
	virtual bool PlayEmptySound();
	virtual void ResetEmptySound();

	virtual void SendWeaponAnim( int iAnim, int skiplocal = 1, int body = 0 );  // skiplocal is 1 if client is predicting weapon animations

	virtual bool CanDeploy() const override;
	virtual bool IsUseable();
	bool DefaultDeploy( char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0, int body = 0 );
	bool DefaultReload( int iClipSize, int iAnim, float fDelay, int body = 0 );

	virtual void ItemPostFrame( void ) override;	// called each frame by the player PostThink
	// called by CBasePlayerWeapons ItemPostFrame()
	virtual void PrimaryAttack( void ) { return; }				// do "+ATTACK"
	virtual void SecondaryAttack( void ) { return; }			// do "+ATTACK2"
	virtual void Reload( void ) { return; }						// do "+RELOAD"
	virtual void WeaponIdle( void ) { return; }					// called when no buttons pressed
	virtual bool UpdateClientData( CBasePlayer *pPlayer ) override;		// sends hud info to client dll, if things have changed
	virtual void RetireWeapon( void );
	virtual bool ShouldWeaponIdle() {return false; }
	virtual void Holster( int skiplocal = 0 );
	virtual bool UseDecrement() const { return false; }
	
	int	PrimaryAmmoIndex() const; 
	int	SecondaryAmmoIndex() const; 

	void PrintState( void );

	virtual CBasePlayerItem *GetWeaponPtr( void ) override { return (CBasePlayerItem *)this; };
	float GetNextAttackDelay( float delay );

	/**
	*	Copies weapon data to the weapon_data_t instance.
	*	@param data Weapon data.
	*/
	virtual void GetWeaponData( weapon_data_t& data )
	{
		//TODO: move this to a source file once we have a shared weapon file - Solokiller
		data.m_iClip					= m_iClip;

		data.m_flTimeWeaponIdle			= max( m_flTimeWeaponIdle, -0.001 );
		data.m_flNextPrimaryAttack		= max( m_flNextPrimaryAttack, -0.001 );
		data.m_flNextSecondaryAttack	= max( m_flNextSecondaryAttack, -0.001 );

		data.m_fInReload				= m_fInReload;

		data.fuser1						= max( pev->fuser1, -0.001 );
	}

	/**
	*	Copies weapon data from the weapon_data_t instance.
	*	@param data Weapon data.
	*/
	virtual void SetWeaponData( const weapon_data_t& data )
	{
		//TODO: move this to a source file once we have a shared weapon file - Solokiller
		m_iClip						= data.m_iClip;

		m_flTimeWeaponIdle			= data.m_flTimeWeaponIdle;
		m_flNextPrimaryAttack		= data.m_flNextPrimaryAttack;
		m_flNextSecondaryAttack		= data.m_flNextSecondaryAttack;

		m_fInReload					= data.m_fInReload != 0;

		pev->fuser1					= data.fuser1;
	}

	float	m_flNextPrimaryAttack;								// soonest time ItemPostFrame will call PrimaryAttack
	float	m_flNextSecondaryAttack;							// soonest time ItemPostFrame will call SecondaryAttack
	float	m_flTimeWeaponIdle;									// soonest time ItemPostFrame will call WeaponIdle
	int		m_iPrimaryAmmoType;									// "primary" ammo index into players m_rgAmmo[]
	int		m_iSecondaryAmmoType;								// "secondary" ammo index into players m_rgAmmo[]
	int		m_iClip;											// number of shots left in the primary weapon clip, -1 it not used
	int		m_iClientClip;										// the last version of m_iClip sent to hud dll
	int		m_iClientWeaponState;								// the last version of the weapon state sent to hud dll (is current weapon, is on target)
	bool	m_fInReload;										// Are we in the middle of a reload;

	int		m_iDefaultAmmo;// how much ammo you get when you pick up this weapon as placed by a level designer.
	
	// hle time creep vars
	float	m_flPrevPrimaryAttack;
	float	m_flLastFireTime;			

	/**
	*	Pointer to the primary ammo type. - Solokiller
	*/
	CAmmoType* m_pPrimaryAmmo = nullptr;

	/**
	*	Pointer to the secondary ammo type. - Solokiller
	*/
	CAmmoType* m_pSecondaryAmmo = nullptr;
};

#define DEFAULT_AMMO_PICKUP_SOUND "items/9mmclip1.wav"

/**
*	Gives ammo to the given player.
*	@param pGiver Entity that is giving the ammo.
*	@param pPlayer Player to give ammo to. If this is not a player, no ammo is given.
*	@param iAmount Amount of ammo to give. Amount smaller than or equal to 0 are ignored.
*	@param pszAmmoName Name of the ammo type to give ammo of.
*	@param pszPickupSound Sound to play on pickup. Defaults to DEFAULT_AMMO_PICKUP_SOUND. If null, no sound is played.
*	@return true if ammo was given, false otherwise.
*/
bool UTIL_GiveAmmoToPlayer( CBaseEntity* pGiver, CBaseEntity* pPlayer,
							const int iAmount, const char* const pszAmmoName, 
							const char* const pszPickupSound = DEFAULT_AMMO_PICKUP_SOUND );

class CBasePlayerAmmo : public CBaseEntity
{
public:
	DECLARE_CLASS( CBasePlayerAmmo, CBaseEntity );

	virtual void Spawn( void ) override;
	void EXPORT DefaultTouch( CBaseEntity *pOther ); // default weapon touch
	virtual bool AddAmmo( CBaseEntity *pOther ) { return true; }

	CBaseEntity* Respawn( void ) override;
	void EXPORT Materialize( void );
};


extern DLL_GLOBAL	short	g_sModelIndexLaser;// holds the index for the laser beam
extern DLL_GLOBAL	const char *g_pModelNameLaser;

extern DLL_GLOBAL	short	g_sModelIndexLaserDot;// holds the index for the laser beam dot
extern DLL_GLOBAL	short	g_sModelIndexFireball;// holds the index for the fireball
extern DLL_GLOBAL	short	g_sModelIndexSmoke;// holds the index for the smoke cloud
extern DLL_GLOBAL	short	g_sModelIndexWExplosion;// holds the index for the underwater explosion
extern DLL_GLOBAL	short	g_sModelIndexBubbles;// holds the index for the bubbles model
extern DLL_GLOBAL	short	g_sModelIndexBloodDrop;// holds the sprite index for blood drops
extern DLL_GLOBAL	short	g_sModelIndexBloodSpray;// holds the sprite index for blood spray (bigger)

extern void DecalGunshot( TraceResult *pTrace, int iBulletType );
extern void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
extern int DamageDecal( CBaseEntity *pEntity, int bitsDamageType );
extern void RadiusDamage( Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType );

extern CMultiDamage g_MultiDamage;

#define LOUD_GUN_VOLUME			1000
#define NORMAL_GUN_VOLUME		600
#define QUIET_GUN_VOLUME		200

#define	BRIGHT_GUN_FLASH		512
#define NORMAL_GUN_FLASH		256
#define	DIM_GUN_FLASH			128

#define BIG_EXPLOSION_VOLUME	2048
#define NORMAL_EXPLOSION_VOLUME	1024
#define SMALL_EXPLOSION_VOLUME	512

#define	WEAPON_ACTIVITY_VOLUME	64

#define VECTOR_CONE_1DEGREES	Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES	Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES	Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES	Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES	Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES	Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES	Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES	Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES	Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES	Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES	Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES	Vector( 0.17365, 0.17365, 0.17365 )

#ifdef CLIENT_DLL
bool bIsMultiplayer ( void );
void LoadVModel ( char *szViewModel, CBasePlayer *m_pPlayer );
#endif

class CGlock : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CGlock, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 2; }
	bool GetItemInfo( ItemInfo* p ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	void GlockFire( float flSpread, float flCycleTime, const bool fUseAutoAim );
	bool Deploy() override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;

	virtual bool UseDecrement() const override
	{ 
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	int m_iShell;
	

	unsigned short m_usFireGlock1;
	unsigned short m_usFireGlock2;
};


class CCrowbar : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CCrowbar, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 1; }
	void EXPORT SwingAgain( void );
	void EXPORT Smack( void );
	bool GetItemInfo( ItemInfo* p ) override;

	void PrimaryAttack( void ) override;
	bool Swing( const bool bFirst );
	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;
	int m_iSwing;
	TraceResult m_trHit;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}
private:
	unsigned short m_usCrowbar;
};

class CPython : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CPython, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 2; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;
	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;

	bool m_fInZoom;// don't save this. 

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usFirePython;
};

class CMP5 : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CMP5, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 3; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool Deploy() override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;
	float m_flNextAnimTime;
	int m_iShell;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usMP5;
	unsigned short m_usMP52;
};

class CCrossbow : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CCrossbow, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( ) override { return 3; }
	bool GetItemInfo( ItemInfo* p ) override;

	void FireBolt( void );
	void FireSniperBolt( void );
	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;
	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;

	int m_fInZoom; // don't save this

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usCrossbow;
	unsigned short m_usCrossbow2;
};

class CShotgun : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CShotgun, CBasePlayerWeapon );
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( ) override { return 3; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool Deploy() override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;
	float m_flNextReload;
	int m_iShell;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

	void GetWeaponData( weapon_data_t& data ) override
	{
		BaseClass::GetWeaponData( data );

		data.m_fInSpecialReload = m_fInSpecialReload;

		//data.m_flPumpTime		= max( m_flPumpTime, -0.001 );
	}

	void SetWeaponData( const weapon_data_t& data ) override
	{
		BaseClass::SetWeaponData( data );

		m_fInSpecialReload	= data.m_fInSpecialReload;
		//m_flPumpTime		= data.m_flPumpTime;
	}

private:
	unsigned short m_usDoubleFire;
	unsigned short m_usSingleFire;

	int m_fInSpecialReload;		// Are we in the middle of a reload for the shotguns
	float m_flPumpTime;
};

class CLaserSpot : public CBaseEntity
{
public:
	DECLARE_CLASS( CLaserSpot, CBaseEntity );

	void Spawn( void ) override;
	void Precache( void ) override;

	int	ObjectCaps() const override { return FCAP_DONT_SAVE; }

	void Suspend( float flSuspendTime );
	void EXPORT Revive( void );
	
	static CLaserSpot *CreateSpot( void );
};

class CRpg : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CRpg, CBasePlayerWeapon );
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif

	void Spawn( void ) override;
	void Precache( void ) override;
	void Reload( void ) override;
	int iItemSlot( void ) override { return 4; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	bool Deploy() override;
	bool CanHolster() override;
	void Holster( int skiplocal = 0 ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	void WeaponIdle( void ) override;

	void UpdateSpot( void );
	bool ShouldWeaponIdle() override { return true; }

	CLaserSpot *m_pSpot;
	int m_fSpotActive;
	int m_cActiveRockets;// how many missiles in flight from this launcher right now?

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usRpg;

};

class CRpgRocket : public CGrenade
{
public:
	DECLARE_CLASS( CRpgRocket, CGrenade );
	DECLARE_DATADESC();

	void Spawn( void ) override;
	void Precache( void ) override;
	void EXPORT FollowThink( void );
	void EXPORT IgniteThink( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	static CRpgRocket *CreateRpgRocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, CRpg *pLauncher );

	int m_iTrail;
	float m_flIgniteTime;
	CRpg *m_pLauncher;// pointer back to the launcher that fired me. 
};

class CGauss : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CGauss, CBasePlayerWeapon );
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 4; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	bool Deploy() override;
	void Holster( int skiplocal = 0  ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	void WeaponIdle( void ) override;
	
	void StartFire( void );
	void Fire( Vector vecOrigSrc, Vector vecDirShooting, float flDamage );
	float GetFullChargeTime( void );

	void GetWeaponData( weapon_data_t& data ) override
	{
		BaseClass::GetWeaponData( data );

		data.iuser2 = m_fInAttack;
	}

	void SetWeaponData( const weapon_data_t& data ) override
	{
		BaseClass::SetWeaponData( data );

		m_fInAttack = data.iuser2;
	}

	int m_iBalls;
	int m_iGlow;
	int m_iBeam;
	int m_iSoundState; // don't save this

	// was this weapon just fired primary or secondary?
	// we need to know so we can pick the right set of effects. 
	bool m_fPrimaryFire;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usGaussFire;
	unsigned short m_usGaussSpin;

	//TODO: this should be an enum - Solokiller
	int m_fInAttack;
};

class CEgon : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CEgon, CBasePlayerWeapon );
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 4; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;

	void UpdateEffect( const Vector &startPoint, const Vector &endPoint, float timeBlend );

	void CreateEffect ( void );
	void DestroyEffect ( void );

	void EndAttack( void );
	void Attack( void );
	void PrimaryAttack( void ) override;
	void WeaponIdle( void ) override;

	float m_flAmmoUseTime;// since we use < 1 point of ammo per update, we subtract ammo on a timer.

	float GetPulseInterval( void );
	float GetDischargeInterval( void );

	void Fire( const Vector &vecOrigSrc, const Vector &vecDir );

	bool HasAmmo() const;

	void UseAmmo( int count );

	void GetWeaponData( weapon_data_t& data ) override
	{
		BaseClass::GetWeaponData( data );

		data.iuser3 = m_fireState;
	}

	void SetWeaponData( const weapon_data_t& data ) override
	{
		BaseClass::SetWeaponData( data );

		m_fireState = data.iuser3;
	}
	
	enum EGON_FIREMODE { FIRE_NARROW, FIRE_WIDE};

	enum EGON_FIRESTATE { FIRE_OFF, FIRE_CHARGE };

	CBeam				*m_pBeam;
	CBeam				*m_pNoise;
	CSprite				*m_pSprite;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

	unsigned short m_usEgonStop;

private:
	float				m_shootTime;
	EGON_FIREMODE		m_fireMode;
	int					m_fireState;
	float				m_shakeTime;
	bool				m_deployed;

	unsigned short m_usEgonFire;
};

class CHgun : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CHgun, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 4; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool Deploy() override;
	bool IsUseable() override;
	void Holster( int skiplocal = 0 ) override;
	void Reload( void ) override;
	void WeaponIdle( void ) override;
	float m_flNextAnimTime;

	float m_flRechargeTime;
	
	int m_iFirePhase;// don't save me.

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}
private:
	unsigned short m_usHornetFire;
};



class CHandGrenade : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CHandGrenade, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 5; }
	bool GetItemInfo( ItemInfo* p ) override;

	void PrimaryAttack( void ) override;
	bool Deploy() override;
	bool CanHolster() override;
	void Holster( int skiplocal = 0 ) override;
	void WeaponIdle( void ) override;
	
	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

	void GetWeaponData( weapon_data_t& data ) override
	{
		BaseClass::GetWeaponData( data );

		data.fuser2 = m_flStartThrow;
		data.fuser3 = m_flReleaseThrow;
	}

	void SetWeaponData( const weapon_data_t& data ) override
	{
		BaseClass::SetWeaponData( data );

		m_flStartThrow		= data.fuser2;
		m_flReleaseThrow	= data.fuser3;
	}

private:
	float m_flStartThrow;
	float m_flReleaseThrow;
};

class CSatchel : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CSatchel, CBasePlayerWeapon );
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 5; }
	bool GetItemInfo( ItemInfo* p ) override;
	bool AddToPlayer( CBasePlayer *pPlayer ) override;
	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool AddDuplicate( CBasePlayerItem *pOriginal ) override;
	bool CanDeploy() const override;
	bool Deploy() override;
	bool IsUseable() override;
	
	void Holster( int skiplocal = 0 ) override;
	void WeaponIdle( void ) override;
	void Throw( void );
	
	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

	void GetWeaponData( weapon_data_t& data ) override
	{
		BaseClass::GetWeaponData( data );

		data.iuser1 = m_chargeReady;
	}

	void SetWeaponData( const weapon_data_t& data ) override
	{
		BaseClass::SetWeaponData( data );

		m_chargeReady = data.iuser1;
	}

private:
	//TODO: make this an enum - Solokiller
	int m_chargeReady;
};


class CTripmine : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CTripmine, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 5; }
	bool GetItemInfo( ItemInfo* p ) override;
	void SetObjectCollisionBox( void ) override
	{
		//!!!BUGBUG - fix the model!
		pev->absmin = pev->origin + Vector(-16, -16, -5);
		pev->absmax = pev->origin + Vector(16, 16, 28); 
	}

	void PrimaryAttack( void ) override;
	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;
	void WeaponIdle( void ) override;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usTripFire;

};

class CSqueak : public CBasePlayerWeapon
{
public:
	DECLARE_CLASS( CSqueak, CBasePlayerWeapon );

	void Spawn( void ) override;
	void Precache( void ) override;
	int iItemSlot( void ) override { return 5; }
	bool GetItemInfo( ItemInfo* p ) override;

	void PrimaryAttack( void ) override;
	void SecondaryAttack( void ) override;
	bool Deploy() override;
	void Holster( int skiplocal = 0 ) override;
	void WeaponIdle( void ) override;
	int m_fJustThrown;

	virtual bool UseDecrement() const override
	{
#if defined( CLIENT_WEAPONS )
		return true;
#else
		return false;
#endif
	}

private:
	unsigned short m_usSnarkFire;
};


#endif // WEAPONS_H
