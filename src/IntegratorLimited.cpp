// Component to model integrator with limit.
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
#include <IntegratorLimited.hpp>

namespace SGFM {

	void IntegratorLimited::init(
			double upper,
			double lower,
			double dt,
			double initSum)
	{
		Integrator::init(dt,initSum);
		limitter.init(upper,lower);
	}

	int IntegratorLimited::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("read:1");
				return EXIT_FAILURE;
			}
			if (Integrator::read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read:1");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("read:2");
				return EXIT_FAILURE;
			}
			if (limitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read:2");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int IntegratorLimited::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_i";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (Integrator::write(bufname.c_str()) != EXIT_SUCCESS) return EXIT_FAILURE;

			post = "_l";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (limitter.write(bufname.c_str()) != EXIT_SUCCESS) return EXIT_FAILURE;
		} catch (std::exception &e) {
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void IntegratorLimited::set(double input) {
		Integrator::set(input);
		limitter.set(Integrator::get());
		Integrator::setOutput(limitter.get());
	}

}
