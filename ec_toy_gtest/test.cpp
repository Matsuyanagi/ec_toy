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

TEST( TestEllipticCurveToy, AddPoints ) {
	int32_t a = 1;
	int32_t b = 1;
	int32_t prime = 11;
	std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( a, b, prime );

	CurveGFp curve( prime, a, b );
	PointGFp point( curve, 0, 1 );
    std::vector<Botan::PointGFp> npoints = EllipticCurveToy::GetMultiplyPoints( point );
	std::vector<PointGFp> model_0_1_points = {
		PointGFp( curve, 0, 1 ),
		PointGFp( curve, 3, 3 ),
		PointGFp( curve, 6, 6 ),
		PointGFp( curve, 6, 5 ),
		PointGFp( curve, 3, 8 ),
		PointGFp( curve, 0, 10 ),
		PointGFp( curve ),
	};

	for ( int i=0; auto &&npoint : npoints ) {
		if ( model_0_1_points[i].is_zero() ) {
			EXPECT_TRUE( npoint.is_zero() );
		} else {
			npoint.force_affine();
			EXPECT_EQ( model_0_1_points[i], npoint );
		}
		i++;
	}
}

TEST( TestEllipticCurveToy, AddPoints_13 ) {
	int32_t a = 1;
	int32_t b = 1;
	int32_t prime = 13;
	std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( a, b, prime );

	CurveGFp curve( prime, a, b );
	PointGFp point( curve, 1, 4 );
    std::vector<Botan::PointGFp> npoints = EllipticCurveToy::GetMultiplyPoints( point );
	
	//         18 : ( 1 : 4 ), ( 8 : 12 ), ( 0 : 12 ), ( 11 : 11 ), ( 5 : 1 ), ( 10 : 6 ), ( 12 : 8 ), ( 4 : 2 ), ( 7 : 0 ), ( 4 : 11 ), ( 12 : 5 ), ( 10 : 7 ), ( 5 : 12 ), ( 11 : 2 ), ( 0 : 1 ), ( 8 : 1 ), ( 1 : 9 ), ( - : - )
	std::vector<PointGFp> model_1_4_points = {
		PointGFp( curve, 1, 4 ),
		PointGFp( curve, 8, 12 ),
		PointGFp( curve, 0, 12 ),
		PointGFp( curve, 11, 11 ),
		PointGFp( curve, 5, 1 ),
		PointGFp( curve, 10, 6 ),
		PointGFp( curve, 12, 8 ),
		PointGFp( curve, 4, 2 ),
		PointGFp( curve, 7, 0 ),
		PointGFp( curve, 4, 11 ),
		PointGFp( curve, 12, 5 ),
		PointGFp( curve, 10, 7 ),
		PointGFp( curve, 5, 12 ),
		PointGFp( curve, 11, 2 ),
		PointGFp( curve, 0, 1 ),
		PointGFp( curve, 8, 1 ),
		PointGFp( curve, 1, 9 ),
		PointGFp( curve ),
	};

	for ( int i=0; auto &&npoint : npoints ) {
		if ( model_1_4_points[i].is_zero() ) {
			EXPECT_TRUE( npoint.is_zero() );
		} else {
			npoint.force_affine();
			EXPECT_EQ( model_1_4_points[i], npoint );
		}
		i++;
	}
}

TEST( TestEllipticCurveToy, Order ) {

	EXPECT_EQ( 14, EllipticCurveToy::GetOrderCount( 1, 1, 11 ) );
	EXPECT_EQ( 18, EllipticCurveToy::GetOrderCount( 1, 1, 13 ) );
	EXPECT_EQ( 35, EllipticCurveToy::GetOrderCount( 1, 1, 41 ) );
	EXPECT_EQ( 987, EllipticCurveToy::GetOrderCount( 1, 1, 977 ) );


}
