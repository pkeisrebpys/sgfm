// Area control model.
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

#include <AreaControl.hpp>
namespace SGFM {

	void AreaControl::init(int nEDC)
	{
		mLFCUnit.init(nEDC);
		mEDCUnit.init(nEDC);
	}

	int AreaControl::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mLFCUnit.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mEDCUnit.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int AreaControl::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_lfc";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mLFCUnit.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_edc";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mEDCUnit.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void AreaControl::set(double freqDeviation, double gridCapLocal, double gridCapOther, double tieLinePower) {
		mLFCUnit.set(freqDeviation,gridCapLocal,gridCapOther,tieLinePower);
		mEDCUnit.set();
	}

	double AreaControl::LFCsignal(int index)const {
		return mLFCUnit.get(index);
	}

	double AreaControl::EDCsignal(int index)const {
		return mEDCUnit.get(index);
	}

	void AreaControl::log(int mode)const {
		mEDCUnit.log(mode);
	}

	int AreaControl::cycle()const {
		return mEDCUnit.cycle();
	}

	int AreaControl::numGen()const {
		return mLFCUnit.size();
	}
}
