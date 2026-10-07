#include "pch.h"
#include <numbers>
#include "Coordinate.h"

const double kTextEps = 1.0e-12;

TEST(ConstructorTest, RectToSpherical)
{
	const auto rectangular = RectangularCoords{ 1.0, 2.0, 3.0 };
	const Coordinate coord(rectangular);

	const auto rectangularRet = coord.getRectangular();
	ASSERT_NEAR(rectangularRet.x, 1.0, kTextEps);
	ASSERT_NEAR(rectangularRet.y, 2.0, kTextEps);
	ASSERT_NEAR(rectangularRet.z, 3.0, kTextEps);

	const auto sphericalRet = coord.getSpherical();
	ASSERT_NEAR(sphericalRet.radius, std::sqrt(14.0), kTextEps);
	ASSERT_NEAR(sphericalRet.azimuth, std::atan2(2.0, 1.0), kTextEps);
	ASSERT_NEAR(sphericalRet.inclination, std::atan2(std::sqrt(5.0), 3.0), kTextEps);
	ASSERT_NEAR(Coordinate::getRadius(1.0, 2.0, 3.0), std::sqrt(14.0), kTextEps);
}

TEST(ConstructorTest, SphericalToRect)
{
	const auto spherical = SphericalCoords{ std::sqrt(14.0), std::atan2(2.0, 1.0), std::atan2(std::sqrt(5.0), 3.0) };
	const Coordinate coord(spherical);

	const auto rectangularRet = coord.getRectangular();
	ASSERT_NEAR(rectangularRet.x, 1.0, kTextEps);
	ASSERT_NEAR(rectangularRet.y, 2.0, kTextEps);
	ASSERT_NEAR(rectangularRet.z, 3.0, kTextEps);

	const auto sphericalRet = coord.getSpherical();
	ASSERT_NEAR(sphericalRet.radius, std::sqrt(14.0), kTextEps);
	ASSERT_NEAR(sphericalRet.azimuth, std::atan2(2.0, 1.0), kTextEps);
	ASSERT_NEAR(sphericalRet.inclination, std::atan2(std::sqrt(5.0), 3.0), kTextEps);
	ASSERT_NEAR(Coordinate::getRadius(1.0, 2.0, 3.0), std::sqrt(14.0), kTextEps);
}

TEST(FunctionTest, getRadius)
{
	ASSERT_NEAR(Coordinate::getRadius(1.0, 1.5, 0.0), std::sqrt(3.25), kTextEps);
}

TEST(FunctionTest, rectangularToSpherical)
{
	const RectangularCoords rect2{ -2.0, -1.0, -2.0 };
	const auto spherical2 = Coordinate::rectangularToSpherical(rect2.x, rect2.y, rect2.z);
	ASSERT_NEAR(spherical2.radius, 3.0, kTextEps);
	ASSERT_NEAR(spherical2.azimuth, -2.677945044588987, kTextEps);
	ASSERT_NEAR(spherical2.inclination, 2.300523983021863, kTextEps);
}

TEST(FunctionTest, rectangularToSpherical2)
{
	const RectangularCoords rect2{ 1.0, -2.0, 0.0 };
	const auto spherical2 = Coordinate::rectangularToSpherical(rect2.x, rect2.y, rect2.z);
	ASSERT_NEAR(spherical2.radius, std::sqrt(5.0), kTextEps);
	ASSERT_NEAR(spherical2.azimuth, -1.1071487177940904, kTextEps);
	ASSERT_NEAR(spherical2.inclination, 1.5707963267948966, kTextEps);
}

TEST(FunctionTest, sphericalToRectangular1)
{
	const SphericalCoords spherical{ 5.0, -5.0 * std::numbers::pi / 6.0, std::numbers::pi / 8.0 };
	const auto rectangular = Coordinate::sphericalToRectangular(spherical.radius, spherical.azimuth, spherical.inclination);
	ASSERT_NEAR(rectangular.x, -1.657067870177959, kTextEps);
	ASSERT_NEAR(rectangular.y, -0.9567085809127243, kTextEps);
	ASSERT_NEAR(rectangular.z, 4.6193976625564335, kTextEps);
}

TEST(FunctionTest, sphericalToRectangular2)
{
	const SphericalCoords spherical{ 2.0, 0.1 * std::numbers::pi, 0.5 * std::numbers::pi };
	const auto rectangular = Coordinate::sphericalToRectangular(spherical.radius, spherical.azimuth, spherical.inclination);
	ASSERT_NEAR(rectangular.x, 1.902113032590307, kTextEps);
	ASSERT_NEAR(rectangular.y, 0.6180339887498948, kTextEps);
	ASSERT_NEAR(rectangular.z, 0, kTextEps);
}

TEST(InvalidArgumentTest, NegativeRadius)
{
	SphericalCoords spherical1{ -1.0, 0.0, 0.0 };

	EXPECT_THROW({ Coordinate coord(spherical1); },std::invalid_argument);
}

TEST(InvalidArgumentTest, ZeroRadius)
{
	SphericalCoords spherical1{ 0.0, 0.0, 0.0 };

	EXPECT_NO_THROW({ Coordinate coord(spherical1); });
}

TEST(InvalidArgumentTest, AzimuthOutOfBounds)
{
	SphericalCoords spherical1{ 1.0, -std::numbers::pi, 0.0 };

	EXPECT_THROW({ Coordinate coord(spherical1); }, std::invalid_argument);
}

TEST(InvalidArgumentTest, AzimuthValidBound)
{
	SphericalCoords spherical1{ 1.0, std::numbers::pi, 0.0 };

	EXPECT_NO_THROW({ Coordinate coord(spherical1); });
}

TEST(InvalidArgumentTest, InclinationOutOfBounds)
{
	SphericalCoords spherical1{ 1.0, 0.0, -std::numbers::pi };

	EXPECT_THROW({ Coordinate coord(spherical1); }, std::invalid_argument);
}

TEST(InvalidArgumentTest, InclinationValidBound)
{
	SphericalCoords spherical1{ 1.0, 0.0, std::numbers::pi };

	EXPECT_NO_THROW({ Coordinate coord(spherical1); });
}