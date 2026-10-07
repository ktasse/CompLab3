#pragma once


//Structs for each coordinate type

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

	/*
	* Construct coordinate from spherical coordinates
	* Error checks input values: 
	* radius >= 0
	* -pi < azimuth <= pi 
	* -pi < inclination <= pi
	* If value inputed is out of this range function will throw an error
	* 
	* @param coords  spherical coordinates
	*/
	Coordinate(SphericalCoords coords);

	/*
	* Construct coordinate from rectangular coordinates		*
	* @param coords  Rectangular coordinates
	*/
	Coordinate(RectangularCoords coords);

	/*
	* Get rectangular coordinates
	*
	* @return  Rectangular coordinates
	*/
	RectangularCoords getRectangular() const;

	/*
	* Get spherical coordinates
	*
	* @return  Spherical coordinates
	*/
	SphericalCoords getSpherical() const;

	/*
	* Calculate radius from rectangular coordinates
	*
	* @param x  X coordinate
	* @param y  Y coordinate
	* @param z  Z coordinate
	* @return  Radius
	*/
	static double getRadius(double x, double y, double z);

	/*
	* Convert rectangular coordinates to spherical coordinates
	*
	* @param x  X coordinate
	* @param y  Y coordinate
	* @param z  Z coordinate
	* @return  Spherical coordinates
	*/
	static SphericalCoords rectangularToSpherical(double x, double y, double z);

	/*
	* Convert spherical coordinates to rectangular coordinates
	*
	* @param radius Distance from origin
	* @param azimuth Angle in XY plane
	* @param inclination Angle from positive Z axis
	* @return  Rectangular coordinates
	*/
	static RectangularCoords sphericalToRectangular(double radius, double azimuth, double inclination);
	

};

