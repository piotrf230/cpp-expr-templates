#include <fstream>
#include <iostream>
#include <filesystem>

#include "Vector3d.h"
#include "Gravity.h"

template <size_t D>
class VectorBuffer
{
	std::array<Vectors::Vector<D>, 2> _buffer;
	int _iterator = 0;
public:
	Vectors::Vector<D> &previous() {
		return _buffer[!_iterator];
	}
	Vectors::Vector<D> &current() {
		return _buffer[_iterator];
	}
	Vectors::Vector<D> &next() {
		_iterator = !_iterator;
		return _buffer[_iterator];
	}
};

void velociy_verlet_step(Physics::Body<2> &body, VectorBuffer<2> &force, const double delta_time) {
	body.position += body.velocity * delta_time + force.previous() * (delta_time * delta_time * .5 / body.mass);
	body.velocity += (force.current() + force.previous()) * (delta_time * .5 / body.mass);
}

int main() {
	const Vectors::Vector<2> zero = {.0,.0}, moon_pos = {.0,3.844e8}, moon_vel = {1.022e3,.0};
	const char separator = ';';

	const double delta_time = 60, total_time = 3600.0 * 24.0 * 100.0;
	Physics::Body<2> earth(zero, zero, 5.9722e24);
	Physics::Body<2> moon(moon_pos, moon_vel, 7.347673e22);

	if (!std::filesystem::exists("outputs") && !std::filesystem::create_directories("outputs"))
	{
		std::cerr << "Outputs directory cannot be created, aborting!"<<std::endl;
		return 1;
	}

	std::ofstream output_file("outputs/earth_moon_positions.dat");
	if (!output_file.is_open())
	{
		std::cerr << "Output file cannot be created, aborting!" << std::endl;
		return 1;
	}

	output_file << "time" << separator
		<< "earth_position_x" << separator << "earth_position_y" << separator << "earth_velocity_x" << separator << "earth_velocity_y" << separator
		<< "moon_position_x" << separator << "moon_position_y" << separator << "moon_velocity_x" << separator << "moon_velocity_y" << std::endl;
	output_file << 0.0 << separator << earth.position[0] << separator << earth.position[1] << separator << earth.velocity[0] << separator << earth.velocity[1] << separator
		<< moon.position[0] << separator << moon.position[1] << separator << moon.velocity[0] << separator << moon.velocity[1] << '\n';

	VectorBuffer<2> force_earth, force_moon;

	Physics::calculate_gravity(earth, moon, force_earth.current(), force_moon.current());
	for (double time = delta_time; time < total_time; time += delta_time) {
		Physics::calculate_gravity(earth, moon, force_earth.next(), force_moon.next());
		velociy_verlet_step(earth, force_earth, delta_time);
		velociy_verlet_step(moon, force_moon, delta_time);
		output_file << time << separator
			<< earth.position[0] << separator << earth.position[1] << separator << earth.velocity[0] << separator << earth.velocity[1] << separator
			<< moon.position[0] << separator << moon.position[1] << separator << moon.velocity[0] << separator << moon.velocity[1] << '\n';
	}
	output_file.flush();
	output_file.close();

	return 0;
}