#pragma once
#include <exception>
#include <map>
#include <string>
#include <vector>
#include <botan/bigint.h>
#include <botan/curve_gfp.h>
#include <botan/ec_group.h>
#include <botan/point_gfp.h>


class EllipticCurveToy {
public:
	typedef std::map<Botan::BigInt, Botan::BigInt> BigIntSqrtTableType;

	// 判別式 4a^3 + 27b^2(mod prime) が ≠ 0 ならば true
	static bool discriminant_ok( const Botan::BigInt &a, const Botan::BigInt &b, const Botan::BigInt &prime );
	// 平方根テーブル作成
	static BigIntSqrtTableType CreateSqrtTable( const Botan::BigInt &prime );

	// 点GFpを文字列化
	static std::string StringPointGFp( const Botan::PointGFp &p );

	// y^2 = x^3 + ax + b (mod prime) の点 (x, y) を求める
	static std::vector<Botan::PointGFp> GetNPoints( const Botan::BigInt &a, const Botan::BigInt &b, const Botan::BigInt &prime );

	// それぞれの点 P の 2P, 3P, 4P,... をリスト化する
	static std::vector<Botan::PointGFp> GetMultiplyPoints( const Botan::PointGFp &point );

	// a, b, prime を指定して位数を求める
	static int64_t GetOrderCount( const Botan::BigInt &a, const Botan::BigInt &b, const Botan::BigInt &prime );
	

private:
	BigIntSqrtTableType sqrt_table;


	
};
