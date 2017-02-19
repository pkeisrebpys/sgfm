// LFC calculation Unit.
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

#include <PrintPass.hpp>
#include <LFCUnit.hpp>
namespace SGFM {

	void LFCUnit::init(int nLFC, int LFCmode)
	{
		mAreaReq.init();
		mAreaReqSmoothing.init();
		mDeadBand.init(0.002,-0.002);
		mAreaReqPI.init();
		mLFCCommands.init(nLFC);
		mLFCMode = LFCmode;
	}

	int LFCUnit::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mAreaReq.read(buf.c_str());
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mAreaReqSmoothing.read(buf.c_str());
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mDeadBand.read(buf.c_str());
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mAreaReqPI.read(buf.c_str());
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mLFCCommands.read(buf.c_str());

			int ibuf;
			if (!(fin >>ibuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mLFCMode = ibuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int LFCUnit::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_ar";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaReq.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_sm";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaReqSmoothing.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_db";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mDeadBand.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_pi";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAreaReqPI.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_dt";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mLFCCommands.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << mLFCMode << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void LFCUnit::set(double freqDeviation, double gridCapLocal, double gridCapOther, double tieLinePower) {
		if (mLFCMode == modeFFC) {
			mDeadBand.set(freqDeviation);
			mAreaReq.set(mDeadBand.get(),gridCapLocal,gridCapOther,tieLinePower);
			mAreaReqSmoothing.set(mAreaReq.get());
			mAreaReqPI.set(mAreaReqSmoothing.get());
		} else if (mLFCMode == modeTBC) {
			mAreaReq.set(freqDeviation,gridCapLocal,gridCapOther,tieLinePower);
			mAreaReqSmoothing.set(mAreaReq.get());
			mDeadBand.set(mAreaReqSmoothing.get());
			mAreaReqPI.set(mAreaReqSmoothing.get());
		}
		mLFCCommands.set(mAreaReqPI.get());
	}

	double LFCUnit::get(int index)const {
		return mLFCCommands.get(index);
	}

	int LFCUnit::size()const {
		return mLFCCommands.size();
	}

}
