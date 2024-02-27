#pragma once
#include <array>
#include <cmath>

namespace Vectors
{
	template <typename E>
	class VectorExpr
	{
	public:
		static constexpr bool is_constant = false;
		double operator[](size_t i) const {
			return static_cast<E const &>(*this)[i];
		}
	};
	template <typename E>
	class DoubleExpr
	{
	public:
		operator double() const {
			return static_cast<double>(static_cast<E const &>(*this));
		}
	};

	template <size_t N>
	class Vector : public VectorExpr<Vector<N>>
	{
		std::array<double, N> values;
	public:
		static constexpr bool is_constant = true;

		double operator[](size_t index) const { return index < N ? values[index] : 0.0; }
		double &operator[](size_t index) { return values[index]; }

		Vector() {
			std::fill(values.begin(), values.end(), 0);
		}
		Vector(std::initializer_list<double> init) {
			std::copy(init.begin(), init.end(), values.begin());
		}
		template <typename E> Vector(const VectorExpr<E> &expr) {
			for (size_t i = 0; i < N; i++)
				values[i] = expr[i];
		}

		double magnitude_squared() const {
			double sum = 0;
			for (const auto &value : values)
				sum += value * value;
			return sum;
		}

		double magnitude() const {
			return std::sqrt(magnitude_squared());
		}

		void normalize() {
			double mag = magnitude();
			for (size_t i = 0; i < N; i++)
				values[i] /= mag;
		}

		template <typename E>
		Vector operator=(const VectorExpr<E> &expr) {
			for (size_t i = 0; i < N; i++)
				values[i] = expr[i];
			return *this;
		}
		template <typename E>
		Vector operator+=(const VectorExpr<E> &expr) {
			for (size_t i = 0; i < N; i++)
				values[i] += expr[i];
			return *this;
		}


	};

	template <typename LHS, typename RHS>
	class VectorSumExpr : public VectorExpr<VectorSumExpr<LHS, RHS>>
	{
		typename std::conditional_t<LHS::is_constant, const LHS &, const LHS> _lhs;
		typename std::conditional_t<RHS::is_constant, const RHS &, const RHS> _rhs;

	public:
		VectorSumExpr(LHS const &lhs, RHS const &rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator[](size_t i) const { return _lhs[i] + _rhs[i]; }
	};
	template <typename LHS, typename RHS>
	VectorSumExpr<LHS, RHS> operator+(VectorExpr<LHS> const &lhs, VectorExpr<RHS> const &rhs) {
		return VectorSumExpr<LHS, RHS>(*static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
	}

	template <typename LHS, typename RHS>
	class VectorRemExpr : public VectorExpr<VectorRemExpr<LHS, RHS>>
	{
		typename std::conditional_t<LHS::is_constant, const LHS &, const LHS> _lhs;
		typename std::conditional_t<RHS::is_constant, const RHS &, const RHS> _rhs;

	public:
		VectorRemExpr(LHS const &lhs, RHS const &rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator[](size_t i) const { return _lhs[i] - _rhs[i]; }
	};
	template <typename LHS, typename RHS>
	VectorRemExpr<LHS, RHS> operator-(VectorExpr<LHS> const &lhs, VectorExpr<RHS> const &rhs) {
		return VectorRemExpr<LHS, RHS>(*static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
	}

	template <typename LHS>
	class VectorScalarProdExpr : public VectorExpr<VectorScalarProdExpr<LHS>>
	{
		typename std::conditional_t<LHS::is_constant, const LHS &, const LHS> _lhs;
		double _rhs;
	public:
		VectorScalarProdExpr(LHS const &lhs, double const &rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator[](size_t i) const { return _lhs[i] * _rhs; }
	};
	template <typename LHS>
	VectorScalarProdExpr<LHS> operator*(VectorExpr<LHS> const &lhs, double rhs) {
		return VectorScalarProdExpr<LHS>(*static_cast<const LHS *>(&lhs), rhs);
	}

	template <typename RHS>
	class VectorNegExpr : public VectorExpr<VectorNegExpr<RHS>>
	{
		typename std::conditional_t<RHS::is_constant, const RHS &, const RHS> _rhs;

	public:
		VectorNegExpr(RHS const &rhs) : _rhs(rhs) {}
		double operator[](size_t i) const { return -_rhs[i]; }
	};
	template <typename RHS>
	VectorNegExpr<RHS> operator-(VectorExpr<RHS> const &rhs) {
		return VectorNegExpr<RHS>(*static_cast<const RHS *>(&rhs));
	}
}