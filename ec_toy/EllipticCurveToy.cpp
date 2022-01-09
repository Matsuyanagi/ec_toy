#include "EllipticCurveToy.h"

using namespace Botan;

// 判別式 4a^3 + 27b^2(mod prime) が ≠ 0 ならば true
bool EllipticCurveToy::discriminant_ok( const BigInt &a, const BigInt &b, const BigInt &prime ) {
	BigInt d( ( a * a * a * 4 + b * b * 27 ) % prime );
	return d.is_nonzero();
}

// 平方根テーブル作成
EllipticCurveToy::BigIntSqrtTableType EllipticCurveToy::CreateSqrtTable( const BigInt &prime ) {
	BigIntSqrtTableType sqrt_table;
	BigInt prime_half = prime >> 1;
	for ( BigInt i = 0; i <= prime_half; i++ ) {
		sqrt_table[ ( i * i ) % prime ] = i;
	}
	return sqrt_table;
}

// ポイントを文字列化
std::string EllipticCurveToy::StringPointGFp( const PointGFp &p ) {
	std::string s;
	if ( p.is_zero() ) {
		s = "( - : - )";
	} else {
		s = "( ";
		s += p.get_affine_x().to_dec_string();
		s += " : ";
		s += p.get_affine_y().to_dec_string();
		s += " )";
	}
	return s;
}

// y^2 = x^3 + ax + b (mod prime) の点群 (x, y) を求める
std::vector<PointGFp> EllipticCurveToy::GetNPoints( const BigInt &a, const BigInt &b, const BigInt &prime )
{
	// 平方根テーブル
	BigIntSqrtTableType sqrt_table = CreateSqrtTable( prime );

	std::vector<PointGFp> points;

	// 曲線
	CurveGFp curve( prime, a, b );

	for ( BigInt i = 0; i < prime; i++ ) {
		BigInt y2 = i * i * i + a * i + b;
		y2 %= prime;
		if ( auto it = sqrt_table.find( y2 ); it != sqrt_table.end() ) {
			const BigInt y = it->second;

			points.push_back( PointGFp( curve, i, y ) );
			if ( y != 0 ) {
				PointGFp point( curve, i, prime - y );
				points.push_back( point );
			}
		}
	}
	PointGFp p0( curve );
	p0.zero();
	points.push_back( p0 );

	return points;
}

// それぞれの点 P の 2P, 3P, 4P,... をリスト化する
// @param point 点
// @return P, 2P, 3P, ... リスト。最後のゼロ点は含まない。
std::vector<Botan::PointGFp> EllipticCurveToy::GetMultiplyPoints( const Botan::PointGFp &point )
{
	std::vector<BigInt> workspace( Botan::PointGFp::WORKSPACE_SIZE );
	std::vector<PointGFp> points;

	PointGFp ans = point;
	while ( !ans.is_zero() ) {
		points.emplace_back( ans );
		ans.add( point, workspace );
	}
	points.emplace_back( ans );

	return points;
}

// a, b, prime を指定して位数を求める
int64_t EllipticCurveToy::GetOrderCount( const Botan::BigInt &a, const Botan::BigInt &b, const Botan::BigInt &prime )
{
	if ( ! discriminant_ok( a, b, prime ) ){
		return 0;
	}
	
	const BigIntSqrtTableType sqrt_table = CreateSqrtTable( prime );
	int64_t order = 0;

	for ( Botan::BigInt i = 0; i < prime; i++ ) {
		Botan::BigInt y2 = i * i * i + a * i + b;
		y2 %= prime;
		if ( sqrt_table.contains( y2 ) ) {
			Botan::BigInt y = sqrt_table.at( y2 );

			order++;
			if ( y.is_nonzero() ) {  //	y != 0 なら -y もカウントする
				order++;
			}
		}
	}
	order++;  // O : 無限点 O

	return order;

}


