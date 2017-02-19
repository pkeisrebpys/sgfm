// Component to model thermal power plant for grid frequency simulation.
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
#include <Thermal.hpp>
namespace SGFM {

	void Thermal::init(double capacity)
	{
		mFreqBias.init(0.05,-0.05,0.0084,0.006-0.006,-0.0084);
		mRefChangeLimitter.init(0.0005,0.1,0.75);
		mRefLimitter.init(1.0,0.3);
		mSteamBoiler.init(120.0,0.9,0.3,1.0,0.4,60.0,150.0,0.1,0.75,0.75);
		mLoadRefPI.init(0.5,30.0,1.2,0.0);
		mGovernor.init(25.0,0.2,0.1);
		mAutoLoadLimitter.init(0.05,0.00083,-0.00083,1.05,0.0,0.1);
		mControlValve.init(5.0,0.2,-1000.0,1.05,0.0,0.1);
		mSteamTurbine.init(0.25,9.0,0.3,0.1);

		mCapacity = capacity;
		mOutput = 0.75;
		mSteamFlow = 0.75;
	}

	int Thermal::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mFreqBias.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mRefChangeLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mRefLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mSteamBoiler.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mLoadRefPI.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mGovernor.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mAutoLoadLimitter.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mControlValve.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mSteamTurbine.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			double dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mCapacity = dbuf;

			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mOutput = dbuf;

			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mSteamFlow = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int Thermal::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_fb";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mFreqBias.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_cr";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mRefChangeLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_rl";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mRefLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_sb";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mSteamBoiler.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_pi";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mLoadRefPI.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_gv";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mGovernor.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_al";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mAutoLoadLimitter.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_cv";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mControlValve.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_st";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mSteamTurbine.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mCapacity << std::endl;
			fout << mOutput << std::endl;
			fout << mSteamFlow << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void Thermal::set(double freqDeviation, double refOutput) {
		refOutput /= mCapacity;
		// calculate output reference MWD'
		mFreqBias.set(freqDeviation);
		mRefChangeLimitter.set(refOutput);
		mRefLimitter.set(mFreqBias.get() + mRefChangeLimitter.get());

		// CV position calculation
		mLoadRefPI.set(mRefLimitter.get()-mOutput+mSteamBoiler.getDeviation());
		mGovernor.set(freqDeviation,mLoadRefPI.get(),mAutoLoadLimitter.get());
		mAutoLoadLimitter.set(mGovernor.get());
		mControlValve.set(mGovernor.get());

		// calculate main steam pressure
		mSteamBoiler.set(mRefLimitter.get(),mSteamFlow);

		// calculate main steam flow
		mSteamFlow = mControlValve.get()*mSteamBoiler.get();

		// calculate output power
		mSteamTurbine.set(mSteamFlow);
		mOutput = mSteamTurbine.get();
	}

	void Thermal::log(int mode)const {
		if (mode == 0) {
			std::cout << '\t' << mRefLimitter.get();
			std::cout << '\t' << mLoadRefPI.get();
			std::cout << '\t' << mAutoLoadLimitter.get();
			std::cout << '\t' << mGovernor.get();
			std::cout << '\t' << mControlValve.get();
			std::cout << '\t' << mSteamBoiler.get();

		} else {
			std::cout << '\t' << "freqbias ";
			std::cout << '\t' << "PIcontrol";
			std::cout << '\t' << "AutoLoadLim";
			std::cout << '\t' << "Governot ";
			std::cout << '\t' << "ControlValve";
			std::cout << '\t' << "SteamBoiler";
		}
	}

	std::string Thermal::name()const {
		std::string name = "Thermal";
		return name;
	}


}
