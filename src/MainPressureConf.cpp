// Component to model main pressure configurator for thermal power plant.
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
#include <MainPressureConf.hpp>
namespace SGFM {

	void MainPressureConf::init(
			double uPower, double lPower,
			double uPressure, double lPressure)
	{
		mUpperPower = uPower;
		mLowerPower = lPower;
		mUpperPressure = uPressure;
		mLowerPressure = lPressure;
	}

	int MainPressureConf::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mUpperPower = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mLowerPower = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mUpperPressure = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mLowerPressure = buf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int MainPressureConf::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mUpperPower << std::endl;
			fout << mLowerPower << std::endl;
			fout << mUpperPressure << std::endl;
			fout << mLowerPressure << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void MainPressureConf::set(double power) {
		if (power > mUpperPower) {
			mPressure = mUpperPressure;
		} else if (power > mLowerPower) {
			mPressure = mLowerPressure
				+ (mUpperPressure - mLowerPressure)
				* (power - mLowerPower)
				/ (mUpperPower - mLowerPower);
		} else {
			mPressure = mLowerPressure;
		}
	}

	double MainPressureConf::get()const {
		return mPressure;
	}

}
