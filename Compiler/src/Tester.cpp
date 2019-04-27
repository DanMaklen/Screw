#include "Tester.hpp"
#include <fstream>
#include <sstream>
#include "Parser.hpp"
#include "Logger.hpp"
using namespace std;

Tester::Tester(string dataSetPath) : baseDir(dataSetPath){
	ifstream dataSetFile(dataSetPath + "/set.tsv");
	string line;
	while(!dataSetFile.eof()){
		getline(dataSetFile, line);
		istringstream lineStream(line);
		string path; getline(lineStream, path, '\t');
		string expected; getline(lineStream, expected, '\t');
		if(path != "")
			dataSet.push_back(TestCase{path, expected=="true"});
	}
}

Tester::TestResultSummary Tester::Run(){
	TestResultSummary summary;
	Parser parser;
	for(TestCase tc : dataSet){
		AST* ast = parser.Parse(baseDir + "/" + tc.FilePath);
		bool result = (ast != nullptr);
		if(result != tc.Expected)
			summary.failures.push_back(TestResult{baseDir + tc.FilePath, tc.Expected, ast==nullptr});
		if(ast != nullptr) delete ast;
	}
	summary.passRate = 1 - 1.0 * summary.failures.size() / dataSet.size();
	return summary;
}
