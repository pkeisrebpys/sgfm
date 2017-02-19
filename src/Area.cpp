// Area model.
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

#include <Area.hpp>
namespace SGFM {

	void Area::init(int nEDC, int nBase, int nLoad, double gridCap)
	{
		mLFCBus.init(nEDC);
		mEDCBus.init(nEDC);
		mAreaGrid.init(nEDC,nBase,nLoad);
		mAreaControl.init(nEDC);
		mGridCap = gridCap; // [grid p.u.]
	}

	int Area::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mLFCBus.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mEDCBus.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAreaGrid.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAreaControl.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mGridCap = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Area::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_lfc";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mLFCBus.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_edc";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mEDCBus.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_gr";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaGrid.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_ct";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaControl.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mGridCap << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void Area::set(double gridCapOther, double tieLinePower) {
		mAreaGrid.get();
		mAreaControl.set(mAreaGrid.get(),mGridCap,gridCapOther,tieLinePower);
		for (int i = 0; i < mAreaControl.numGen(); i++) {
			mLFCBus.set(i,mAreaControl.LFCsignal(i));
			mEDCBus.set(i,mAreaControl.EDCsignal(i));
		}
		mAreaGrid.set(tieLinePower,mLFCBus,mEDCBus);
	}

	double Area::get()const {
		return mAreaGrid.get();
	}

	void Area::log(int mode)const {
		mLFCBus.log(mode);
		mEDCBus.log(mode);
		mAreaGrid.log(mode);
		mAreaControl.log(mode);
	}

	int Area::cycle()const {
		int minCycle = mAreaGrid.cycle();
		if (minCycle > mAreaControl.cycle()) {
			minCycle = mAreaControl.cycle();
		}
		return minCycle;
	}

	double Area::gridCap()const {
		return mGridCap;
	}
}
