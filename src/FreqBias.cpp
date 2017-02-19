// Component to model frequency bias for thermal power plant.
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
#include <FreqBias.hpp>
namespace SGFM {

	void FreqBias::init(
			double pu, double pl,
			double fuu, double ful, double flu, double fll)
	{
		mpu = pu;
		mpl = pl;
		mfuu = fuu;
		mful = ful;
		mflu = flu;
		mfll = fll;
	}

	int FreqBias::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mpu = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mpl = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mfuu = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mful = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mflu = buf;
			if(!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mfll = buf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int FreqBias::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mpu << std::endl;
			fout << mpl << std::endl;
			fout << mfuu << std::endl;
			fout << mful << std::endl;
			fout << mflu << std::endl;
			fout << mfll << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void FreqBias::set(double freqBias) {
		if (freqBias > mfuu) {
			mPowerBias = mpl;
		} else if (freqBias > mful) {
			mPowerBias = mpl * (freqBias - mful)/(mfuu - mful);
		} else if (freqBias > mflu) {
			mPowerBias = 0.0;
		} else if (freqBias > mfll) {
			mPowerBias = mpu * (mflu - freqBias)/(mflu - mfll);
		} else {
			mPowerBias = mpu;
		}
	}

	double FreqBias::get()const {
		return mPowerBias;
	}

}
