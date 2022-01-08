#include "pch.h"

#include "../ec_toy/EllipticCurveToy.h"

using namespace Botan;

TEST( TestEllipticCurveToy, NPoints ) {
	int32_t a = 1;
	int32_t b = 1;
	int32_t prime = 11;
	std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( a, b, prime );

	EXPECT_EQ(14, points.size());

	// 曲線
	CurveGFp curve( prime, a, b );
	std::vector<PointGFp> model_points = {
		PointGFp( curve, 0, 1 ),
		PointGFp( curve, 0, 10 ),
		PointGFp( curve, 1, 5 ),
		PointGFp( curve, 1, 6 ),
		PointGFp( curve, 2, 0 ),
		PointGFp( curve, 3, 3 ),
		PointGFp( curve, 3, 8 ),
		PointGFp( curve, 4, 5 ),
		PointGFp( curve, 4, 6 ),
		PointGFp( curve, 6, 5 ),
		PointGFp( curve, 6, 6 ),
		PointGFp( curve, 8, 2 ),
		PointGFp( curve, 8, 9 ),
	};
	
	for ( int i=0; auto &&point : points ) {
		if ( i == points.size() - 1 ) {
			EXPECT_TRUE( point.is_zero() );
		} else {
			EXPECT_EQ( model_points[i], point );
		}
		i++;
	}
}