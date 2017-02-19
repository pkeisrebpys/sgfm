// Component to model AR PI controller.
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
#include <AreaReqPI.hpp>
namespace SGFM {

	void AreaReqPI::init(
			double kp,
			double ki,
			double dt,
			double ts,
			double initElapsed,
			double initSum)
	{
		mdt = dt;
		mElapsedT = initElapsed;
		mPIController.init(kp,1.0/ki,ts,initSum);
	}

	int AreaReqPI::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mPIController.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mdt = dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mElapsedT = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int AreaReqPI::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_pi";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mPIController.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mdt << std::endl;
			fout << mElapsedT << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void AreaReqPI::set(double AR) {
		mElapsedT += mdt;
		if (mElapsedT >= mPIController.dt()) {
			mPIController.set(AR);
			mElapsedT -= mPIController.dt();
		}
	}

	double AreaReqPI::get()const {
		return mPIController.get();
	}

}
