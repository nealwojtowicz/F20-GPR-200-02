/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	gproVector.h
	Interface for vectors. Sets an example for C and C++ compatible headers.

	Modified by: ____________
	Modified because: ____________
*/

#ifdef _GPRO_VECTOR_H_
#ifndef _GPRO_VECTOR_INL_
#define _GPRO_VECTOR_INL_

#include "gproVector.h"

#ifdef __cplusplus

inline vec3::vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}
inline vec3::vec3(float const xc, float const yc, float const zc) : x(xc), y(yc), z(zc)
{
}
inline vec3::vec3(float3 const vc) : x(vc[0]), y(vc[1]), z(vc[2])
{
}
inline vec3::vec3(vec3 const& rh) : x(rh.x), y(rh.y), z(rh.z)
{
}

inline vec3& vec3::operator =(vec3 const& rh)
{
	e[0] = rh.e[0];
	e[1] = rh.e[1];
	e[2] = rh.e[2];
	return *this;
}

inline vec3& vec3::operator +=(vec3 const& rh)
{
	e[0] += rh.e[0];
	e[1] += rh.e[1];
	e[2] += rh.e[2];
	return *this;
}

inline vec3 const vec3::operator+(vec3 const& rh) const
{
	return vec3(e[0] + e[0], e[1] + e[1], e[2] + e[2]);
}

inline floatv vec3default(float3 v_out)
{
	v_out[0] = v_out[1] = v_out[2] = 0.0f;
	return v_out;
}
inline floatv vec3init(float3 v_out, float const xc, float const yc, float const zc)
{
	v_out[0] = xc;
	v_out[1] = yc;
	v_out[2] = zc;
	return v_out;
}
inline floatv vec3copy(float3 v_out, float3 const v_rh)
{
	v_out[0] = v_rh[0];
	v_out[1] = v_rh[1];
	v_out[2] = v_rh[2];
	return v_out;
}

inline floatv vec3add(float3 v_lh_sum, float3 const v_rh)
{
	v_lh_sum[0] += v_rh[0];
	v_lh_sum[1] += v_rh[1];
	v_lh_sum[2] += v_rh[2];
	return v_lh_sum;
}

inline floatv vec3sum(float3 v_sum, float3 const v_lh, float3 const v_rh)
{
	return vec3init(v_sum, (v_lh[0] + v_rh[0]), (v_lh[1] + v_rh[1]), (v_lh[2] + v_rh[2]));
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const point3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, float t)
{
	return t * v;
}

inline vec3 operator/(vec3 v, float t)
{
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}


#endif	// __cplusplus
#endif	// !_GPRO_VECTOR_INL_
#endif	// _GPRO_VECTOR_H_
