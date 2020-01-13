#pragma once

class  Stopwatch {
protected:
	/// is the stopwatch currently running or not?
	bool isStopped_;
	/// this is the point of time the stopwatch was started
	clock_t startTime_;
	/// this is the amount of time the stopwatch has been running until now
	clock_t runTime_;

public:
	/// The constructor.  It sets all the uints to 0 and stops the stopwatch.
	Stopwatch();

	/// This function should return the number of elapsed milliseconds since some reference point in the past.
	/// Under windows this is system start time. Be aware: it counts something like 47 days.
	///
	/// DO NOT CONFUSE WITH getRuntime() !!
	static unsigned long long getTicks();

	/// This is the function that returns the current runtime of the stopwatch in milliseconds.
	clock_t getRuntime();

	/// Stop the stopwatch.
	void stop();

	/// Start the stopwatch.
	void start();

	/// Returns the time the stopwatch was started.
	inline clock_t getStartTime() const { return startTime_; }

	/// Reset the stopwatch.
	void reset();
};