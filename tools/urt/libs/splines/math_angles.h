/*
This code is based on source provided under the terms of the Id Software 
LIMITED USE SOFTWARE LICENSE AGREEMENT, a copy of which is included with the
GtkRadiant sources (see LICENSE_ID). If you did not receive a copy of 
LICENSE_ID, please contact Id Software immediately at info@idsoftware.com.

All changes and additions to the original source which have been developed by
other contributors (see CONTRIBUTORS) are provided under the terms of the
license the contributors choose (see LICENSE), to the extent permitted by the
LICENSE_ID. If you did not receive a copy of the contributor license,
please contact the GtkRadiant maintainers at info@gtkradiant.com immediately.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __MATH_ANGLES_H__
#define __MATH_ANGLES_H__

#include <stdlib.h>
#include <assert.h>

#include "math_vector.h"

class mat3_t;
class quat_t;
class idVec3;
typedef idVec3 &vec3_p;

class angles_t {
public:
	float			pitch;
	float			yaw;
	float			roll;

					angles_t();
					angles_t( float pitch, float yaw, float roll );
					angles_t( const idVec3 &vec );

	friend void		toAngles( idVec3 &src, angles_t &dst );
	friend void		toAngles( quat_t &src, angles_t &dst );
	friend void		toAngles( mat3_t &src, angles_t &dst );

					operator vec3_p();

	float			operator[]( int index ) const;
	float&			operator[]( int index );

	void 			set( float pitch, float yaw, float roll );

	void			operator=( angles_t const &a );
	void			operator=( idVec3 const &a );

	friend angles_t	operator+( const angles_t &a, const angles_t &b );
	angles_t		&operator+=( angles_t const &a );
	angles_t		&operator+=( idVec3 const &a );

	friend angles_t	operator-( angles_t &a, angles_t &b );
	angles_t		&operator-=( angles_t &a );

	friend angles_t	operator*( const angles_t &a, float b );
	friend angles_t	operator*( float a, const angles_t &b );
	angles_t		&operator*=( float a );

	friend int		operator==(	angles_t &a, angles_t &b );
					
	friend int		operator!=(	angles_t &a, angles_t &b );

	void			toVectors( idVec3 *forward, idVec3 *right = NULL, idVec3 *up = NULL );
	idVec3			toForward( void );

	angles_t		&Zero( void );

	angles_t		&Normalize360( void );
	angles_t		&Normalize180( void );
};

extern angles_t ang_zero;

inline angles_t::angles_t() {}

inline angles_t::angles_t( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

inline angles_t::angles_t( const idVec3 &vec ) {
	this->pitch = vec.x;
	this->yaw	= vec.y;
	this->roll	= vec.z;
}

inline float angles_t::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

inline float& angles_t::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

inline angles_t::operator vec3_p( void ) {
	return *( idVec3 * )&pitch;
}

inline void angles_t::set( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

inline void angles_t::operator=( angles_t const &a ) {
	pitch	= a.pitch;
	yaw		= a.yaw;
	roll	= a.roll;
}

inline void angles_t::operator=( idVec3 const &a ) {
	pitch	= a[ 0 ];
	yaw		= a[ 1 ];
	roll	= a[ 2 ];
}

inline angles_t operator+( const angles_t &a, const angles_t &b ) {
	return angles_t( a.pitch + b.pitch, a.yaw + b.yaw, a.roll + b.roll );
}

inline angles_t& angles_t::operator+=( angles_t const &a ) {
	pitch	+= a.pitch;
	yaw		+= a.yaw;
	roll	+= a.roll;

	return *this;
}

inline angles_t& angles_t::operator+=( idVec3 const &a ) {
	pitch	+= a.x;
	yaw	+= a.y;
	roll	+= a.z;

	return *this;
}

inline angles_t operator-( angles_t &a, angles_t &b ) {
	return angles_t( a.pitch - b.pitch, a.yaw - b.yaw, a.roll - b.roll );
}

inline angles_t& angles_t::operator-=( angles_t &a ) {
	pitch	-= a.pitch;
	yaw		-= a.yaw;
	roll	-= a.roll;

	return *this;
}

inline angles_t operator*( const angles_t &a, float b ) {
	return angles_t( a.pitch * b, a.yaw * b, a.roll * b );
}

inline angles_t operator*( float a, const angles_t &b ) {
	return angles_t( a * b.pitch, a * b.yaw, a * b.roll );
}

inline angles_t& angles_t::operator*=( float a ) {
	pitch	*= a;
	yaw		*= a;
	roll	*= a;

	return *this;
}

inline int operator==( angles_t &a, angles_t &b ) {
	return ( ( a.pitch == b.pitch ) && ( a.yaw == b.yaw ) && ( a.roll == b.roll ) );
}

inline int operator!=( angles_t &a, angles_t &b ) {
	return ( ( a.pitch != b.pitch ) || ( a.yaw != b.yaw ) || ( a.roll != b.roll ) );
}

inline angles_t& angles_t::Zero( void ) {
	pitch	= 0.0f;
	yaw		= 0.0f;
	roll	= 0.0f;

	return *this;
}

#endif /* !__MATH_ANGLES_H__ */
