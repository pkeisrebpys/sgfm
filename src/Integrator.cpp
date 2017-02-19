// Component to model Integrator.
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
#include <Integrator.hpp>

namespace SGFM {

	void Integrator::init(double dt, double initSum)
	{
		mdt = dt;
		mOutput = initSum;
	}

	int Integrator::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mdt = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mOutput = buf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Integrator::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mdt << std::endl;
			fout << mOutput << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void Integrator::set(double input) {
		mOutput += input * mdt;
	}

	double Integrator::get()const {
		return mOutput;
	}

	void Integrator::setOutput(double input) {
		mOutput = input;
	}

}
