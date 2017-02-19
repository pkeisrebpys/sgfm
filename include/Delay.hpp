// Component to model delay.
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

#ifndef SGFM_DELAY_HPP
#define SGFM_DELAY_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <PrintPass.hpp>

namespace SGFM {

	/*
	 * Delay - Signal delay model.
	 */
	template <class T>
	class Delay {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double delayTime = 3.0, // Delay time [s].
					double dt = 0.1, // Simulation interval time [s].
					int initPosition = 0 // Initial data position.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: initPosition
			 * 2: delayTime
			 * 3: dt
			 * after line 3, buffered data is stored.
			 */
			int read(const char *filename);

			/*
			 * Write config to file.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * Set input value.
			 */
			void set(T input);

			/* 
			 * Get output value.
			 */
			T get()const;

		private:
			/* Model parameter */
			double mDelayTime;

			/* Simulation paramrter */
			double mdt;

			/*
			 * Internal values.
			 */
			int mPosition;
			int mSize;
			T *mData;

			/* output parameter */
			T mOutput;
	};

	template <class T>
	void Delay<T>::init(
			double delayTime,
			double dt,
			int initPosition)
	{
		mDelayTime = delayTime;
		mdt = dt;
		mPosition = initPosition;

		mSize = mDelayTime / mdt;
		mData = new T[mSize];
		for (int i = 0; i < mSize; i++) {
			mData[i] = 0;
		}
		mOutput = 0;
	}

	template <class T>
	int Delay<T>::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			int ibuf;
			if(!(fin >> ibuf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mPosition = ibuf;

			double buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mDelayTime = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mdt = buf;
			mSize = mDelayTime / mdt;
			mData = new T[mSize];
			T databuf;
			int i = 0;
			while(fin >> databuf) {
				mData[i] = databuf;
				i++;
				if (i >= mSize) {
					break;
				}
			}
			mOutput = 0.0;
		} catch (std::exception &e) {
			PRINT_PASS("File read error.");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	template <class T>
	int Delay<T>::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << mPosition << std::endl;

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << mDelayTime << std::endl;
			fout << mdt << std::endl;
			for (int i = 0; i < mSize; i++) {
				fout << mData[i] << std::endl;
			}
		} catch (std::exception &e) {
			PRINT_PASS("File write error.");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	
	template <class T>
	void Delay<T>::set(T input) {
		mOutput = mData[mPosition];
		mData[mPosition] = input;
		mPosition++;
		mPosition = mPosition % mSize;
	}

	template <class T>
	T Delay<T>::get()const {
		return mOutput;
	}
}
#endif
