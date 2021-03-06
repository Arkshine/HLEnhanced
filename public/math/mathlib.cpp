/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
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
// mathlib.cpp -- math primitives

#include "mathlib.h"

const Vector vec3_origin( 0, 0, 0 );

const int nanmask = 255 << 23;

float VectorNormalize( Vector& v )
{
	float	length, ilength;

	length = v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ];
	length = sqrt( length );		// FIXME

	if( length )
	{
		ilength = 1 / length;
		v[ 0 ] *= ilength;
		v[ 1 ] *= ilength;
		v[ 2 ] *= ilength;
	}

	return length;

}

void VectorMA( const Vector& veca, float scale, const Vector& vecb, Vector& vecc )
{
	vecc[ 0 ] = veca[ 0 ] + scale*vecb[ 0 ];
	vecc[ 1 ] = veca[ 1 ] + scale*vecb[ 1 ];
	vecc[ 2 ] = veca[ 2 ] + scale*vecb[ 2 ];
}

void AngleVectors( const Vector& angles, Vector* forward, Vector* right, Vector* up )
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = static_cast<float>( angles[ YAW ] * ( M_PI * 2 / 360 ) );
	sy = sin( angle );
	cy = cos( angle );
	angle = static_cast<float>( angles[ PITCH ] * ( M_PI * 2 / 360 ) );
	sp = sin( angle );
	cp = cos( angle );
	angle = static_cast<float>( angles[ ROLL ] * ( M_PI * 2 / 360 ) );
	sr = sin( angle );
	cr = cos( angle );

	if( forward )
	{
		( *forward )[ 0 ] = cp*cy;
		( *forward )[ 1 ] = cp*sy;
		( *forward )[ 2 ] = -sp;
	}
	if( right )
	{
		( *right )[ 0 ] = ( -1 * sr*sp*cy + -1 * cr*-sy );
		( *right )[ 1 ] = ( -1 * sr*sp*sy + -1 * cr*cy );
		( *right )[ 2 ] = -1 * sr*cp;
	}
	if( up )
	{
		( *up )[ 0 ] = ( cr*sp*cy + -sr*-sy );
		( *up )[ 1 ] = ( cr*sp*sy + -sr*cy );
		( *up )[ 2 ] = cr*cp;
	}
}

void AngleVectorsTranspose( const Vector& angles, Vector* forward, Vector* right, Vector* up )
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = static_cast<float>( angles[ YAW ] * ( M_PI * 2 / 360 ) );
	sy = sin( angle );
	cy = cos( angle );
	angle = static_cast<float>( angles[ PITCH ] * ( M_PI * 2 / 360 ) );
	sp = sin( angle );
	cp = cos( angle );
	angle = static_cast<float>( angles[ ROLL ] * ( M_PI * 2 / 360 ) );
	sr = sin( angle );
	cr = cos( angle );

	if( forward )
	{
		( *forward )[ 0 ] = cp*cy;
		( *forward )[ 1 ] = ( sr*sp*cy + cr*-sy );
		( *forward )[ 2 ] = ( cr*sp*cy + -sr*-sy );
	}
	if( right )
	{
		( *right )[ 0 ] = cp*sy;
		( *right )[ 1 ] = ( sr*sp*sy + cr*cy );
		( *right )[ 2 ] = ( cr*sp*sy + -sr*cy );
	}
	if( up )
	{
		( *up )[ 0 ] = -sp;
		( *up )[ 1 ] = sr*cp;
		( *up )[ 2 ] = cr*cp;
	}
}

void VectorMatrix( Vector& forward, Vector& right, Vector& up )
{
	Vector tmp;

	if( forward[ 0 ] == 0 && forward[ 1 ] == 0 )
	{
		right[ 0 ] = 1;
		right[ 1 ] = 0;
		right[ 2 ] = 0;
		up[ 0 ] = -forward[ 2 ];
		up[ 1 ] = 0;
		up[ 2 ] = 0;
		return;
	}

	tmp[ 0 ] = 0; tmp[ 1 ] = 0; tmp[ 2 ] = 1.0;
	right = CrossProduct( forward, tmp );
	right = right.Normalize();
	up = CrossProduct( right, forward );
	up = up.Normalize();
}

void VectorAngles( const Vector& forward, Vector& angles )
{
	float	tmp, yaw, pitch;

	if( forward[ 1 ] == 0 && forward[ 0 ] == 0 )
	{
		yaw = 0;
		if( forward[ 2 ] > 0 )
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = static_cast<float>( atan2( forward[ 1 ], forward[ 0 ] ) * 180 / M_PI );
		if( yaw < 0 )
			yaw += 360;

		tmp = sqrt( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );
		pitch = static_cast<float>( atan2( forward[ 2 ], tmp ) * 180 / M_PI );
		if( pitch < 0 )
			pitch += 360;
	}

	angles[ 0 ] = pitch;
	angles[ 1 ] = yaw;
	angles[ 2 ] = 0;
}

void AngleMatrix( const Vector& angles, float( *matrix )[ 4 ] )
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = static_cast<float>( angles[ YAW ] * ( M_PI * 2 / 360 ) );
	sy = sin( angle );
	cy = cos( angle );
	angle = static_cast<float>( angles[ PITCH ] * ( M_PI * 2 / 360 ) );
	sp = sin( angle );
	cp = cos( angle );
	angle = static_cast<float>( angles[ ROLL ] * ( M_PI * 2 / 360 ) );
	sr = sin( angle );
	cr = cos( angle );

	// matrix = (YAW * PITCH) * ROLL
	matrix[ 0 ][ 0 ] = cp*cy;
	matrix[ 1 ][ 0 ] = cp*sy;
	matrix[ 2 ][ 0 ] = -sp;
	matrix[ 0 ][ 1 ] = sr*sp*cy + cr*-sy;
	matrix[ 1 ][ 1 ] = sr*sp*sy + cr*cy;
	matrix[ 2 ][ 1 ] = sr*cp;
	matrix[ 0 ][ 2 ] = ( cr*sp*cy + -sr*-sy );
	matrix[ 1 ][ 2 ] = ( cr*sp*sy + -sr*cy );
	matrix[ 2 ][ 2 ] = cr*cp;
	matrix[ 0 ][ 3 ] = 0.0;
	matrix[ 1 ][ 3 ] = 0.0;
	matrix[ 2 ][ 3 ] = 0.0;
}

void AngleIMatrix( const Vector& angles, float matrix[ 3 ][ 4 ] )
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = static_cast<float>( angles[ YAW ] * ( M_PI * 2 / 360 ) );
	sy = sin( angle );
	cy = cos( angle );
	angle = static_cast<float>( angles[ PITCH ] * ( M_PI * 2 / 360 ) );
	sp = sin( angle );
	cp = cos( angle );
	angle = static_cast<float>( angles[ ROLL ] * ( M_PI * 2 / 360 ) );
	sr = sin( angle );
	cr = cos( angle );

	// matrix = (YAW * PITCH) * ROLL
	matrix[ 0 ][ 0 ] = cp*cy;
	matrix[ 0 ][ 1 ] = cp*sy;
	matrix[ 0 ][ 2 ] = -sp;
	matrix[ 1 ][ 0 ] = sr*sp*cy + cr*-sy;
	matrix[ 1 ][ 1 ] = sr*sp*sy + cr*cy;
	matrix[ 1 ][ 2 ] = sr*cp;
	matrix[ 2 ][ 0 ] = ( cr*sp*cy + -sr*-sy );
	matrix[ 2 ][ 1 ] = ( cr*sp*sy + -sr*cy );
	matrix[ 2 ][ 2 ] = cr*cp;
	matrix[ 0 ][ 3 ] = 0.0;
	matrix[ 1 ][ 3 ] = 0.0;
	matrix[ 2 ][ 3 ] = 0.0;
}

void VectorTransform( const Vector& in1, float in2[ 3 ][ 4 ], Vector& out )
{
	//TODO: avoid copy constructing here. - Solokiller
	out[ 0 ] = DotProduct( in1, in2[ 0 ] ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, in2[ 1 ] ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, in2[ 2 ] ) + in2[ 2 ][ 3 ];
}

void NormalizeAngles( float *angles )
{
	int i;
	// Normalize angles
	for( i = 0; i < 3; i++ )
	{
		if( angles[ i ] > 180.0 )
		{
			angles[ i ] -= 360.0;
		}
		else if( angles[ i ] < -180.0 )
		{
			angles[ i ] += 360.0;
		}
	}
}

/*
===================
AngleBetweenVectors

===================
*/
float AngleBetweenVectors( const Vector& v1, const Vector& v2 )
{
	float angle;
	float l1 = v1.Length();
	float l2 = v2.Length();

	if( !l1 || !l2 )
		return 0.0f;

	angle = acos( DotProduct( v1, v2 ) ) / ( l1*l2 );
	angle = static_cast<float>( ( angle  * 180.0f ) / M_PI );

	return angle;
}

float Distance( const Vector& v1, const Vector& v2 )
{
	return ( v2 - v1 ).Length();
}

/*
===================
InterpolateAngles

Interpolate Euler angles.
FIXME:  Use Quaternions to avoid discontinuities
Frac is 0.0 to 1.0 ( i.e., should probably be clamped, but doesn't have to be )
===================
*/
void InterpolateAngles( Vector& start, Vector&end, Vector& output, float frac )
{
	int i;
	float ang1, ang2;
	float d;

	NormalizeAngles( start );
	NormalizeAngles( end );

	for( i = 0; i < 3; i++ )
	{
		ang1 = start[ i ];
		ang2 = end[ i ];

		d = ang2 - ang1;
		if( d > 180 )
		{
			d -= 360;
		}
		else if( d < -180 )
		{
			d += 360;
		}

		output[ i ] = ang1 + d * frac;
	}

	NormalizeAngles( output );
}

int Q_log2( int val )
{
	int answer = 0;
	while( val >>= 1 )
		++answer;
	return answer;
}

float anglemod( float a )
{
	a = static_cast<float>( ( 360.0 / 65536 ) * ( ( int ) ( a*( 65536 / 360.0 ) ) & 65535 ) );
	return a;
}