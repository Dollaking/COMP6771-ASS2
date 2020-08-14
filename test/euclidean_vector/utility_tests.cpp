#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>

TEST_CASE("Utility Tests") {
	// Euclidean Norm
	auto norm_list = {1.0, 2.0, 3.0};
	auto e_vector = comp6771::euclidean_vector(norm_list);
	SECTION("Checking Euclidean Norm") {
		CHECK(comp6771::euclidean_norm(e_vector) == sqrt(14));
		CHECK(comp6771::euclidean_norm(e_vector) == sqrt(14));
		e_vector[0] = 0;
		CHECK(comp6771::euclidean_norm(e_vector) != sqrt(14));
		e_vector[0] = 1.0;
		CHECK(comp6771::euclidean_norm(e_vector) == sqrt(14));
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_norm(e_vector));
		}
	}

	// Unit
	auto unit_vector = comp6771::euclidean_vector(norm_list);
	unit_vector /= sqrt(14);
	SECTION("Checking Unit") {
		CHECK(comp6771::unit(e_vector) == unit_vector);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::unit(e_vector));
			CHECK_THROWS_WITH(comp6771::unit(comp6771::euclidean_vector()),
			                  "euclidean_vector with zero euclidean normal does not have a unit "
			                  "vector");
		}
	}

	// Dot Product
	auto dot_vector = comp6771::euclidean_vector({1, 2});
	auto dot_vector2 = comp6771::euclidean_vector({3, 4});

	SECTION("Checking Dot Product") {
		CHECK(comp6771::dot(dot_vector, dot_vector2) == 11);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::dot(dot_vector, dot_vector2));
			CHECK_THROWS_WITH(comp6771::dot(dot_vector, e_vector),
			                  "Dimensions of LHS(X) and RHS(Y) do not match");
		}
	}
}