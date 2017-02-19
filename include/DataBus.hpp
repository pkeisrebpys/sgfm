// Data bus with delay model
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

#ifndef SGFM_DATA_BUS_HPP
#define SGFM_DATA_BUS_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <Delay.hpp>
namespace SGFM {

	/*
	 * DataBus - Data bus with delay.
	 */
	template <class T>
	class DataBus {
		public:
			/*
			 * Initialize with default value.
			 */
			void init(
					int size=2, // number of data lines.
					double delayTime=3.0, // Delay time [s].
					double dt = 0.1 // Simulation interval time [s].
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each data line delya is stored is written one by one.
			 * Number of data line is counted by number of lines in the file.
			 */
			int read(const char *filename);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * Be care, When this method is called,
			 * allocated array for Thermal parameters are deleted.
			 */
			int write(const char *filename)const;

			/*
			 * set input.
			 * index: data line index
			 * input: data.
			 */
			void set(int index, T data);

			/*
			 * get sum of output power
			 */
			T get(int index)const;

			/*
			 * log model state on stdout with tab separated format.
			 */
			void log(int mode=0, std::string name="mDelay")const;

			/*
			 * get number of data lines
			 */
			int size()const;

		private:
			/* model parameter */
			int mSize; // number of data lines.
			Delay<T> *mDelay; // data delay line.

	};

	template <class T>
	void DataBus<T>::init(int size, double delayTime, double dt)
	{
		mSize = size;
		mDelay = new Delay<T>[mSize];
		for (int i = 0; i < mSize; i++) {
			mDelay[i].init(delayTime,dt);
		}
	}

	template <class T>
	int DataBus<T>::read(const char *filename) {
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

		mDelay = new Delay<T>[mSize];
		try {
			std::ifstream fin(filename);

			std::string buf;
			int i = 0;
			while (fin >> buf) {
				if( i >= mSize) {
					break;
				}
				if (mDelay[i].read(buf.c_str()) != EXIT_SUCCESS) {
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

	template <class T>
	int DataBus<T>::write(const char *filename)const {
		try {
			std::ofstream fout(filename);
			std::string pre = filename;
			std::string sep = "_";

			for (int i = 0; i < mSize; i++) {
				std::string post = std::to_string(i);
				std::string bufname = pre + sep + post;
				fout << bufname << std::endl;
				if (mDelay[i].write(bufname.c_str()) != EXIT_SUCCESS) {
					PRINT_PASS("");
					return EXIT_FAILURE;
				}
			}
			delete[] mDelay;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	template <class T>
	void DataBus<T>::set(int index, T data) {
		if (index < mSize) {
			mDelay[index].set(data);
		}
	}


	template <class T>
	T DataBus<T>::get(int index)const {
		if (index < mSize) {
			return mDelay[index].get();
		}
		return 0;
	}

	template <class T>
	void DataBus<T>::log(int mode, std::string name)const {
		if (mode == 0) {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << mDelay[i].get();
			}
		} else {
			for (int i = 0; i < mSize; i++) {
				std::cout << '\t' << name << "[" << i << "]";
			}
		}
	}

	template <class T>
	int DataBus<T>::size()const {
		return mSize;
	}

}
#endif
