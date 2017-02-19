// Component to model frequency bias for thermal power plant.
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

#ifndef SGFM_FREQ_BIAS_HPP
#define SGFM_FREQ_BIAS_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace SGFM {

	/*
	 * FreqBias - Frequency bias for thermal power plant.
	 * This component simulates frequency bias for thermal power plant.
	 */
	class FreqBias {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double pu=0.05, // power bias upper limit [generator p.u.]
					double pl=-0.05, // power bias lower limit [generator p.u.]
					double fuu=0.0084, // frequency deviation upper side upper limit [p.u.]
					double ful=0.006, // frequency deviation upper side lower limit [p.u.]
					double flu=-0.006, // frequency deviation lower side upper limit [p.u.]
					double fll=-0.0084 // frequency deviation lower side lower limit [p.u.]
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: pu [generator p.u.]
			 * 2: pl [generator p.u.]
			 * 3: fuu [p.u.]
			 * 4: ful [p.u.]
			 * 5: flu [p.u.]
			 * 6: fll [p.u.]
			 */
			int read(const char *filename);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * set input frequency bias.
			 */
			void set(double freqBias);

			/*
			 * get output power bias.
			 */
			double get()const;

		private:
			/* model parameter */
			double mpu;
			double mpl;
			double mfuu;
			double mful;
			double mflu;
			double mfll;

			/* for output */
			double mPowerBias;
	};
}
#endif
