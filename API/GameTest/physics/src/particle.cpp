// particle.cpp
#include "stdafx.h"
#include <assert.h>
#include "../include/particle.h"

using namespace physics;


// Constructor
Particle::Particle(const Vector3& pos, const Vector3& vel, const Vector3& acc, const real damp)
	: position(pos)
	, velocity(vel)
	, acceleration(acc)
	, damping(damp)
{
}


// This move the player by it's velocity, it also slows it down
void Particle::integrate(real duration)
{
	assert(duration > 0.0);

	// Update linear position
	position.addScaledVector(velocity, duration);

	// Work out the acceleration from the force, will add this if I add forces (relevant in chapter 5)
	/*Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);*/

	// Update linear velocity from the acceleration.
		// Will add this one if I add forces
	velocity.addScaledVector(acceleration, duration);

	// Impose drag. (might make movement feel nicer)
	velocity *= real_pow(damping, duration);
}
