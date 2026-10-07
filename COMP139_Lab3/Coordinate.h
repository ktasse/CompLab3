#pragma once

struct SphericalCoords {
	double radius{};
	double azimuth{};
	double inclination{};
};

struct RectangularCoords {
	double x{};
	double y{};
	double z{};
};

class Coordinate
{	

private:
	RectangularCoords rectangular{};
	SphericalCoords spherical{};


public:
	Coordinate(SphericalCoords coords);
	Coordinate(RectangularCoords coords);

	RectangularCoords getRectangular() const;
	SphericalCoords getSpherical() const;

	static double getRadius(double x, double y, double z);

	static SphericalCoords rectangularToSpherical(double x, double y, double z);

	static RectangularCoords sphericalToRectangular(double radius, double azimuth, double inclination);
	

};

