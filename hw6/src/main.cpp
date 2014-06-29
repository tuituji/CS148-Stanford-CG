#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include "image.h"
using namespace std;
using namespace Eigen;

template<class ArrayType, class ElementType>
void iteratedBoxFilter(ArrayType &signal, ArrayType &outSignal, int filterSize, int filterIterations) {
	// problem 1
}

void process2dSignal(Image &signal, Image &outSignal, int filterSize, int filterIterations) {
	// problem 3
}

void tiltShift(Image &signal, Image &outSignal, int filterSize, int filterIterations) {
	// problem 4
	
	// feel free to ignore filterSize/filterIterations if you don't need them
}

void process1dSignal(vector<double> &signal, vector<double> &outSignal, int filterSize, int filterIterations) {
	iteratedBoxFilter< vector<double>, double >(signal, outSignal, filterSize, filterIterations);
}

int main(int argc, char *argv[]) {
	if (argc < 6) {
		cout << "Usage: " << argv[0] << " signalType filterSize filterIterations in out\n";
		cout << "\tsignalType is one of \"1d,\" \"2d\", or \"tilt\" (no quotes)\n";
		cout << "\tfilterSize is an integer k describing the width 2k+1 of the box\n\t\t(this and the next argument have whatever meaning you like for tilt shift filtering)\n";
		cout << "\tfilterIterations is an integer with the number of iterations of box\n";
		cout << "\tin is the input signal (.txt for 1d, .png for 2d)\n";
		cout << "\tout is the output signal\n";
		return 0;
	}
	
	string signalType = argv[1];
	
	int filterSize, filterIterations;
	sscanf(argv[2],"%d",&filterSize);
	sscanf(argv[3],"%d",&filterIterations);
	
	string in = argv[4];
	string out = argv[5];
	
	if (signalType == "1d") {
		vector<double> signal;
		
		ifstream infile(in.c_str());
		double d;
		while (infile >> d) signal.push_back(d);
		
		vector<double> outSignal(signal.size());
		process1dSignal(signal, outSignal, filterSize, filterIterations);
		
		ofstream outfile(out.c_str());
		for (unsigned int i = 0; i < outSignal.size(); i++)
			outfile << outSignal[i] << endl;
	} else if (signalType == "2d") {
		Image signal(in);
		Image outSignal(signal.width(),signal.height());
		process2dSignal(signal, outSignal, filterSize, filterIterations);
		outSignal.write(out);
	} else if (signalType == "tilt") {
		Image signal(in);
		Image outSignal(signal.width(),signal.height());
		tiltShift(signal, outSignal, filterSize, filterIterations);
		outSignal.write(out);
	}
	
	return 0;
}
