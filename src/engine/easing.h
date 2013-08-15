//
//  easing.h
//  SpaceJunk
//
//  Created by ixtli on 8/15/13.
//
//	Based on jQuery Easing v1.3 - http://gsgd.co.uk/sandbox/jquery/easing/
//	Copyright © 2008 George McGinley Smith under the BSD License.
//	All rights reserved.
//	The original license follows:
//

/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * Neither the name of the author nor the names of contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SpaceJunk_easing_h
#define SpaceJunk_easing_h

/*
 * All functions hereafter follow the following variable naming convention:
 * t: current time, b: begInnIng value, c: change In value, d: duration
 */

#include <math.h>

#define EASING_FUNCTION(name) \
template <class T> \
__attribute__((always_inline)) \
T name (T x, T t, T b, T c, T d)

EASING_FUNCTION(easeInQuad)
{
	return c * (t /= d) * t + b;
}

EASING_FUNCTION(easeOutQuad)
{
	return -c *(t/=d)*(t-2) + b;
}

EASING_FUNCTION(easeInOutQuad)
{
	if ((t/=d/2) < 1) return c/2*t*t + b;
	return -c/2 * ((--t)*(t-2) - 1) + b;
}

EASING_FUNCTION(easeInCubic)
{
	return c*(t/=d)*t*t + b;
}

EASING_FUNCTION(easeOutCubic)
{
	return c*((t=t/d-1)*t*t + 1) + b;
}

EASING_FUNCTION(easeInOutCubic)
{
	if ((t/=d/2) < 1) return c/2*t*t*t + b;
	return c/2*((t-=2)*t*t + 2) + b;
}

EASING_FUNCTION(easeInQuart)
{
	return c*(t/=d)*t*t*t + b;
}

EASING_FUNCTION(easeOutQuart)
{
	return -c * ((t=t/d-1)*t*t*t - 1) + b;
}

EASING_FUNCTION(easeInOutQuart)
{
	if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
	return -c/2 * ((t-=2)*t*t*t - 2) + b;
}

EASING_FUNCTION(easeInQuint)
{
	return c*(t/=d)*t*t*t*t + b;
}

EASING_FUNCTION(easeOutQuint)
{
	return c*((t=t/d-1)*t*t*t*t + 1) + b;
}

EASING_FUNCTION(easeInOutQuint)
{
	if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
	return c/2*((t-=2)*t*t*t*t + 2) + b;
}

EASING_FUNCTION(easeInSine)
{
	return -c * cos(t/d * (M_PI_2)) + c + b;
}

EASING_FUNCTION(easeOutSine)
{
	return c * sin(t/d * (M_PI_2)) + b;
}

EASING_FUNCTION(easeInOutSine)
{
	return -c/2 * (cos(M_PI * t/d) - 1) + b;
}

EASING_FUNCTION(easeInExpo)
{
	return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

EASING_FUNCTION(easeOutExpo)
{
	return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
}

EASING_FUNCTION(easeInOutExpo)
{
	if (t==0) return b;
	if (t==d) return b+c;
	if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
	return c/2 * (-pow(2, -10 * --t) + 2) + b;
}

EASING_FUNCTION(easeInCirc)
{
	return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}

EASING_FUNCTION(easeOutCirc)
{
	return c * sqrt(1 - (t=t/d-1)*t) + b;
}

EASING_FUNCTION(easeInOutCirc)
{
	if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
	return c/2 * (sqrt(1 - (t-=2)*t) + 1) + b;
}

EASING_FUNCTION(easeInElastic)
{
	T s = 1.70158f; T p=0 ; T a = c;
	if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
	if (a < abs(c)) { a=c; s = p/4; }
	else s = p/(2*M_PI) * asin (c/a);
	return -(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*M_PI)/p )) + b;
}

EASING_FUNCTION(easeOutElastic)
{
	T s = 1.70158f; T p=0;T a=c;
	if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
	if (a < abs(c)) { a=c; s = p/4; }
	else s = p/(2*M_PI) * asin (c/a);
	return a*pow(2,-10*t) * sin( (t*d-s)*( 2.0f * M_PI)/p ) + c + b;
}

EASING_FUNCTION(easeInOutElastic)
{
	T s = 1.70158f; T p=0; T a=c;
	if (t==0) return b;  if ((t/=d/2)==2) return b+c;  if (!p) p=d*(.3*1.5);
	if (a < abs(c)) { a=c; s=p/4; }
	else s = p/(2 * M_PI) * asin (c/a);
	if (t < 1) return -.5*(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*M_PI)/p )) + b;
	return a*pow(2,-10*(t-=1)) * sin( (t*d-s)*(2*M_PI)/p )*.5 + c + b;
}

EASING_FUNCTION(easeInBack)
{
	T s = 1.70158f;
	return c*(t/=d)*t*((s+1)*t - s) + b;
}
								
EASING_FUNCTION(easeOutBack)
{
	T s = 1.70158f;
	return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}
																
EASING_FUNCTION(easeInOutBack)
{
	T s = 1.70158f;
	if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
	return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
}

EASING_FUNCTION(easeOutBounce)
{
	if ((t/=d) < (1/2.75)) {
		return c*(7.5625*t*t) + b;
	} else if (t < (2/2.75)) {
		return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
	} else if (t < (2.5/2.75)) {
		return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
	} else {
		return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
	}
}

EASING_FUNCTION(easeInBounce)
{
	return c - easeOutBounce(x, d-t, 0, c, d) + b;
}

EASING_FUNCTION(easeInOutBounce)
{
	if (t < d/2) return easeInBounce(x, t*2, 0, c, d) * .5 + b;
	return easeOutBounce(x, t*2-d, 0, c, d) * .5 + c*.5 + b;
}

#endif
