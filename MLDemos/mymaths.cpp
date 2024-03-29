/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2010  Basilio Noris
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#include "public.h"
#include "mymaths.h"

/************************************************************************/
/*                       std::vector<float>                             */
/************************************************************************/

void operator+= (fvec &a, const fvec b)
{
	if(a.size() == 2)
	{
		a[0] += b[0];
		a[1] += b[1];
	}
	else
	{
		FOR(i, min(a.size(),b.size())) a[i] += b[i];
	}
}

void operator-= (fvec &a, const fvec b)
{
	if(a.size() == 2)
	{
		a[0] -= b[0];
		a[1] -= b[1];
	}
	else
	{
		FOR(i, min(a.size(), b.size())) a[i] -= b[i];
	}
}
void operator+= (fvec &a, const float b)
{
	if(a.size() == 2)
	{
		a[0] += b;
		a[1] += b;
	}
	else
	{
		FOR(i, a.size()) a[i] += b;
	}
}
void operator-= (fvec &a, const float b)
{
	if(a.size() == 2)
	{
		a[0] -= b;
		a[1] -= b;
	}
	else
	{
		FOR(i, a.size()) a[i] -= b;
	}
}
void operator *= (fvec &a, const float b)
{
	if(a.size() == 2)
	{
		a[0] *= b;
		a[1] *= b;
	}
	else
	{
		FOR(i, a.size()) a[i] *= b;
	}
}
void operator /= (fvec &a, const float b)
{
	if(a.size() == 2)
	{
		a[0] /= b;
		a[1] /= b;
	}
	else
	{
		FOR(i, a.size()) a[i] /= b;
	}
}

fvec operator + (const fvec a, const fvec b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] += b[i];
	return c;
}
fvec operator - (const fvec a, const fvec b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] -= b[i];
	return c;
}
fvec operator + (const fvec a, const float b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] += b;
	return c;
}
fvec operator - (const fvec a, const float b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] -= b;
	return c;
}
fvec operator * (const fvec a, const float b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] *= b;
	return c;
}
fvec operator / (const fvec a, const float b)
{
	fvec c = a;
	FOR(i, c.size()) c[i] /= b;
	return c;
}

float operator * (const fvec a, const fvec b)
{
	float sum = 0;
	FOR(i, a.size()) sum += a[i] * b[i];
	return sum;
}

bool operator == (const fvec a, const fvec b)
{
	if(a.size() != a.size()) return false;
	FOR(i, a.size())
	{
		if(a[i] != b[i]) return false;
	}
	return true;
}

bool operator == (const fvec a, const float b)
{
	FOR(i, a.size()) if(a[i] != b) return false;
	return true;
}

bool operator != (const fvec a, const fvec b)
{
	if(a.size() != a.size()) return true;
	FOR(i, a.size())
	{
		if(a[i] != b[i]) return true;
	}
	return false;
}

bool operator != (const fvec a, const float b)
{
	FOR(i, a.size()) if(a[i] != b) return true;
	return false;
}


std::vector<fvec> interpolate(std::vector<fvec> a, int count)
{
	// basic interpolation
	std::vector<fvec> res;
	res.resize(count);
	FOR(i, count)
	{
		int length = a.size();
		float ratio = i/(float)count;
		int index = (int)(ratio*length);
		float remainder = ratio*length - (float)(int)(ratio*length);
		if(remainder == 0 || index == length-1) res[i] = a[index];
		else // we need to interpolate
		{
			fvec pt0 = a[index];
			fvec pt1 = a[index+1];
			res[i] = pt0*(1.f-remainder) + pt1*remainder;
		}
	}
	return res;
}
