#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>

TEST_CASE("Constructor Tests") {
	// INFO("Creating Default Constructor");
	auto default_constructor = comp6771::euclidean_vector();
	auto default_vector = std::vector<double>();
	default_vector.push_back(0.0);
	SECTION("Checking if default constructor vector is correct") {
		CHECK(default_constructor.get_magnitudes() == default_vector);
	}
	SECTION("Checking if default constructor dimensions is correct") {
		CHECK(default_constructor.dimensions() == 1);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector());
		}
	}

	auto single_arg_const = comp6771::euclidean_vector(5);
	auto single_int = 5;
	auto single_arg_const2 = comp6771::euclidean_vector(single_int);
	auto single_arg_vector = std::vector<double>();
	single_arg_vector.reserve(5);
	for (auto index = 0; index < 5; index++) {
		single_arg_vector.push_back(0.0);
	}
	SECTION("Single Argument Constructor Test") {
		CHECK(single_arg_const.get_magnitudes() == single_arg_vector);
		CHECK(single_arg_const.dimensions() == 5);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(single_int));
		}
	}

	// INFO("Creating Dim and Magns Constructor");
	auto int_double_const = comp6771::euclidean_vector(4, 23.0);
	auto int_dimension = 4;
	auto double_mag = 23.0;
	auto int_double_const2 = comp6771::euclidean_vector(int_dimension, double_mag);
	auto int_double_vector = std::vector<double>();
	int_double_vector.reserve(23.0);
	for (auto index = 0; index < int_dimension; index++) {
		int_double_vector.push_back(double_mag);
	}
	SECTION("Dimension Magnitude Tests") {
		CHECK(int_double_const.get_magnitudes() == int_double_vector);
		CHECK(int_double_const.dimensions() == 4);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(4, 23.0));
		}
	}

	// INFO("Creating Iterator Constructor");
	auto iterator_vector = std::vector<double>();
	iterator_vector.push_back(43.0);
	iterator_vector.push_back(22.0);
	iterator_vector.push_back(0.0);
	iterator_vector.push_back(14.3);
	iterator_vector.push_back(1324.0);
	iterator_vector.push_back(7832.0);
	auto iterator_const = comp6771::euclidean_vector(iterator_vector.begin(), iterator_vector.end());
	SECTION("Iterator Constructor Test") {
		CHECK(iterator_const.get_magnitudes() == iterator_vector);
		CHECK(iterator_const.dimensions() == 6);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(iterator_vector.begin(), iterator_vector.end()));
		}
	}

	// INFO("Creating Initialiser List Constructor");
	auto init_list = {33.2, 24.9, 10230.3, 78.0, 93.0, 183.6};
	auto init_list_const = comp6771::euclidean_vector(init_list);
	auto init_vector = static_cast<std::vector<double>>(init_list);
	SECTION("Initialiser List Test") {
		CHECK(init_list_const.get_magnitudes() == init_vector);
		CHECK(init_list_const.dimensions() == 6);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(init_list));
		}
	}

	// INFO("Creating Copy Constructor");
	auto copy_const = comp6771::euclidean_vector(init_list_const);
	SECTION("Copy Constructor Test") {
		CHECK(copy_const.get_magnitudes() == init_vector);
		CHECK(copy_const.dimensions() == 6);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(init_list_const));
		}
	}

	// INFO("Creating Move Constructor");
	auto temp_move_const = comp6771::euclidean_vector(iterator_vector.begin(), iterator_vector.end());
	auto temp_move_const2 = comp6771::euclidean_vector(iterator_vector.begin(), iterator_vector.end());
	auto move_const = comp6771::euclidean_vector(std::move(temp_move_const));
	SECTION("Move Constructor Test") {
		CHECK(move_const.dimensions() == 6);
		CHECK(move_const.get_magnitudes() == iterator_vector);
		SECTION("Checking Exceptions") {
			CHECK_NOTHROW(comp6771::euclidean_vector(std::move(temp_move_const2)));
		}
	}
}