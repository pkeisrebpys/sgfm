// Component to model limitter.
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
#include <Limitter.hpp>

namespace SGFM {

	void Limitter::init(double upper, double lower)
	{
		mUpper = upper;
		mLower = lower;
	}

	int Limitter::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("File read error.");
				return EXIT_FAILURE;
			}
			mUpper = buf;

			if(!(fin >> buf)) {
				PRINT_PASS("File read error.");
				return EXIT_FAILURE;
			}
			mLower = buf;
		} catch (std::exception &e) {
			PRINT_PASS("File read error.");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Limitter::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mUpper << std::endl;
			fout << mLower << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("File write error.");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void Limitter::set(double input) {
		if (input > mUpper) {
			mOutput = mUpper;
		} else if (input > mLower) {
			mOutput = input;
		} else {
			mOutput = mLower;
		}
	}

	double Limitter::get()const {
		return mOutput;
	}
}
