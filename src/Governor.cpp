// Component to model governor for thermal power plant.
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
#include <Governor.hpp>
namespace SGFM {

	void Governor::init(
			double speedRegulation, double tGovernor,
			double dt,
			double initDelayInput, double initDelayOutput)
	{
		mSpeedRegulation = speedRegulation;
		mDelay.init(tGovernor,dt,initDelayInput,initDelayOutput);
	}

	int Governor::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mDelay.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			double dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mSpeedRegulation = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Governor::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_d";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mDelay.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mSpeedRegulation << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void Governor::set(double freqDeviation, double loadConf, double loadLimit) {
		mDelay.set(mSpeedRegulation * freqDeviation);
		double governorConf = loadConf - mDelay.get();

		if (governorConf < loadLimit) {
			mOutput = governorConf;
		} else {
			mOutput = loadLimit;
		}
	}

	double Governor::get()const {
		return mOutput;
	}

}
