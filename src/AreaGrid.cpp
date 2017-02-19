// Area grid model.
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
#include <AreaGrid.hpp>
namespace SGFM {

	void AreaGrid::init(int nEDC, int nBase, int nLoad)
	{
		mInertia.init(1.0);
		mGeneratorUnit.init(nEDC);
		mBaseUnit.init(nBase);
		mLoadUnit.init(nLoad);
	}

	int AreaGrid::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			std::string buf;
			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mInertia.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mLoadUnit.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mBaseUnit.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			if (!(fin >> buf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			if (mGeneratorUnit.read(buf.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int AreaGrid::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string post = "_in";
			std::string bufname = pre + post;
			fout << bufname << std::endl;
			if (mInertia.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_lu";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mLoadUnit.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_bu";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mBaseUnit.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			post = "_tu";
			bufname = pre + post;
			fout << bufname << std::endl;
			if (mGeneratorUnit.write(bufname.c_str()) != EXIT_SUCCESS) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void AreaGrid::set(double tieLinePower, const DataBus<double>& lfc, const DataBus<double>& edc) {
		mLoadUnit.set();
		mBaseUnit.set();
		mGeneratorUnit.set(mInertia.get(),lfc,edc);

		double powerDeviation = 0; // P [p.u.]
		powerDeviation -= tieLinePower; // from local to other is positive
		powerDeviation -= mLoadUnit.get();
		powerDeviation += mBaseUnit.get();
		powerDeviation += mGeneratorUnit.get();

		mInertia.set(powerDeviation); // delta P [p.u.], generation is positive

	}

	double AreaGrid::get()const {
		return mInertia.get();
	}

	void AreaGrid::log(int mode)const {
		mInertia.log(mode);
		mLoadUnit.log(mode);
		mBaseUnit.log(mode);
		mGeneratorUnit.log(mode);
	}

	int AreaGrid::cycle()const {
		int minCycle = mLoadUnit.cycle();
		if (minCycle > mBaseUnit.cycle()) {
			minCycle = mBaseUnit.cycle();
		}
		return minCycle;
	}

}
