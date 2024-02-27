#pragma once
#include "vectors.h"

namespace Physics
{
	namespace Constants
	{
		const double G = 6.67430e-11;
	}

	template <size_t D>
	class Body
	{
	public:
		Vectors::Vector<D> position;
		Vectors::Vector<D> velocity;
		double mass;

		template <typename E>
		Body(const Vectors::VectorExpr<E> &_position, const Vectors::VectorExpr<E> &_velocity, double _mass)
			: position(_position), velocity(_velocity), mass(_mass) {}

		Body(const Body &) = delete;
		Body operator=(const Body &) = delete;
	};

	template <size_t D>
	void calculate_gravity(const Body<D> &body1, const Body<D> &body2, Vectors::Vector<D> &force1_out, Vectors::Vector<D> &force2_out) {
		Vectors::Vector<D> distance_vector = body2.position - body1.position;
		long double force = Constants::G * body1.mass * body2.mass / distance_vector.magnitude_squared();
		distance_vector.normalize();
		force1_out = distance_vector * force;
		force2_out = distance_vector * -force;
	}
}