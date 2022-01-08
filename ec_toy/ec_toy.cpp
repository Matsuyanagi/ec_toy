#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "EllipticCurveToy.h"

using namespace Botan;

int main() {

    // y^2 = x^3 + ax + b (mod prime) の点 (x, y) を求める
    std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( 1, 1, 11 );
    for ( auto &&point : points ) {
		std::cout << EllipticCurveToy::StringPointGFp( point ) << std::endl;;
	}

    // それぞれの点 P の 2P, 3P, 4P,... をリストにとって表示
    for ( auto &&point : points ) {
        std::vector<Botan::PointGFp> npoints = EllipticCurveToy::GetMultiplyPoints( point );

		std::cout << npoints.size() << " : ";
        for ( auto &&npoint : npoints ) {
            std::cout << EllipticCurveToy::StringPointGFp( npoint );
        }
		std::cout << std::endl;
	}


    return 0;    
}
