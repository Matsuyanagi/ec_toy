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

    return 0;    
}
