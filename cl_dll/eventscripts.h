//========= Copyright � 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

// eventscripts.h
#if !defined ( EVENTSCRIPTSH )
#define EVENTSCRIPTSH

#include "event_args.h"

// defaults for clientinfo messages
//TODO: defined in client.cpp - Solokiller
#define	DEFAULT_VIEWHEIGHT	28
//TODO: defined in util.h - Solokiller
#define VEC_DUCK_VIEW 12

#include "Damage.h"

// Some of these are HL/TFC specific?
void EV_EjectBrass( float *origin, float *velocity, float rotation, int model, int soundtype );
void EV_GetGunPosition( event_args_t *args, Vector& pos, const Vector& origin );
void EV_GetDefaultShellInfo( event_args_t *args, 
							 const Vector& origin, const Vector& velocity,
							 Vector& ShellVelocity, Vector& ShellOrigin,
							 const Vector& forward, const Vector& right, const Vector& up,
							 float forwardScale, float upScale, float rightScale );
bool EV_IsLocal( int idx );
bool EV_IsPlayer( int idx );
void EV_CreateTracer( float *start, float *end );

struct cl_entity_s *GetEntity( int idx );
struct cl_entity_s *GetViewEntity( void );
void EV_MuzzleFlash( void );

#endif // EVENTSCRIPTSH
