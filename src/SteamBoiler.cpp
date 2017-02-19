// Component to model steam boiler for thermal power plant.
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
#include <SteamBoiler.hpp>
namespace SGFM {

	void SteamBoiler::init(
			double tBoilSteam,
			double mainPowerUpper, double mainPowerLower,
			double mainPressureUpper, double mainPressureLower,
			double tBoiler,
			double tControl,
			double dt,
			double initRefInput, double initBoidSteam,
			double initSteamError,
			double initBoilerError, double initControlError)
	{
		mDelayBoilSteam.init(tBoilSteam,dt,initRefInput,initBoidSteam);
		mMainPConf.init(mainPowerUpper,mainPowerLower,mainPressureUpper,mainPressureLower);
		mDelayBoilError.init(tBoiler,dt,initSteamError,initBoilerError);
		mDelayControl.init(tControl,dt,initBoilerError,initControlError);
	}

	int SteamBoiler::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mDelayBoilSteam.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mMainPConf.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mDelayBoilError.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mDelayControl.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			
			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mDeviation = dbuf;

		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int SteamBoiler::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_db";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mDelayBoilSteam.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_mp";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mMainPConf.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_eb";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mDelayBoilError.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_ec";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mDelayControl.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mDeviation << std::endl;

		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	void SteamBoiler::set(double powerRef, double outputFlow) {
		mDelayBoilSteam.set(powerRef);
		double boilerSteam = mDelayBoilSteam.get();
		mMainPConf.set(boilerSteam);
		double steamError = boilerSteam - outputFlow;
		mDelayBoilError.set(steamError);
		mDelayControl.set(steamError);
		mDeviation = mDelayBoilError.get() - mDelayControl.get();
		mPressure = mMainPConf.get() + mDeviation;
	}

	double SteamBoiler::get()const {
		return mPressure;
	}

	double SteamBoiler::getDeviation()const {
		return mDeviation;
	}
}
