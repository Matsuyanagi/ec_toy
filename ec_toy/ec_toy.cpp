#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <boost/format.hpp>

#include "EllipticCurveToy.h"

using namespace Botan;
using namespace boost;

int main() {

    BigInt a("1");
    BigInt b("1");
    BigInt prime("11");

    if ( __argc > 1 ) {
        a = BigInt(__argv[1]);
        if ( __argc > 2 ) {
            b = BigInt(__argv[2]);
            if ( __argc > 3 ) {
                prime = BigInt(__argv[3]);
            }
        }
    }

    // discriminant_ok のテスト
    if ( ! EllipticCurveToy::discriminant_ok(a, b, prime) ) {
        std::cout << boost::format( "discriminant error : a = %1% , b = %2% , prime = %3% " ) % a.to_dec_string() % b.to_dec_string() % prime.to_dec_string() << std::endl;
        return 1;
    }

    // y^2 = x^3 + ax + b (mod prime) の点 (x, y) を求める
    std::vector<PointGFp> points = EllipticCurveToy::GetNPoints( a, b, prime );
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

    // a, b, prime を指定して位数を求める
    int64_t order_count = EllipticCurveToy::GetOrderCount( a, b, prime );
	std::cout << boost::format( "order : %1%" ) % order_count << std::endl;

    return 0;    
}
