#pragma once
#include <string>
#include <vector>

class Tester{
public:
	struct TestResult{
		std::string filePath;
		bool Expected;
		bool Result;
	};
	struct TestResultSummary{
		double passRate;
		std::vector<TestResult> failures;
	};
	struct TestCase{
		std::string FilePath;
		bool Expected;
	};
private:
	std::string baseDir;
	std::vector<TestCase> dataSet;
public:
	Tester(std::string dataSetPath);
	TestResultSummary Run();
};
