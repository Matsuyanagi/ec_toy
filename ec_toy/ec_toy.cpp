#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <fmt/core.h>
#include <botan/numthry.h>
#include <botan/chacha_rng.h>

#include "EllipticCurveToy.h"

using namespace Botan;

int main() {

    BigInt a("1");
    BigInt b("1");
    BigInt prime("11");
    ChaCha_RNG rng;

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
        std::cout << fmt::format( "discriminant error : a = {} , b = {} , prime = {} ", a.to_dec_string(), b.to_dec_string(), prime.to_dec_string() ) << std::endl;
        return 1;
    }
    std::cout << fmt::format( "a = {} , b = {} , prime = {}", a.to_dec_string(), b.to_dec_string(), prime.to_dec_string() ) << std::endl;
    // a, b, prime を指定して位数を求める
    int64_t order_count = EllipticCurveToy::GetOrderCount( a, b, prime );
	std::cout << fmt::format( "order : {}" , order_count ) << std::endl;

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

    std::cout << "a\\b\t";
    for ( int64_t a = 0; a < prime; a++ ) {
        std::cout << a << "\t";
    }
	std::cout << std::endl;
    for ( int64_t a = 0; a < prime; a++ ) {
        std::cout << a << "\t";
        for ( int64_t b = 0; b < prime; b++ ) {
            if ( EllipticCurveToy::discriminant_ok(a, b, prime) ) {
                BigInt order_count = EllipticCurveToy::GetOrderCount( a, b, prime );

                if ( Botan::is_prime(order_count, rng ) ) {
                    std::cout << "[" << order_count << "]" << "\t";
                } else {
                    std::cout << order_count << "\t";
                }
            }else{
                std::cout << "-\t";
            }
        }
		std::cout << std::endl;
    }
    return 0;    
}
