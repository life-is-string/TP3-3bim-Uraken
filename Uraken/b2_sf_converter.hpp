/*
 * b2_sf_converter.hpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: user
 */

#ifndef B2_SF_CONVERTER_HPP_
#define B2_SF_CONVERTER_HPP_

namespace converter
{
   constexpr double PIXELS_PER_METERS = 32.0;
   constexpr double PI = 3.14159265358979323846;

   template<typename T>
   constexpr T pixelsToMeters(const T& x){return x/PIXELS_PER_METERS;};

   template<typename T>
   constexpr T metersToPixels(const T& x){return x*PIXELS_PER_METERS;};

   template<typename T>
   constexpr T degToRad(const T& x){return PI*x/180.0;};

   template<typename T>
   constexpr T radToDeg(const T& x){return 180.0*x/PI;}
}

#endif /* B2_SF_CONVERTER_HPP_ */
