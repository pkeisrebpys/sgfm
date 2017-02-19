// Component to model PI controller.
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
#include <PIController.hpp>

namespace SGFM {

	void PIController::init(
			double ka,
			double ta,
			double dt,
			double initErrorSum)
	{
		mka = ka;
		mta = ta;
		mdt = dt;
		mErrorSum = initErrorSum;
	}

	int PIController::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mka = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mta = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mdt = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mErrorSum = buf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int PIController::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mka << std::endl;
			fout << mta << std::endl;
			fout << mdt << std::endl;
			fout << mErrorSum << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void PIController::set(double error) {
		mErrorSum += error * mdt;
		mOutput = mka * error + mErrorSum / mta;
	}

	double PIController::get()const {
		return mOutput;
	}
	double PIController::ka()const {
		return mka;
	}
	double PIController::ta()const {
		return mta;
	}
	double PIController::dt()const {
		return mdt;
	}
	double PIController::ErrorSum()const {
		return mErrorSum;
	}

	void PIController::setOutput(double output) {
		mOutput = output;
	}

}
