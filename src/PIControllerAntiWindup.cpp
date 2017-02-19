// Component to model PI controller with anti-windup control.
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
#include <PIControllerAntiWindup.hpp>

namespace SGFM {

	void PIControllerAntiWindup::init(
			double ka, double ta,
			double dt,
			double initErrorSum,
			double upper, double lower,
			double initAntiWindupFB)
	{
		PIController::init(ka,ta,dt,initErrorSum);
		outputLimitter.init(upper,lower);
		mAntiWindupFB = initAntiWindupFB;
	}

	int PIControllerAntiWindup::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (PIController::read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (outputLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			double dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mAntiWindupFB = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int PIControllerAntiWindup::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_p";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (PIController::write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_l";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (outputLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mAntiWindupFB << std::endl;

		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void PIControllerAntiWindup::set(double error) {
		PIController::set(error-mAntiWindupFB);
		double preLimit = PIController::get() + mAntiWindupFB * PIController::ka();

		outputLimitter.set(preLimit);
		PIController::setOutput(outputLimitter.get());
		mAntiWindupFB = (preLimit - get())/PIController::ka();
	}

}
