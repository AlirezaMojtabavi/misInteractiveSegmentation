/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 The Voreen Team. <http://www.voreen.org>   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

/**
 * This module contains all functions which are used for the raysetup
 * as well as the ray traversal within a raycaster.
 * RC_BEGIN_LOOP and RC_END_LOOP are used within the raycaster fragment
 * shaders to control the ray traversal.
 */

uniform float samplingStepSize_;
uniform float isoValue_;

/**
 * This parameter defines the minimum opacity saturation
 * a ray has to reach before it is terminated.
 * Setting this value to 1.0 disables early ray termination.
 */
#define EARLY_RAY_TERMINATION_OPACITY 0.95

/***
 * Calculates the direction of the ray and returns the number
 * of steps and the direction.
 ***/
void raySetup(in vec3 first, in vec3 last, out vec3 rayDirection, out float tIncr, out float tEnd) {
    // calculate ray parameters
    tIncr = samplingStepSize_;

    rayDirection = last - first;
    tEnd = length(rayDirection);
    rayDirection = normalize(rayDirection);
    #ifdef ADAPTIVE_SAMPLING
        directionWithStepSize = rayDirection * tIncr;
    #endif
}

/***
 * Applies early ray termination. The current opacity is compared to
 * the maximum opacity. In case it is greater, the opacity is set to
 * 1.0 and true is returned, otherwise false is returned.
 ***/
bool earlyRayTermination(inout float opacity, in float maxOpacity) {
    if (opacity >= maxOpacity) {
        opacity = 1.0;
        return true;
    } else {
        return false;
    }
}

#if defined(VRN_OS_APPLE) && defined(VRN_VENDOR_ATI)
  // We do manual inlining in order to deal with older ATI boards on Mac where these function
  // calls seem to drastically reduce rendering speed (triggering fallback to software mode).
  #define RC_EARLY_RAY_TERMINATION(opacity, maxOpacity, finished) \
    if (opacity >= maxOpacity) {                                  \
        opacity = 1.0;                                            \
        finished = true;                                          \
    }
#else
  // Just wrap the usual functions
  #define RC_EARLY_RAY_TERMINATION(opacity, maxOpacity, finished) \
    finished = earlyRayTermination(opacity, maxOpacity)
  #define WRITE_DEPTH_VALUE(t, tEnd, entryPointsDepth, entryParameters, exitPointsDepth, exitParameters) \
    gl_FragDepth = getDepthValue(t, tEnd, entryPointsDepth, entryParameters, exitPointsDepth, exitParameters);
#endif


// Does the hardwarr support a shader program length that allows us to use a single loop or do
// we need two nested loops?
#ifdef VRN_MAX_PROGRAM_LOOP_COUNT
    // - ATI preprocessor doesn't support shortcut evaluation)
    // - Mac/GeForce 9400M reports integer 'constant overflow'
    #if (VRN_MAX_PROGRAM_LOOP_COUNT >= 256*256) && !defined(VRN_OS_APPLE)
        #define USE_SINGLE_LOOP
    #endif
#endif

#ifdef USE_SINGLE_LOOP
    // Nvidia seems to support a loop count > 256 only for
    // for-loops and not for while-loops on Geforce 8800 GTX.
    // On GTX280 a for-loop is still slightly faster than a while-loop. joerg
    #if defined(VRN_MAX_PROGRAM_LOOP_COUNT)
        #define RAYCASTING_LOOP_COUNT VRN_MAX_PROGRAM_LOOP_COUNT
    #else
        #define RAYCASTING_LOOP_COUNT 255*255
    #endif
    #define RC_BEGIN_LOOP_FOR                                              \
      for (int loop=0; !finished && loop<RAYCASTING_LOOP_COUNT; loop++) {
    #define RC_END_LOOP_BRACES }
#else
    // Use two nested loops, should be supported everywhere
    #define RC_BEGIN_LOOP_FOR                                   \
      for (int loop0=0; !finished && loop0<255; loop0++) {      \
          for (int loop1=0; !finished && loop1<255; loop1++) {
    #define RC_END_LOOP_BRACES } }
#endif

/***
 * The beginning of a typical raycasting loop.
 */
#define RC_BEGIN_LOOP                                         \
    float tDepth = -1.0;                                      \
    bool finished = false;                                    \
    RC_BEGIN_LOOP_FOR

/***
 * The end of a typical raycasting loop. If adaptive sampling
 * is used for rendering bricked volumes, t is increased by a
 * multiple of tIncr, thereby skipping several samples.
 */
#ifdef ADAPTIVE_SAMPLING
#define RC_END_LOOP(result)                                        \
            RC_EARLY_RAY_TERMINATION(result.a, EARLY_RAY_TERMINATION_OPACITY, finished);    \
            t += (tIncr * float(numberOfSkippedSamples));          \
            finished = finished || (t > tEnd);                     \
    RC_END_LOOP_BRACES                                             \
    WRITE_DEPTH_VALUE(tDepth, tEnd, entryPointsDepth_, entryParameters_, exitPointsDepth_, exitParameters_);
#else
#define RC_END_LOOP(result)                                        \
            RC_EARLY_RAY_TERMINATION(result.a, EARLY_RAY_TERMINATION_OPACITY, finished);    \
            t += tIncr;                                            \
            finished = finished || (t > tEnd);                     \
    RC_END_LOOP_BRACES                                             \
    WRITE_DEPTH_VALUE(tDepth, tEnd, entryPointsDepth_, entryParameters_, exitPointsDepth_, exitParameters_);

#endif

/**
* In order to keep the shaders as free as possible from dealing
* with bricking and adaptive sampling, these defines can be placed
* before and after the compositing function calls to enable adaptive
* sampling when bricking is used. For normal datasets these defines
* will have no impact at all.
*/
#ifdef ADAPTIVE_SAMPLING
#define RC_BEGIN_COMPOSITING \
    for (int i=0; i<numberOfSkippedSamples; i++) {
#else
    #define RC_BEGIN_COMPOSITING
#endif

#ifdef ADAPTIVE_SAMPLING
#define RC_END_COMPOSITING \
    }
#else
#define RC_END_COMPOSITING
#endif
