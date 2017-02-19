// Component to read load or generation power data.
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
#include <FileReader.hpp>
namespace SGFM {

	void FileReader::init(int nData, double tSample, double dt, int position, double elapsedTime)
	{
		for (int i = 0; i < nData; i++) {
			mData.emplace_back(0.0);
		}
		mts = tSample;
		mdt = dt;
		mPosition = position;
		mElapsedTime = elapsedTime;
	}

	int FileReader::read(const char *filename) {
		try {
			std::ifstream fin(filename);

			if (!(fin >> mDataFileName)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			try {
				std::ifstream fdata(mDataFileName.c_str());
				double data;
				while (fdata >> data) {
					mData.emplace_back(data);
				}
			} catch (std::exception &e) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}

			unsigned int ibuf = 0;
			if (!(fin >> ibuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mPosition = ibuf;

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
			mts = dbuf;
			if (!(fin >> dbuf)) {
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			mElapsedTime = dbuf;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int FileReader::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			if (mDataFileName.empty()) {
				std::string pre = filename;
				std::string post = "_dt";
				std::string curFileName = pre + post;
				try {
					std::ofstream fdata(curFileName.c_str());
					for (double const &data: mData) {
						fdata << data << std::endl;
					}
				} catch (std::exception &e) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
				fout << curFileName << std::endl;
			} else {
				fout << mDataFileName << std::endl;
			}

			fout << mPosition << std::endl;

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mdt << std::endl;
			fout << mts << std::endl;
			fout << mElapsedTime << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}


	void FileReader::set() {
		mElapsedTime += mdt;
		if (mElapsedTime >= mts) {
			mPosition++;
			mPosition = mPosition % mData.size();
			mElapsedTime -= mts;
		}
	}

	double FileReader::get()const {
		return mData[mPosition];
	}

	int FileReader::size()const {
		return mData.size();
	}

	int FileReader::cycle()const {
		double factor = mts / mdt;
		return (int)((double)mData.size() * factor);
	}

}
