// EDC calculation Unit.
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
#include <EDCUnit.hpp>
namespace SGFM {

	void EDCUnit::init(int nData)
	{
			mEDCData.init(nData);
	}

	int EDCUnit::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			std::string buf;

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mEDCData.read(buf.c_str());
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int EDCUnit::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_dt";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mEDCData.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void EDCUnit::set() {
		mEDCData.set();
	}

	double EDCUnit::get(int index)const {
		return mEDCData.get(index);
	}

	void EDCUnit::log(int mode)const {
		mEDCData.log(mode);
	}
	int EDCUnit::cycle()const {
		return mEDCData.cycle();
	}

	int EDCUnit::size()const {
		return mEDCData.size();
	}

}
