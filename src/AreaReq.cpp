// Component to model AR.
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
#include <AreaReq.hpp>
namespace SGFM {

	void AreaReq::init(double gridConst)
	{
		mGridConst = gridConst;
	}

	int AreaReq::read(const char *filename) {
			try {
			std::ifstream fin(filename);

			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mGridConst = dbuf;
			} catch (std::exception &e) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			return EXIT_SUCCESS;
	}

	int AreaReq::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mGridConst << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void AreaReq::set(double freqDeviation, double gridCapLocal, double gridCapOther, double tieLinePower) {
		mOutput = tieLinePower - mGridConst * (gridCapLocal + gridCapOther) * freqDeviation;
	}

	double AreaReq::get()const {
		return mOutput;
	}

}
