// Resion model.
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

#include <Resion.hpp>

namespace SGFM {

	void Resion::init(int nEDC, int nBase, int nLoad)
	{
		mTieLine.init();
		mAreaLocal.init(nEDC,nBase,nLoad);
		mAreaOther.init();
	}

	int Resion::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mTieLine.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAreaLocal.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAreaOther.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Resion::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_ti";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mTieLine.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_lo";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaLocal.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_ot";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaOther.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void Resion::set() {
		mTieLine.set(mAreaLocal.get(),mAreaOther.get());
		mAreaLocal.set(mAreaOther.gridCap(),mTieLine.get());
		mAreaOther.set(mAreaLocal.gridCap(),mTieLine.get());
	}

	double Resion::get()const {
		return mAreaLocal.get();
	}

	void Resion::log(int mode)const {
		mTieLine.log(mode);
		mAreaLocal.log(mode);
		mAreaOther.log(mode);
	}

	int Resion::cycle()const {
		int minCycle = mAreaLocal.cycle();
		if (minCycle > mAreaOther.cycle()) {
			minCycle = mAreaOther.cycle();
		}
		return minCycle;
	}

}
