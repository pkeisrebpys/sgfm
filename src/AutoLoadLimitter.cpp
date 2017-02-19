// Component to model automatic load limitter for thermal power plant.
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
#include <AutoLoadLimitter.hpp>
namespace SGFM {

	void AutoLoadLimitter::init(
			double widthGF,
			double upperGF,
			double lowerGF,
			double upperInt,
			double lowerInt,
			double dt,
			double initInt)
	{
		mWidthGF = widthGF;
		mGFLimitter.init(upperGF,lowerGF);
		mIntLimitter.init(upperInt,lowerInt,dt,initInt);
	}

	int AutoLoadLimitter::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("f>>b:1");
				return EXIT_FAILURE;
			}
			if (mGFLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read:1");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("f>>b:2");
				return EXIT_FAILURE;
			}
			if (mIntLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("read:2");
				return EXIT_FAILURE;
			}

			double dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("f>>b:3");
				return EXIT_FAILURE;
			}
			mWidthGF = dbuf;

			if(!(fin >> dbuf)) {
				PRINT_PASS("f>>b:3");
				return EXIT_FAILURE;
			}
			mOutput = dbuf;

		} catch (std::exception &e) {
			PRINT_PASS("read:exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int AutoLoadLimitter::write(const char *filename)const
	{
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_l";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mGFLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("write:1");
				return EXIT_FAILURE;
			}

			post = "_il";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mIntLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("write:2");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mWidthGF << std::endl;
			fout << mOutput << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("write:exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void AutoLoadLimitter::set(double governorConf) {
		mGFLimitter.set(governorConf+mWidthGF-mOutput);
		mIntLimitter.set(mGFLimitter.get());
		mOutput = mIntLimitter.get();
	}

	double AutoLoadLimitter::get()const {
		return mOutput;
	}

}
