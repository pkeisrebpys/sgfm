// Component to model change rate limitter.
//
// Copyright (C) 2017  Ken-ichi Kondo.
//
// This file is part of SGFM.
// 
// SGFM is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// SGFM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with SGFM.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <PrintPass.hpp>
#include <ChangeRateLimitter.hpp>

namespace SGFM {

	void ChangeRateLimitter::init(
			double cr,
			double dt,
			double initInput)
	{
		mcr = cr;
		mdt = dt;
		mOutput = initInput;
	}

	int ChangeRateLimitter::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("f>>b:1");
				return EXIT_FAILURE;
			}
			mcr = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("f>>b:2");
				return EXIT_FAILURE;
			}
			mdt = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("f>>b:3");
				return EXIT_FAILURE;
			}
			mOutput = buf;
		} catch (std::exception &e) {
			PRINT_PASS("exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int ChangeRateLimitter::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mcr << std::endl;
			fout << mdt << std::endl;
			fout << mOutput << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void ChangeRateLimitter::set(double input) {
		double curChangeRate = (input - mOutput)/mdt;
		if (curChangeRate > mcr) {
			mOutput += mcr * mdt;
		} else if (curChangeRate < -mcr) {
			mOutput -= mcr * mdt;
		} else {
			mOutput = input;
		}
	}

	double ChangeRateLimitter::get()const {
		return mOutput;
	}

	double ChangeRateLimitter::cr()const {
		return mcr;
	}
}
