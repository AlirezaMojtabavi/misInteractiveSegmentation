// Use the following macro(es) to benchmark a certain operation (P, a function object, labmda expression, etc.) and printing
// out the results to the output.
#define MIS_BENCHMARK_MILLISECS(P, N)	\
{	\
	auto time = misBenchmark::BenchmarkMilliseconds(P, N);	\
	std::cout << "Benchmark result in " << __FUNCTION__ << " ( line " << __LINE__ << " ): " << time << " ms" << std::endl;	\
}	

// Use the static methods in the misBenchmark class to benchmark a certain operation by running it a certain number of times, 
// measuring the time taken, and compute the average time taken per run. The operation can be passed to benchmark methods as
// a function object, lambda expression, etc.
class misBenchmark
{
public:
	typedef boost::chrono::duration<double, boost::milli> DoubleMilliseconds;

	// Benchmark the operation and get the result in milliseconds.
	static double BenchmarkMilliseconds(std::function<void()> subjectProcess, unsigned int numberOfRuns)
	{
		auto time = Benchmark(subjectProcess, numberOfRuns);
		return time.count();
	}

	// Benchmark the operation and get the result as a boost duration object.
	static DoubleMilliseconds Benchmark(std::function<void()> subjectProcess, unsigned int numberOfRuns)
	{
		auto loopTime = BenchmarkLoop(numberOfRuns * 10);

		auto startTime = boost::chrono::high_resolution_clock::now();
		for (int i = 0; i < numberOfRuns; ++i)
			subjectProcess();
		auto elapsedTime = boost::chrono::high_resolution_clock::now() - startTime;
		auto benchmark = elapsedTime / numberOfRuns - loopTime;
		return boost::chrono::duration_cast< DoubleMilliseconds >(benchmark);
	}

	static DoubleMilliseconds BenchmarkLoop( unsigned int numberOfLoopRuns )
	{
		auto loopStartTime = boost::chrono::high_resolution_clock::now();
		for (int i = 0; i < numberOfLoopRuns; ++i);
		auto loopElapsedTime = boost::chrono::high_resolution_clock::now() - loopStartTime;
		return loopElapsedTime / numberOfLoopRuns;
	}

};
