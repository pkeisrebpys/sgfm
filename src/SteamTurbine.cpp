// Component to model steam turbine for thermal power plant.
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
#include <SteamTurbine.hpp>
namespace SGFM {

	void SteamTurbine::init(
			double tall, double tlow, double ratehp,
			double dt,
			double initAllInput, double initAllOutput,
			double initLowInput, double initLowOutput)
	{
		mAllDelay.init(tall,dt,initAllInput,initAllOutput);
		mLowDelay.init(tlow,dt,initLowInput,initLowOutput);
		mRateHP = ratehp;
	}

	int SteamTurbine::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAllDelay.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mLowDelay.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			double dbuf;
			if(!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mRateHP = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int SteamTurbine::write(const char *filename)const
	{
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_a";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mAllDelay.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_l";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mLowDelay.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mRateHP << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void SteamTurbine::set(double steamPressure) {
		mAllDelay.set(steamPressure);
		double turbinInput = mAllDelay.get();

		mLowDelay.set((1.0 - mRateHP) * turbinInput);
		double lpOutput = mLowDelay.get();

		double hpOutput = mRateHP * turbinInput;

		mOutput = lpOutput + hpOutput;
	}

	double SteamTurbine::get()const {
		return mOutput;
	}
}
