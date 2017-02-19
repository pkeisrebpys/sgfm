// Group of generators.
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
#include <GeneratorUnit.hpp>
namespace SGFM {

	void GeneratorUnit::init(int size)
	{
		mSize = size;
		mUnit = new Generator* [mSize];
		for (int i = 0; i < mSize; i++) {
			mUnit[i] = new Thermal;
			mUnit[i]->init(4.0);
		}
		mOutput = 0.0;
	}

	int GeneratorUnit::read(const char *filename) {
		mSize = 0;
		try {
			std::ifstream fin(filename);

			std::string buf;
			while (fin >> buf) {
				mSize++;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		if (mSize % 2 != 0) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		mSize /= 2;
		if (mSize == 0) {
			return EXIT_FAILURE;
		}
		mUnit = new Generator* [mSize];
		try {
			std::ifstream fin(filename);

			std::string buf;
			std::string nameThermal = "Thermal";
			int i = 0;
			while (fin >> buf) {
				if( i >= mSize) {
					return EXIT_FAILURE;
				}

				if (buf == nameThermal) {
					mUnit[i] = new Thermal;
				} else {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}

				if (!(fin >> buf)) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				if (mUnit[i]->read(buf.c_str()) != EXIT_SUCCESS) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				i++;
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int GeneratorUnit::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;
			std::string sep = "_";

			for (int i = 0; i < mSize; i++) {
				fout << mUnit[i]->name() << std::endl;
				std::string post = std::to_string(i);
				std::string bufname = pre + sep + post;
				fout << bufname << std::endl;
				if (mUnit[i]->write(bufname.c_str()) != EXIT_SUCCESS) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				delete mUnit[i];
			}

		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		delete[] mUnit;
		return EXIT_SUCCESS;
	}

	void GeneratorUnit::set(double freqDeviation, const DataBus<double>& lfc, const DataBus<double>& edc) {
		for (int i = 0; i < mSize; i++) {
			mUnit[i]->set(
					freqDeviation,
					lfc.get(i)
					+edc.get(i));
		}
		mOutput = 0;
		for (int i = 0; i < mSize; i++) {
			mOutput += mUnit[i]->get();
		}
	}


	double GeneratorUnit::get()const {
		return mOutput;
	}

	void GeneratorUnit::log(int mode)const {
		if (mode==0) {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << mUnit[i]->get();
				mUnit[i]->log(mode);
			}
		} else {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << "GUnit[" << i << "]";
				mUnit[i]->log(mode);
			}
		}
	}

	int GeneratorUnit::size()const {
		return mSize;
	}

}
