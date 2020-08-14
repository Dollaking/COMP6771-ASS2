// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

namespace comp6771 {
	// Implement solution here

	// Constructor

	euclidean_vector::euclidean_vector() noexcept {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(1);
		this->dimensions_ = 1;
		this->need_norm_cal = true;
	}

	euclidean_vector::euclidean_vector(int dim) noexcept {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		for (auto i = 0; i < dim; i++) {
			magnitudes_[static_cast<size_t>(i)] = 0;
		}
		this->dimensions_ = dim;
		this->need_norm_cal = true;
		this->norm = 0;
	}

	euclidean_vector::euclidean_vector(int dim, double mag) noexcept {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		for (auto i = 0; i < dim; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = mag;
		}
		this->dimensions_ = dim;
		this->need_norm_cal = true;
		this->norm = 0;
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin_iterator,
	                                   std::vector<double>::const_iterator end_iterator) noexcept {
		auto counter = 0;
		for (auto temp = begin_iterator; temp != end_iterator; temp++) {
			counter++;
		}

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(counter));

		counter = 0;
		for (auto temp2 = begin_iterator; temp2 != end_iterator; temp2++) {
			this->magnitudes_[static_cast<size_t>(counter)] = *temp2;
			counter++;
		}
		this->dimensions_ = counter;
		this->need_norm_cal = true;
		this->norm = 0;
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list) noexcept {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(list.size());
		auto counter = 0;
		for (auto temp : list) {
			magnitudes_[static_cast<size_t>(counter)] = temp;
			counter++;
		}
		this->dimensions_ = counter;
		this->need_norm_cal = true;
		this->norm = 0;
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& original) noexcept {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(original.dimensions()));

		for (auto temp = 0; temp < original.dimensions(); temp++) {
			magnitudes_[static_cast<size_t>(temp)] = original.magnitudes_[static_cast<size_t>(temp)];
		}
		this->dimensions_ = original.dimensions();
		this->need_norm_cal = original.need_norm_cal;
		this->norm = original.norm;
	}
	euclidean_vector::euclidean_vector(euclidean_vector&& original) noexcept {
		this->magnitudes_ = std::exchange(original.magnitudes_, nullptr);
		this->dimensions_ = std::exchange(original.dimensions_, 0);
		this->need_norm_cal = std::exchange(original.need_norm_cal, true);
		this->norm = std::exchange(original.norm, 0);
	}

	// Deconstructor
	euclidean_vector::~euclidean_vector() = default;

	// Operator Overload
	auto euclidean_vector::operator=(euclidean_vector const& rhs) noexcept -> euclidean_vector& {
		auto temp = rhs;
		std::swap(temp.magnitudes_, this->magnitudes_);
		std::swap(temp.dimensions_, this->dimensions_);
		std::swap(temp.need_norm_cal, this->need_norm_cal);
		return *this;
	}
	auto euclidean_vector::operator=(euclidean_vector&& rhs) noexcept -> euclidean_vector& {
		ranges::swap(rhs.magnitudes_, this->magnitudes_);
		ranges::swap(rhs.dimensions_, this->dimensions_);
		ranges::swap(rhs.need_norm_cal, this->need_norm_cal);
		auto* need_deleted = rhs.magnitudes_.release();
		delete[] need_deleted;
		rhs.magnitudes_ = nullptr;
		rhs.dimensions_ = 0;
		rhs.need_norm_cal = true;
		return *this;
	}
	auto euclidean_vector::operator[](int index) noexcept -> double& {
		assert(index >= 0);
		assert(index < static_cast<int>(sizeof(this->magnitudes_)));
		this->need_norm_cal = true;
		return magnitudes_[static_cast<size_t>(index)];
	}
	auto euclidean_vector::operator[](int index) const noexcept -> double {
		assert(index >= 0);
		assert(index < static_cast<int>(sizeof(this->magnitudes_)));
		return magnitudes_[static_cast<size_t>(index)];
	}
	auto euclidean_vector::operator+() noexcept -> euclidean_vector {
		auto temp_vector = this->get_magnitudes();
		euclidean_vector temp = euclidean_vector(temp_vector.begin(), temp_vector.end());
		return temp;
	}
	auto euclidean_vector::operator-() noexcept -> euclidean_vector {
		auto temp_vector = this->get_magnitudes();
		for (auto& index : temp_vector) {
			index *= -1;
		}
		euclidean_vector temp = euclidean_vector(temp_vector.begin(), temp_vector.end());
		return temp;
	}
	auto euclidean_vector::operator+=(euclidean_vector const& rhs) -> euclidean_vector& {
		if (this->dimensions() != rhs.dimensions()) {
			throw "Dimensions of LHS(X) and RHS(Y) do not match";
		}
		this->need_norm_cal = true;
		if (this->dimensions() == 0) {
			return *this;
		}

		auto rhs_mags = rhs.get_magnitudes();
		for (auto mag_length = 0; mag_length < rhs.dimensions(); mag_length++) {
			this->magnitudes_[static_cast<size_t>(mag_length)] +=
			   rhs_mags[static_cast<size_t>(mag_length)];
		}
		return *this;
	}
	auto euclidean_vector::operator-=(euclidean_vector const& rhs) -> euclidean_vector& {
		if (this->dimensions() != rhs.dimensions()) {
			throw "Dimensions of LHS(X) and RHS(Y) do not match";
		}
		this->need_norm_cal = true;
		if (this->dimensions() == 0) {
			return *this;
		}
		auto rhs_mags = rhs.get_magnitudes();
		for (auto mag_length = 0; mag_length < rhs.dimensions(); mag_length++) {
			this->magnitudes_[static_cast<size_t>(mag_length)] -=
			   rhs_mags[static_cast<size_t>(mag_length)];
		}
		return *this;
	}
	auto euclidean_vector::operator*=(double rhs) noexcept -> euclidean_vector& {
		this->need_norm_cal = true;
		if (this->dimensions() == 0) {
			return *this;
		}

		for (auto mag_length = 0; mag_length < this->dimensions(); mag_length++) {
			this->magnitudes_[static_cast<size_t>(mag_length)] *= rhs;
		}
		return *this;
	}
	auto euclidean_vector::operator/=(double rhs) -> euclidean_vector& {
		if (rhs == 0.0) {
			throw "Invalid vector division by 0";
		}
		this->need_norm_cal = true;
		if (this->dimensions() == 0) {
			return *this;
		}
		for (auto mag_length = 0; mag_length < this->dimensions(); mag_length++) {
			this->magnitudes_[static_cast<size_t>(mag_length)] /= rhs;
		}
		return *this;
	}
	euclidean_vector::operator std::vector<double>() noexcept {
		auto length = this->dimensions();
		auto result = std::vector<double>();
		result.reserve(static_cast<size_t>(length));
		for (auto index = 0; index < length; index++) {
			result.push_back(this->magnitudes_[static_cast<size_t>(index)]);
		}
		return result;
	}
	euclidean_vector::operator std::vector<double>() const noexcept {
		auto length = this->dimensions();
		auto result = std::vector<double>();
		result.reserve(static_cast<size_t>(length));
		for (auto index = 0; index < length; index++) {
			result.push_back(this->magnitudes_[static_cast<size_t>(index)]);
		}
		return result;
	}
	euclidean_vector::operator std::list<double>() noexcept {
		auto list = std::list<double>();
		for (auto temp : this->get_magnitudes()) {
			list.push_back(temp);
		}
		return list;
	}
	euclidean_vector::operator std::list<double>() const noexcept {
		auto list = std::list<double>();
		for (auto temp : this->get_magnitudes()) {
			list.push_back(temp);
		}
		return list;
	}

	// Member Functions
	auto euclidean_vector::at(int index) const -> double {
		if (index < 0 || index >= this->dimensions()) {
			throw "Index X is not valid for this euclidean_vector object";
		}
		return this->magnitudes_[static_cast<size_t>(index)];
	}
	auto euclidean_vector::at(int index) -> double& {
		if (index < 0 || index >= this->dimensions()) {
			throw "Index X is not valid for this euclidean_vector object";
		}
		this->need_norm_cal = true;
		return this->magnitudes_[static_cast<size_t>(index)];
	}
	auto euclidean_vector::dimensions() const noexcept -> int {
		return this->dimensions_;
	}

	// Friends
	auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept -> bool {
		if (lhs.dimensions() != rhs.dimensions()) {
			return false;
		}
		for (auto length = static_cast<size_t>(0); length < static_cast<size_t>(rhs.dimensions());
		     length++) {
			if (rhs.magnitudes_[length] != lhs.magnitudes_[length]) {
				return false;
			}
		}
		return true;
	}
	auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept -> bool {
		if (lhs.dimensions() != rhs.dimensions()) {
			return true;
		}
		for (auto length = static_cast<size_t>(0); length < static_cast<size_t>(rhs.dimensions());
		     length++) {
			if (rhs.magnitudes_[length] != lhs.magnitudes_[length]) {
				return true;
			}
		}
		return false;
	}
	auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs.dimensions() != rhs.dimensions()) {
			throw "Dimensions of LHS(X) and RHS(Y) do not match";
		}
		if (lhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto rhs_vector = rhs.get_magnitudes();
		auto lhs_vector = lhs.get_magnitudes();

		auto result_vector = std::vector<double>();
		auto sum = 0.0;

		for (auto length = static_cast<size_t>(0); length < static_cast<size_t>(rhs.dimensions());
		     length++) {
			sum = rhs_vector[length] + lhs_vector[length];
			result_vector.push_back(sum);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs.dimensions() != rhs.dimensions()) {
			throw "Dimensions of LHS(X) and RHS(Y) do not match";
		}
		if (lhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto rhs_vector = rhs.get_magnitudes();
		auto lhs_vector = lhs.get_magnitudes();
		auto result_vector = std::vector<double>();

		for (auto length = static_cast<size_t>(0); length < rhs_vector.size(); length++) {
			result_vector.push_back(lhs_vector[length] - rhs_vector[length]);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator*(euclidean_vector const& lhs, double rhs) noexcept -> euclidean_vector {
		if (lhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto lhs_vector = lhs.get_magnitudes();
		auto result_vector = std::vector<double>();

		for (auto length = static_cast<size_t>(0); length < lhs_vector.size(); length++) {
			result_vector.push_back(lhs_vector[length] * rhs);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator*(double lhs, euclidean_vector const& rhs) noexcept -> euclidean_vector {
		if (rhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto rhs_vector = rhs.get_magnitudes();
		auto result_vector = std::vector<double>();

		for (auto length = static_cast<size_t>(0); length < rhs_vector.size(); length++) {
			result_vector.push_back(rhs_vector[length] * lhs);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator/(euclidean_vector const& lhs, double rhs) -> euclidean_vector {
		if (rhs == 0) {
			throw "Invalid vector division by 0";
		}
		if (lhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto lhs_vector = lhs.get_magnitudes();
		auto result_vector = std::vector<double>();

		for (auto length = static_cast<size_t>(0); length < lhs_vector.size(); length++) {
			result_vector.push_back(lhs_vector[length] / rhs);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator/(double lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs == 0) {
			throw "Invalid vector division by 0";
		}
		if (rhs.dimensions() == 0) {
			return comp6771::euclidean_vector(0, 0.0);
		}
		auto rhs_vector = rhs.get_magnitudes();
		auto result_vector = std::vector<double>();

		for (auto length = static_cast<size_t>(0); length < rhs_vector.size(); length++) {
			result_vector.push_back(lhs / rhs_vector[length]);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}
	auto operator<<(std::ostream& os, euclidean_vector const& evector) noexcept -> std::ostream& {
		auto temp_vector = evector.get_magnitudes();
		os << "[";
		auto counter = 0;
		for (auto value : temp_vector) {
			if (counter == 0) {
				os << value;
			}
			else {
				os << " " << value;
			}
			counter++;
		}
		os << "]";
		return os;
	}

	// Utility Functions
	auto euclidean_norm(euclidean_vector const& evector) -> double {
		if (evector.dimensions() == 0) {
			throw "euclidean_vector with no dimensions does not have a norm";
		}
		if (evector.need_norm_cal) {
			auto temp_vector = evector.get_magnitudes();
			auto result = 0.0;
			for (auto temp : temp_vector) {
				result += temp * temp;
			}
			result = sqrt(result);
			evector.need_norm_cal = false;
			evector.norm = result;
			return result;
		}
		return evector.norm;
	}
	auto unit(euclidean_vector const& evector) -> euclidean_vector {
		if (evector.dimensions() == 0) {
			throw "euclidean_vector with no dimensions does not have a unit vector";
		}
		auto temp_vector = static_cast<std::vector<double>>(evector);
		auto norm = euclidean_norm(evector);
		if (norm == 0) {
			throw "euclidean_vector with zero euclidean normal does not have a unit vector";
		}

		for (auto& temp : temp_vector) {
			temp /= norm;
		}

		return euclidean_vector(temp_vector.begin(), temp_vector.end());
	}
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw "Dimensions of LHS(X) and RHS(Y) do not match";
		}
		auto x_vector = x.get_magnitudes();
		auto y_vector = y.get_magnitudes();
		auto result = 0.0;

		for (auto length = static_cast<size_t>(0); length < static_cast<size_t>(x.dimensions());
		     length++) {
			result += x_vector[length] * y_vector[length];
		}
		return result;
	}

	// Getter Setters
	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	auto euclidean_vector::get_magnitudes() const -> std::vector<double> {
		auto length = this->dimensions();
		auto result = std::vector<double>();
		result.reserve(static_cast<size_t>(length));
		for (auto index = 0; index < static_cast<int>(length); index++) {
			auto temp = this->magnitudes_[static_cast<size_t>(index)];
			result.push_back(temp);
		}
		return result;
	}
	auto euclidean_vector::get_magnitudes() -> std::vector<double> {
		auto length = this->dimensions();
		auto result = std::vector<double>();
		result.reserve(static_cast<size_t>(length));
		for (auto index = 0; index < length; index++) {
			auto temp = this->magnitudes_[static_cast<size_t>(index)];
			result.push_back(temp);
		}
		return result;
	}

} // namespace comp6771
