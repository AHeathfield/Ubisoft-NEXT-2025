/*
 *	A particle is the simplest object that can be simulated in
 *	the physics system.
 */
#pragma once

#include "core.h"
#include "precision.h"

namespace physics
{
	class Particle
	{
	public:

		// Holds the linear position of the particle in world space
		Vector3 position;

		// Holds the linear velocity of the particle in world space
		Vector3 velocity;

		/*
		 *	Holds the acceleration of the particle. This will be a constant value
		 *	for things like gravity.
		 */
		Vector3 acceleration;

		/*
		 *	Holds the amount of damping applied to linear motion.
		 *	Damping is required to remove energy added through
		 *	numerical instability in the integrator.
		 * If we don't want no damping set it = 1
		 *
		 */
		real damping;

		/*
		 *	Holds the inverse of the mass of the particle. It is
		 *	more useful because integration is simpler and because
		 *	real-time simulation it's more useful to have objects
		 *	with infinite mass (immovable) than zero mass
		 *	(completely unstable in numerical simulation)
		 */
		 //real inverseMass;	// My engine doesn't use forces, so I don't need this


		 /* Constructors */
		Particle() : position(Vector3()), velocity(Vector3()), acceleration(Vector3()), damping(1.0f) {}
		Particle(const Vector3& pos, const Vector3& vel, const Vector3& acc, const real damp = 1.0f);

		/*
		 *	Integrates the particle forward in time by given amount.
		 *	This function uses a Newton_Euler integration method, which
		 *	is a linear approximation of the correct integral. It may be
		 *	inaccurate in some cases.
		 */
		void integrate(real duration);
	};
}
