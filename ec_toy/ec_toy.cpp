#include <iostream>
#include <botan/bigint.h>
#include <botan/curve_gfp.h>
#include <botan/ec_group.h>
#include <botan/point_gfp.h>

using namespace Botan;

int main() {
	BigInt a = 33;
	std::cout << a << "\n";
}
