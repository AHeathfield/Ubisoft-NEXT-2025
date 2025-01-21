// Clock.cpp

#include "stdafx.h"
#include "Clock.h"

/* ===== PUBLIC METHODS ===== */

// Constructor
// The check on the duration is too make sure all values are positive unless
//	the duration is the infinite duration (-1).
Clock::Clock(bool isLooping, float duration)
	: m_timeElapsed(0.0f)
	, m_duration((duration == INFINITE_DURATION) ? duration : abs(duration))
	, m_paused(true)
	, m_isLooping(isLooping)
{
}


void Clock::start() { m_paused = false; }
void Clock::pause() { m_paused = true; }
void Clock::reset() { m_timeElapsed = 0.0f; }


void Clock::update(float deltaTime)
{
	if (m_paused)
	{
		return;
	}
	else if (m_isLooping)
	{
		// Increments the time elapsed
		m_timeElapsed += deltaTime;

		// Since it's looping it will just start again
		if (isClockFinish() && !isClockInfinite())
		{
			reset();
			start();
		}
	}
	else
	{
		// Increments the time elapsed
		m_timeElapsed += deltaTime;

		// Not looping so it will pause
		if (isClockFinish() && !isClockInfinite())
		{
			pause();
			// Just because the deltaTime will not always add perfectly up to m_duration
			m_timeElapsed = m_duration;
		}
	}
}


void Clock::setDuration(float duration) { m_duration = duration; }


void Clock::toggleLooping()
{
	if (m_isLooping)
	{
		m_isLooping = false;
	}
	else
	{
		m_isLooping = true;
	}
}

float Clock::getTimeElapsed() const { return m_timeElapsed; }
float Clock::getDuration() const { return m_duration; }
bool Clock::isPaused() const { return m_paused; }
bool Clock::isLooping() const { return m_isLooping; }

bool Clock::isClockFinish() const
{
	return m_timeElapsed >= m_duration;
}


/* ===== PRIVATE METHODS ===== */
bool Clock::isClockInfinite() const
{
	return m_duration == INFINITE_DURATION;
}