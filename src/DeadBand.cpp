// Component to model dead band.
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
#include <DeadBand.hpp>

namespace SGFM {

	void DeadBand::init(
			double bandUpper,
			double bandLower)
	{
		mUpper = bandUpper;
		mLower = bandLower;
	}

	int DeadBand::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("File write error.");
				return EXIT_FAILURE;
			}
			mUpper = buf;

			if(!(fin >> buf)) {
				PRINT_PASS("File write error.");
				return EXIT_FAILURE;
			}
			mLower = buf;
		} catch (std::exception &e) {
			PRINT_PASS("File write error.");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int DeadBand::write(const char *filename)const {
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

	void DeadBand::set(double input) {
		if (input > mUpper) {
			mOutput = input;
		} else if (input > mLower) {
			mOutput = 0.0;
		} else {
			mOutput = input;
		}
	}

	double DeadBand::get()const {
		return mOutput;
	}
}
