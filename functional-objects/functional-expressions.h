#pragma once
#include <cmath>
namespace FuncExpr
{
	class Variable
	{
	public:
		double operator() (double x) const {
			return x;
		}
	};

	class Constant
	{
		double _c;
	public:
		explicit Constant(double c) : _c(c) {}
		double operator()(double x) const {
			return _c;
		}
	};

	template <typename RHS>
	class NegExpr
	{
		RHS _rhs;
	public:
		explicit NegExpr(RHS rhs) : _rhs(rhs) {}
		double operator()(double x) const {
			return -_rhs(x);
		}
	};
	template <typename RHS>
	NegExpr<RHS> operator-(RHS rhs) { return NegExpr<RHS>(rhs); }

	template <typename LHS, typename RHS>
	class AddExpr
	{
		LHS _lhs;
		RHS _rhs;
	public:
		AddExpr(LHS lhs, RHS rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator()(double x) const {
			return _lhs(x) + _rhs(x);
		}
	};
	template <typename LHS, typename RHS>
	AddExpr<LHS, RHS> operator+(LHS lhs, RHS rhs) { return AddExpr<LHS, RHS>(lhs, rhs); }

	template <typename LHS, typename RHS>
	class SubExpr
	{
		LHS _lhs;
		RHS _rhs;
	public:
		SubExpr(LHS lhs, RHS rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator()(double x) const {
			return _lhs(x) - _rhs(x);
		}
	};
	template <typename LHS, typename RHS>
	SubExpr<LHS, RHS> operator-(LHS lhs, RHS rhs) { return SubExpr<LHS, RHS>(lhs, rhs); }

	template <typename LHS, typename RHS>
	class MulExpr
	{
		LHS _lhs;
		RHS _rhs;
	public:
		MulExpr(LHS lhs, RHS rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator()(double x) const {
			return _lhs(x) * _rhs(x);
		}
	};
	template <typename LHS, typename RHS>
	MulExpr<LHS, RHS> operator*(LHS lhs, RHS rhs) { return MulExpr<LHS, RHS>(lhs, rhs); }

	template <typename LHS, typename RHS>
	class DivExpr
	{
		LHS _lhs;
		RHS _rhs;
	public:
		DivExpr(LHS lhs, RHS rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator()(double x) const {
			return _lhs(x) / _rhs(x);
		}
	};
	template <typename LHS, typename RHS>
	DivExpr<LHS, RHS> operator/(LHS lhs, RHS rhs) { return DivExpr<LHS, RHS>(lhs, rhs); }

	template <typename LHS, typename RHS>
	class PowExpr
	{
		LHS _lhs;
		RHS _rhs;
	public:
		PowExpr(LHS lhs, RHS rhs) : _lhs(lhs), _rhs(rhs) {}
		double operator()(double x) const {
			return std::pow(_lhs(x), _rhs(x));
		}
	};
	template <typename LHS, typename RHS>
	PowExpr<LHS, RHS> pow(LHS lhs, RHS rhs) { return PowExpr<LHS, RHS>(lhs, rhs); }
}