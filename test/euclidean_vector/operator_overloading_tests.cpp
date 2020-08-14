#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>

TEST_CASE("Operator Overloading Tests") {
	// Copy Assignment
	auto init_list = {33.2, 24.9, 10230.3, 78.0, 93.0, 183.6};
	auto other_list = {3.0, 23.0};
	auto e_vector = comp6771::euclidean_vector(init_list);
	auto other_vector = comp6771::euclidean_vector(other_list);
	auto copy_assignment = e_vector;
	auto copy_assignment2 = e_vector;
	SECTION("Checking Copy Assignment") {
		CHECK(copy_assignment.get_magnitudes() == e_vector.get_magnitudes());
		CHECK(copy_assignment.dimensions() == e_vector.dimensions());
		copy_assignment = other_vector;
		CHECK(copy_assignment.get_magnitudes() == other_vector.get_magnitudes());
		CHECK(copy_assignment.dimensions() == other_vector.dimensions());
		SECTION("Checking exceptions") {
			CHECK_NOTHROW(copy_assignment = e_vector);
		}
	}

	// Move Assignment
	auto move_assignment = std::move(copy_assignment);
	auto move2 = other_vector;
	SECTION("Checking Move Assignment") {
		CHECK(move_assignment.get_magnitudes() == e_vector.get_magnitudes());
		CHECK(move_assignment.dimensions() == e_vector.dimensions());
		move_assignment = std::move(move2);
		CHECK(move_assignment.get_magnitudes() == other_vector.get_magnitudes());
		CHECK(move_assignment.dimensions() == other_vector.dimensions());
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(move_assignment = std::move(copy_assignment2));
		}
	}

	// Subscript Assignment
	auto subscript_assignment = comp6771::euclidean_vector(10, 32.0);
	SECTION("Checking Subscript Assignment") {
		CHECK(subscript_assignment[3] == 32.0);
		subscript_assignment[3] = 0.0;
		CHECK(subscript_assignment[3] == 0.0);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(10, 32.0));
		}
	}

	// Unary Plus Assignment
	auto unary_plus = +subscript_assignment;
	SECTION("Checking Unary Plus Assignment") {
		CHECK(unary_plus.get_magnitudes() == subscript_assignment.get_magnitudes());
		CHECK(unary_plus.dimensions() == subscript_assignment.dimensions());
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(unary_plus = +subscript_assignment);
		}
	}

	// Negation Assignment
	auto negation = -unary_plus;
	auto negation_check = subscript_assignment.get_magnitudes();
	for (auto& temp : negation_check) {
		temp *= -1;
	}
	SECTION("Checking Negation Assignment") {
		CHECK(negation.get_magnitudes() == negation_check);
		CHECK(static_cast<size_t>(negation.dimensions()) == negation_check.size());
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(unary_plus = -subscript_assignment);
		}
	}

	// Adding Operator Overload
	auto adding = comp6771::euclidean_vector(3, 3.0);
	auto adding2 = comp6771::euclidean_vector(3, 10.0);
	auto adding2_copy = adding2;
	adding += adding2;
	auto adding_check = std::vector<double>();
	adding_check.push_back(13.0);
	adding_check.push_back(13.0);
	adding_check.push_back(13.0);
	SECTION("Checking Adding") {
		CHECK(adding.get_magnitudes() == adding_check);
		CHECK(adding.dimensions() == adding2_copy.dimensions());
		CHECK(adding2.get_magnitudes() == adding2_copy.get_magnitudes());
		SECTION("Checking Exceptions") {
			CHECK_THROWS_WITH(adding += subscript_assignment,
			                  "Dimensions of LHS(X) and RHS(Y) do not match");
			CHECK_NOTHROW(adding += adding2);
		}
	}

	// Subtracting Operator Overload
	auto subtracting = comp6771::euclidean_vector(3, 20.0);
	auto subtracting2 = comp6771::euclidean_vector(3, 15.0);
	auto subtracting2_copy = subtracting2;
	subtracting -= subtracting2;
	auto subtracting_check = std::vector<double>();
	subtracting_check.push_back(5.0);
	subtracting_check.push_back(5.0);
	subtracting_check.push_back(5.0);
	SECTION("Checking Subtracting") {
		CHECK(subtracting.get_magnitudes() == subtracting_check);
		CHECK(subtracting.dimensions() == subtracting2_copy.dimensions());
		CHECK(subtracting2.get_magnitudes() == subtracting2_copy.get_magnitudes());
		SECTION("Checking Exceptions") {
			CHECK_THROWS_WITH(adding -= subscript_assignment,
			                  "Dimensions of LHS(X) and RHS(Y) do not match");
			CHECK_NOTHROW(subtracting -= subtracting2);
		}
	}

	// Multiplying Operator Overload
	auto multiplying = comp6771::euclidean_vector(3, 5.0);
	multiplying *= 2.0;
	auto multiplying_check = std::vector<double>();
	multiplying_check.push_back(10.0);
	multiplying_check.push_back(10.0);
	multiplying_check.push_back(10.0);
	SECTION("Checking multiplying") {
		CHECK(multiplying.get_magnitudes() == multiplying_check);
		CHECK(multiplying.dimensions() == 3);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(multiplying *= 3);
		}
	}

	// Dividing Operator Overload
	auto dividing = comp6771::euclidean_vector(3, 10.0);
	dividing /= 2.0;
	auto dividing_check = std::vector<double>();
	dividing_check.push_back(5.0);
	dividing_check.push_back(5.0);
	dividing_check.push_back(5.0);
	SECTION("Checking dividing") {
		CHECK(dividing.get_magnitudes() == dividing_check);
		CHECK(dividing.dimensions() == 3);
		SECTION("Checking Exceptions") {
			CHECK_THROWS_WITH(dividing /= 0, "Invalid vector division by 0");
			CHECK_NOTHROW(dividing /= 1);
		}
	}

	// Vector Conversion
	auto vector_conversion = static_cast<std::vector<double>>(comp6771::euclidean_vector(3, 3.0));
	auto vector_check = std::vector<double>();
	vector_check.push_back(3.0);
	vector_check.push_back(3.0);
	vector_check.push_back(3.0);
	SECTION("Checking Vector Conversion") {
		CHECK(vector_conversion == vector_check);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(static_cast<std::vector<double>>(comp6771::euclidean_vector(3, 3.0)));
		}
	}

	// List Conversion
	auto list_conversion = static_cast<std::list<double>>(comp6771::euclidean_vector(3, 3.0));
	auto list_check = std::list<double>();
	list_check.push_back(3.0);
	list_check.push_back(3.0);
	list_check.push_back(3.0);
	SECTION("Checking Vector Conversion") {
		CHECK(list_conversion == list_check);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(static_cast<std::list<double>>(comp6771::euclidean_vector(3, 3.0)));
		}
	}
}