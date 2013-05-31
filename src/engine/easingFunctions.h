//
//  easingFunctions.h
//  jBRefactor
//
//  Created by Ixtli on 10/1/12.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef jBRefactor_easingFunctions_h
#define jBRefactor_easingFunctions_h

/*
 * Generic inlined easing functions. Copied from jQuery UI's core easing
 * definitions almost exactly. (x passed to each function is elided.)
 * 
 * t = current time/frame.
 * b = start value (usually 0)
 * c = change in value, at the END of the anim (usually 1)
 * d = duration in the same units as t
 * return = current position in the same format as b, c
 */

#include <math.h>

typedef float (*EasingFunction)(float, float, float, float);

inline float quadEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * t * t + b;
}

inline float quadEaseOut(float t, float b, float c, float d)
{
	t /= d;
	return -c * t * (t - 2.0f) + b;
}

inline float quadEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2.0f;
	if (t < 1.0f) return c / 2.0f * t * t + b;
	return -c / 2.0f * ((--t) * (t-2.0f) - 1.0f) + b;
}

inline float cubeEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * (t * t * t) + b;
}

inline float cubeEaseOut(float t, float b, float c, float d)
{
	t = t / d - 1.0f;
	return c * (t * t * t - 1.0f) + b;
}

inline float cubeEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2.0f;
	if (t < 1.0f) return c / 2.0f * t * t * t + b;
	t -= 2.0f;
	return c / 2.0f * (t * t * t + 2.0f) + b;
}

inline float quartEaseIn(float t, float b, float c, float d)
{
	return c * (t /= d) * t * t * t + b;
}

inline float quartEaseOut(float t, float b, float c, float d)
{
	return -c * ((t = t / d - 1.0f) * t * t * t - 1.0f) + b;
}

inline float quartEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2.0f) < 1.0f) return c / 2.0f * t * t * t * t + b;
	return -c / 2.0f * ((t -= 2.0f) * t * t * t - 2.0f) + b;
}

inline float quintEaseIn(float t, float b, float c, float d)
{
	return c * (t /= d) * t * t * t * t + b;
}

inline float quintEaseOut(float t, float b, float c, float d)
{
	return c * ((t = t / d - 1.0f) * t * t * t * t + 1.0f) + b;
}

inline float quintEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2.0f) < 1.0f) return c / 2.0f * t * t * t * t * t + b;
	return c / 2.0f * ((t -= 2.0f) * t * t * t * t + 2.0f) + b;
}

inline float sineEaseIn(float t, float b, float c, float d)
{
	return -c * cosf(t / d * M_PI_2) + c + b;
}

inline float sineEaseOut(float t, float b, float c, float d)
{
	return c * sinf(t / d * M_PI_2) + b;
}

inline float sineEaseInOut(float t, float b, float c, float d)
{
	return -c / 2.0f * (cosf(M_PI * t / d) - 1.0f) + b;
}

inline float expoEaseIn(float t, float b, float c, float d)
{
	return (t == 0.0f) ? b : c * powf(2.0f, 10.0f * (t / d - 1.0f)) + b;
}

inline float expoEaseOut(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b;
}

inline float expoEaseInOut(float t, float b, float c, float d)
{
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2.0f) < 1.0f) return c / 2.0f * powf(2.0f, 10.0f * (t - 1.0f)) + b;
	return c / 2.0f * (-powf(2.0f, -10.0f * --t) + 2.0f) + b;
}

inline float circEaseIn(float t, float b, float c, float d)
{
	return -c * (sqrtf(1.0f - (t /= d) * t) - 1.0f) + b;
}

inline float circEaseOut(float t, float b, float c, float d)
{
	return c * sqrtf(1.0f - (t = t / d - 1.0f) * t) + b;
}

inline float circEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2.0f) < 1.0f)
		return -c / 2.0f * (sqrtf(1.0f - t * t) - 1.0f) + b;
	
	return c / 2.0f * (sqrtf(1.0f - (t -= 2.0f) * t) + 1.0f) + b;
}

inline float elasticEaseIn(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float p = 0.0f;
	float a = c;
	if (t == 0.0f) return b;
	if ((t /= d) == 1.0f) return b + c;
	if (!p) p = d * .3f;
	if (a < fabs(c)) {
		a = c;
		s = p / 4.0f;
	} else s = p / (2.0f * M_PI) * asinf(c / a);
	return -(a * powf(2.0f, 10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * M_PI) / p)) + b;
}

inline float elasticEaseOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float p = 0.0f;
	float a = c;
	if (t == 0.0f) return b;
	if ((t /= d) == 1.0f) return b + c;
	if (!p) p = d * .3f;
	if (a < fabs(c)) {
		a = c;
		s = p / 4.0f;
	} else s = p / (2.0f * M_PI) * asinf(c / a);
	return a * powf(2.0f, -10.0f * t) * sinf((t * d - s) * (2.0f * M_PI) / p) + c + b;
}

inline float elasticEaseInOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float p = 0.0f;
	float a = c;
	if (t == 0.0f) return b;
	if ((t /= d / 2.0f) == 2.0f) return b + c;
	if (!p) p = d * (.3f * 1.5f);
	if (a < fabs(c)) {
		a = c;
		s = p / 4.0f;
	} else s = p / (2.0f * M_PI) * asinf(c / a);
	if (t < 1.0f) return -.5f * (a * powf(2.0f, 10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * M_PI) / p)) + b;
	return a * powf(2.0f, -10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * M_PI) / p) * .5f + c + b;
}

inline float backEaseIn(float t, float b, float c, float d, float s = 1.70158f)
{
	return c * (t /= d) * t * ((s + 1.0f) * t - s) + b;
}

inline float backEaseOut(float t, float b, float c, float d, float s = 1.70158f)
{
	return c * ((t = t / d - 1.0f) * t * ((s + 1.0f) * t + s) + 1.0f) + b;
}

inline float backEaseInOut(float t, float b, float c, float d, float s = 1.70158f)
{
	if ((t /= d / 2.0f) < 1.0f)
		return c / 2.0f * (t * t * (((s *= (1.525f)) + 1.0f) * t - s)) + b;
	
	return c / 2.0f * ((t -= 2.0f) * t * (((s *= (1.525f)) + 1.0f) * t + s) + 2.0f) + b;
}

inline float bounceEaseOut(float t, float b, float c, float d)
{
	if ((t /= d) < (1.0f / 2.75f)) {
		return c * (7.5625f * t * t) + b;
	} else if (t < (2.0f / 2.75f)) {
		return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + 0.75f) + b;
	} else if (t < (2.5f / 2.75f)) {
		return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + 0.9375f) + b;
	} else {
		return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + 0.984375f) + b;
	}
}

inline float bounceEaseIn(float t, float b, float c, float d)
{
	return c - bounceEaseOut(d - t, 0.0f, c, d) + b;
}

inline float bounceEaseInOut(float t, float b, float c, float d)
{
	if (t < d / 2.0f) return bounceEaseIn(t * 2.0f, 0.0f, c, d) * .5f + b;
	return bounceEaseOut(t * 2.0f - d, 0.0f, c, d) * .5f + c * .5f + b;
}

#endif
