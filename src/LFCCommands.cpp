// LFC data storage.
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
#include <LFCCommands.hpp>

namespace SGFM {

	void LFCCommands::init(int nLFC)
	{
		mNGenerator=nLFC;
		mChangeRateLimitters = new ChangeRateLimitter[mNGenerator];
		for (int i = 0; i < mNGenerator; i++) {
			mChangeRateLimitters[i].init(0.001,0.1,0.0);
		}
	}

	int LFCCommands::read(const char *filename) {
		mNGenerator = 0;
		try {
			std::ifstream fin(filename);
			std::string buf;
			while (fin >> buf) {
				mNGenerator++;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}

		mChangeRateLimitters = new ChangeRateLimitter[mNGenerator];
		try {
			int i = 0;
			std::ifstream fin(filename);
			std::string buf;
			while (fin >> buf) {
				if (i >= mNGenerator) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				if(mChangeRateLimitters[i].read(buf.c_str())
						!= EXIT_SUCCESS)
				{
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				i++;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int LFCCommands::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;
			std::string sep = "_";

			for (int i=0; i < mNGenerator; i++) {
				std::string post = std::to_string(i);
				std::string subfilename = pre + sep + post;
				fout << subfilename << std::endl;
				if (mChangeRateLimitters[i].write(subfilename.c_str())
						!= EXIT_SUCCESS)
				{
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
			}
			delete[] mChangeRateLimitters;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void LFCCommands::set(double AR) {
		double sumChangerate = 0;
		for (int i=0; i < mNGenerator; i++) {
			sumChangerate += mChangeRateLimitters[i].cr();
		}
		for (int i=0; i < mNGenerator; i++) {
			double duty;
			duty = mChangeRateLimitters[i].cr() / sumChangerate;
			mChangeRateLimitters[i].set(AR*duty);
		}
	}

	double LFCCommands::get(int generatorNum)const {
		if (generatorNum >= mNGenerator) {
			return 0.0;
		}
		return mChangeRateLimitters[generatorNum].get();
	}

	int LFCCommands::size()const {
		return mNGenerator;
	}
}
