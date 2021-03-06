#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


const string OUTPUT_FILENAME = "integrals.csv";

const double LOWER_BOUND = 0.0;
const double UPPER_BOUND = 1.0;

const vector<int> SAMPLE_RECTANGLES = 
{
	2, 20, 200, 2000, 20000, 200000
};


/**
* Calculus 1 function.
*/
double f1(double x)
{
	return 4.0 / (1 + pow(x, 2));
}

/**
* Calculus 2 function.
*/
double f2(double x)
{
	return 4.0 * sqrt(1 - pow(x, 2));
}

/**
* Approximates the definite integral
* using the midpoint rule (rectangle method).
*
* @a - lower bound
* @b - upper bound
*/
double calculateIntegral(double(*function)(double), double a, double b, int rectangles)
{
	double rectangleWidth = (b - a) / rectangles;
	double definiteIntegral = 0.0;

	for (int rectangle = 0; rectangle < rectangles; rectangle++)
	{
		// Evaluate the given function at the lower bound 
		// of each rectangle to determine its height.
		double rectangleHeight = function(a + (rectangle * rectangleWidth));

		double rectangleArea = rectangleHeight * rectangleWidth;
		definiteIntegral += rectangleArea;
	}

	return definiteIntegral;
}

void writeToFile(ofstream& file, const string& header, vector<double> arr)
{
	const int len = arr.size();

	file << header << ",";

	for (int i = 0; i < len-1; i++)
	{
		file << arr[i] << ",";
	}

	file << arr[len - 1] << endl;
}

int main()
{
	ofstream outputFile;
	outputFile.open(OUTPUT_FILENAME, ios::out);

	if (outputFile.is_open())
	{
		auto sampleIntegral = [&](double(*function)(double)) -> vector<double>
		{
			vector<double> integrals;

			for (int i = 0; i < SAMPLE_RECTANGLES.size(); i++)
			{
				const double integral = calculateIntegral(
					function,
					LOWER_BOUND,
					UPPER_BOUND,
					SAMPLE_RECTANGLES[i]
				);

				integrals.push_back(integral);
			}

			return integrals;
		};

		// Header
		writeToFile(outputFile, "function", vector<double>(
			SAMPLE_RECTANGLES.begin(), 
			SAMPLE_RECTANGLES.end())
		);

		// Data
		writeToFile(outputFile, "f1", sampleIntegral(f1));
		writeToFile(outputFile, "f2", sampleIntegral(f2));

		outputFile.close();

		cout << "Success: wrote to " << OUTPUT_FILENAME << endl;
	}
	else
	{
		cout << "Error: could not open " << OUTPUT_FILENAME << endl;
	}
	
    return 0;
}
