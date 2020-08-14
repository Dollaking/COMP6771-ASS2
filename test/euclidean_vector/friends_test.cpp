#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>

TEST_CASE("Friend Tests") {
	// Equal and Not Equal reference
	auto init_list = {33.2, 24.9, 10230.3, 78.0, 93.0, 183.6};
	auto e_vector = comp6771::euclidean_vector(init_list);
	auto e_vector_copy = comp6771::euclidean_vector(init_list);
	auto e_vector_diff = comp6771::euclidean_vector(init_list);
	e_vector_diff[0] = 0.0;
	SECTION("Checking Equal and Not Equal") {
		CHECK(e_vector == e_vector_copy);
		CHECK(!(e_vector_diff == e_vector));
		CHECK(e_vector != e_vector_diff);
		CHECK(!(e_vector != e_vector_copy));
	}

	// Addition, Subtraction, Multiply, Divide
	auto one = comp6771::euclidean_vector(5, 1.0);
	auto one_vector = one.get_magnitudes();
	auto two = comp6771::euclidean_vector(5, 2.0);
	auto two_vector = two.get_magnitudes();
	auto five = comp6771::euclidean_vector(5, 5.0);
	auto five_vector = five.get_magnitudes();
	auto ten = comp6771::euclidean_vector(5, 10.0);
	auto ten_vector = ten.get_magnitudes();
	auto addition = one + one;
	auto subtraction = ten - five;
	auto division = ten / 5;
	auto multiply = five * 2;
	SECTION("Checking Friends Operator") {
		CHECK(addition == two);
		CHECK(subtraction == five);
		CHECK(division == two);
		CHECK(multiply == ten);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(addition = one + one);
			CHECK_THROWS_WITH(addition = one + e_vector, "Dimensions of LHS(X) and RHS(Y) do not match");
			CHECK_NOTHROW(subtraction = ten - five);
			CHECK_THROWS_WITH(subtraction = one - e_vector,
			                  "Dimensions of LHS(X) and RHS(Y) do not match");
			CHECK_NOTHROW(division = ten / 5);
			CHECK_THROWS_WITH(division = one / 0, "Invalid vector division by 0");
			CHECK_NOTHROW(multiply = five * 2);
		}
	}
}