// Clock.h
#pragma once

#include "stdafx.h"

/*
 *	I can see many cases where it would be useful to have a clock.
 *	Some examples include spawning enemies and cooldowns.
 *	I basically plan to use the deltaTime from Update() to just
 *		add to a variable.
 */

#define INFINITE_DURATION -1		// This is because the clock duration can't be negative so if I want a clock running infinitl

class Clock
{
private:
	float m_timeElapsed;
	float m_duration;	// This is the amount of time before it will reset
	bool m_paused;
	bool m_isLooping;

public:
	Clock(bool isLooping, float duration = INFINITE_DURATION);

	void start();
	void pause();
	void reset();
	void update(float deltaTime);

	void setDuration(float duration);
	void toggleLooping();

	float getTimeElapsed() const;
	float getDuration() const;
	bool isLooping() const;
	bool isPaused() const;
	bool isClockFinish() const;

private:
	bool isClockInfinite() const;
};