#include "pch.h"
#include "Coordinate.h"
#include <cmath>
#include <stdexcept>
#include <numbers>


/*
* Construct coordinate from rectangular coordinates
*
* @param coords  Rectangular coordinates
*/
Coordinate::Coordinate(RectangularCoords coords)
{
   
    rectangular = coords;
    spherical = rectangularToSpherical(coords.x, coords.y, coords.z);
}


/*
* Construct coordinate from spherical coordinates
*
* @param coords  spherical coordinates
*/
Coordinate::Coordinate(SphericalCoords coords)
{
    
    if (coords.radius < 0.0) {
        throw std::invalid_argument("Out of range");
    }
	if (coords.azimuth <= -std::numbers::pi || coords.azimuth > std::numbers::pi) {
		throw std::invalid_argument("Out of range");
	}
	if (coords.inclination <= -std::numbers::pi || coords.inclination > std::numbers::pi) {
		throw std::invalid_argument("Out of range");
	}
   
    spherical = coords;
    rectangular = sphericalToRectangular(coords.radius, coords.azimuth, coords.inclination);
}


/*
* Get rectangular coordinates
*
* @return  Rectangular coordinates
*/
RectangularCoords Coordinate::getRectangular() const
{
   
	return rectangular;
}


/*
* Get spherical coordinates
*
* @return  Spherical coordinates
*/
SphericalCoords Coordinate::getSpherical() const
{
    
    return spherical;
}


/*
* Calculate radius from rectangular coordinates
*
* @param x  X coordinate
* @param y  Y coordinate
* @param z  Z coordinate
* @return  Radius
*/
double Coordinate::getRadius(double x, double y, double z)
{  
    return std::sqrt(x * x + y * y + z * z);
}


/*
* Convert rectangular coordinates to spherical coordinates
*
* @param x  X coordinate
* @param y  Y coordinate
* @param z  Z coordinate
* @return  Spherical coordinates
*/
SphericalCoords Coordinate::rectangularToSpherical(double x, double y, double z)
{
    
	double radius = getRadius(x, y, z);
   
    double azimuth = std::atan2(y, x);
    
	double inclination = std::atan2(std::sqrt(x * x + y * y), z);

    return SphericalCoords{radius, azimuth, inclination};
}


/*
* Convert spherical coordinates to rectangular coordinates
*
* @param radius Distance from origin
* @param azimuth Angle in XY plane
* @param inclination Angle from positive Z axis
* @return  Rectangular coordinates
*/
RectangularCoords Coordinate::sphericalToRectangular(double radius, double azimuth, double inclination)
{
    double x = radius * std::sin(inclination) * std::cos(azimuth);
    double y = radius * std::sin(inclination) * std::sin(azimuth);
    double z = radius * std::cos(inclination);

    return RectangularCoords{ x, y, z };
}