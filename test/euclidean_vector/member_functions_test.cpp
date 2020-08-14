#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>

TEST_CASE("Member Functions Tests") {
	// At reference
	auto init_list = {33.2, 24.9, 10230.3, 78.0, 93.0, 183.6};
	auto e_vector = comp6771::euclidean_vector(init_list);
	auto const const_e_vector = comp6771::euclidean_vector(init_list);
	SECTION("Checking At Reference") {
		CHECK(e_vector.at(0) == 33.2);
		e_vector.at(0) = 0.0;
		CHECK(e_vector.at(0) == 0.0);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(e_vector.at(0));
			CHECK_THROWS_WITH(e_vector.at(-1), "Index X is not valid for this euclidean_vector object");
			CHECK_THROWS_WITH(e_vector.at(100), "Index X is not valid for this euclidean_vector object");
		}
	}

	// Dimensions
	auto dimension_e_vector = comp6771::euclidean_vector(init_list);
	auto dimension_vector = dimension_e_vector.get_magnitudes();
	SECTION("Checking Dimension") {
		CHECK(dimension_e_vector.dimensions() == static_cast<int>(dimension_vector.size()));
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(dimension_e_vector.dimensions());
		}
	}
}