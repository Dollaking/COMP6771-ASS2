#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructor
		euclidean_vector() noexcept;
		explicit euclidean_vector(int dim) noexcept;
		euclidean_vector(int dim, double mag) noexcept;
		euclidean_vector(std::vector<double>::const_iterator begin_iterator,
		                 std::vector<double>::const_iterator end_iterator) noexcept;
		euclidean_vector(std::initializer_list<double> list) noexcept;
		euclidean_vector(euclidean_vector const& original) noexcept;
		euclidean_vector(euclidean_vector&& original) noexcept;

		// Deconstructor
		~euclidean_vector();

		// Operator Overloading
		auto operator=(euclidean_vector const& rhs) noexcept -> euclidean_vector&;
		auto operator=(euclidean_vector&& rhs) noexcept -> euclidean_vector&;
		auto operator[](int index) noexcept -> double&;
		auto operator[](int index) const noexcept -> double;
		auto operator+() noexcept -> euclidean_vector;
		auto operator-() noexcept -> euclidean_vector;
		auto operator+=(euclidean_vector const& rhs) -> euclidean_vector&;
		auto operator-=(euclidean_vector const& rhs) -> euclidean_vector&;
		auto operator*=(double) noexcept -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		explicit operator std::vector<double>() noexcept;
		explicit operator std::vector<double>() const noexcept;
		explicit operator std::list<double>() noexcept;
		explicit operator std::list<double>() const noexcept;

		// Member Functions
		[[nodiscard]] auto at(int index) const -> double;
		auto at(int index) -> double&;
		// auto dimensions() -> int;
		[[nodiscard]] auto dimensions() const noexcept -> int;

		// Friends
		friend auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept
		   -> bool;
		friend auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept
		   -> bool;
		friend auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs)
		   -> euclidean_vector;
		friend auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs)
		   -> euclidean_vector;
		friend auto operator*(euclidean_vector const& lhs, double rhs) noexcept -> euclidean_vector;
		friend auto operator*(double lhs, euclidean_vector const& rhs) noexcept -> euclidean_vector;
		friend auto operator/(euclidean_vector const& lhs, double rhs) -> euclidean_vector;
		friend auto operator/(double lhs, euclidean_vector const& rhs) -> euclidean_vector;
		friend auto operator<<(std::ostream& os, euclidean_vector const& evector) noexcept
		   -> std::ostream&;

		// Getters
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto get_magnitudes() -> std::vector<double>;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		[[nodiscard]] auto get_magnitudes() const -> std::vector<double>;
		bool mutable need_norm_cal;
		double mutable norm;
		// auto get_norm() -> double;

	private:
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitudes_;
		int dimensions_;
	};

	// Utility Functions
	auto euclidean_norm(euclidean_vector const& evector) -> double;
	auto unit(euclidean_vector const& evector) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
