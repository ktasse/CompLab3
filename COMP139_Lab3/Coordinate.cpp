#include "pch.h"
#include "Coordinate.h"
#include <cmath>
#include <stdexcept>
#include <numbers>

// Constructor using rectangular coordinates
Coordinate::Coordinate(RectangularCoords coords)
{
    // Store rectangular coordinates
    rectangular = coords;
    // Calculate and store spherical coordinates
    spherical = rectangularToSpherical(coords.x, coords.y, coords.z);
}

// Constructor using spherical coordinates
Coordinate::Coordinate(SphericalCoords coords)
{
    // Check that spherical coordinates are valid
    if (coords.radius < 0.0) {
        throw std::invalid_argument("Out of range");
    }
	if (coords.azimuth <= -std::numbers::pi || coords.azimuth > std::numbers::pi) {
		throw std::invalid_argument("Out of range");
	}
	if (coords.inclination <= -std::numbers::pi || coords.inclination > std::numbers::pi) {
		throw std::invalid_argument("Out of range");
	}
    // Store spherical coordinates
    spherical = coords;
    // Calculate and store rectangular coordinates
    rectangular = sphericalToRectangular(coords.radius, coords.azimuth, coords.inclination);
}

// Return rectangular coordinates
RectangularCoords Coordinate::getRectangular() const
{
    // Return stored rectangular coordinates
	return rectangular;
}

// Return spherical coordinates
SphericalCoords Coordinate::getSpherical() const
{
    // Return stored spherical coordinates
    return spherical;
}

// Calculate radius from x, y, z
double Coordinate::getRadius(double x, double y, double z)
{
    
    return std::sqrt(x * x + y * y + z * z);
}

// Convert rectangular coordinates to spherical coordinates
SphericalCoords Coordinate::rectangularToSpherical(double x, double y, double z)
{
    
	double radius = getRadius(x, y, z);
   
    double azimuth = std::atan2(y, x);
    
	double inclination = std::atan2(std::sqrt(x * x + y * y), z);

    return SphericalCoords{radius, azimuth, inclination};
   
    
}

// Convert spherical coordinates to rectangular coordinates
RectangularCoords Coordinate::sphericalToRectangular(double radius, double azimuth, double inclination)
{
    double x = radius * std::sin(inclination) * std::cos(azimuth);
    double y = radius * std::sin(inclination) * std::sin(azimuth);
    double z = radius * std::cos(inclination);

    return RectangularCoords{ x, y, z };


}