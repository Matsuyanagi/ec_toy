#include "pch.h"

#include "../ec_toy/EllipticCurveToy.h"

using namespace Botan;

TEST( TestEllipticCurveToy, NPoints ) {
	std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( 1, 1, 11 );

	EXPECT_EQ(14, points.size());
	EXPECT_TRUE(true);
}