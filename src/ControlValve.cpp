// Component to model control valve (CV) in thermal power plant.
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
#include <ControlValve.hpp>

namespace SGFM {

	void ControlValve::init(
			double gain,
			double gainUpper,
			double gainLower,
			double intUpper,
			double intLower,
			double dt,
			double initSum,
			double initOutput)
	{
		mGain = gain;
		gainLimitter.init(gainUpper,gainLower);
		limitedInt.init(intUpper,intLower,dt,initSum);
		mOutput = initOutput;
	}

	int ControlValve::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			if (gainLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			if (limitedInt.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read");
				return EXIT_FAILURE;
			}
			double dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mGain = dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mOutput = dbuf;
		} catch (std::exception &e) {
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int ControlValve::write(const char *filename)const
	{
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_l";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (gainLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("write");
				return EXIT_FAILURE;
			}

			post = "_il";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (limitedInt.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("write");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mGain << std::endl;
			fout << mOutput << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void ControlValve::set(double input) {
		gainLimitter.set(mGain*(input-mOutput));
		limitedInt.set(gainLimitter.get());
		mOutput = limitedInt.get();
	}

	double ControlValve::get()const {
		return mOutput;
	}

}
