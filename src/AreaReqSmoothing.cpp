// Component to model AR smoothing
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
#include <AreaReqSmoothing.hpp>
namespace SGFM {

	void AreaReqSmoothing::init(
			double coSmoothing,
			double tControl,
			double dt,
			double elapsedTime,
			double initAR)
	{
		mCoSmoothing = coSmoothing;
		mtControl = tControl;
		mdt = dt;
		mElapsedTime = elapsedTime;
		mOutput = initAR;
	}

	int AreaReqSmoothing::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mCoSmoothing = dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mtControl = dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mdt = dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mOutput = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int AreaReqSmoothing::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mCoSmoothing << std::endl;
			fout << mtControl << std::endl;
			fout << mdt << std::endl;
			fout << mOutput << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void AreaReqSmoothing::set(double AR) {
		mElapsedTime += mdt;
		if (mElapsedTime >= mtControl) {
			mOutput = mCoSmoothing * (AR - mOutput) + mOutput;
			mElapsedTime -= mtControl;
		}
	}

	double AreaReqSmoothing::get()const {
		return mOutput;
	}

}
