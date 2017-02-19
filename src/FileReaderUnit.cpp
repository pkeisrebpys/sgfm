// Group of FileReaders.
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

#include <FileReaderUnit.hpp>
namespace SGFM {

	void FileReaderUnit::init(int nData)
	{
		mSize = nData;
		mData = new FileReader[mSize];
		for (int i = 0; i < mSize; i++) {
			mData[i].init();
		}
		mOutput = 0.0;
	}

	int FileReaderUnit::read(const char *filename) {
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
		if (mSize == 0) {
			return EXIT_FAILURE;
		}
		mData = new FileReader[mSize];
		try {
			std::ifstream fin(filename);

			std::string buf;
			int i = 0;
			while (fin >> buf) {
				if( i >= mSize) {
					return EXIT_FAILURE;
				}
				if (mData[i].read(buf.c_str()) != EXIT_SUCCESS) {
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

	int FileReaderUnit::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;

			std::string sep = "_";
			for (int i = 0; i < mSize; i++) {
				std::string post = std::to_string(i);
				std::string bufname = pre + sep + post;
				fout << bufname << std::endl;
				if (mData[i].write(bufname.c_str()) != EXIT_SUCCESS) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
			}
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		delete[] mData;
		return EXIT_SUCCESS;
	}

	void FileReaderUnit::set() {
		mOutput = 0;
		for (int i = 0; i < mSize; i++) {
			mData[i].set();
			mOutput += mData[i].get();
		}
	}

	double FileReaderUnit::get()const {
		return mOutput;
	}

	double FileReaderUnit::get(int index)const {
		return mData[index].get();
	}

	void FileReaderUnit::log(int mode)const {
		if (mode==0) {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << mData[i].get();
			}
		} else {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << "RdData[" << i << "]";
			}
		}
	}

	int FileReaderUnit::size()const {
		return mSize;
	}

	int FileReaderUnit::cycle()const {
		int minCycle = mData[0].cycle();
		for (int i = 1; i < mSize; i++) {
			if (mData[i].cycle() < minCycle) {
				minCycle = mData[i].cycle();
			}
		}
		return minCycle;
	}

}
