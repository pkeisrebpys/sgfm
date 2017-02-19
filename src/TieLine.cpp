// Tie line model.
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

#include <TieLine.hpp>

namespace SGFM {

	void TieLine::init()
	{
	}

	int TieLine::read(const char *filename) {
		return EXIT_SUCCESS;
	}

	int TieLine::write(const char *filename)const {
		return EXIT_SUCCESS;
	}


	void TieLine::set(double srcAreaFreqDev, double dstAreaFreqDev) {
		mTieLinePower = 0;
	}

	double TieLine::get()const {
		return mTieLinePower;
	}

	void TieLine::log(int mode)const {
		if (mode == 0) {
			std::cout << '\t' << mTieLinePower;
		} else {
			std::cout << '\t' << "P_TieLine";
		}
	}

}
