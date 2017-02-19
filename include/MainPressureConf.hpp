// Component to model main pressure configurator for thermal power plant.
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

#ifndef SGFM_MAIN_PRESSURE_CONF_HPP
#define SGFM_MAIN_PRESSURE_CONF_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace SGFM {

	/*
	 * MainPressureConf - Main pressure configurator for thermal power plant..
	 * This component simulates main pressure configurator for thermal power plant.
	 */
	class MainPressureConf {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double uPower=0.9, // upper power limit
					double lPower=0.3, // lower power limit
					double uPressure=1.0, // upper presure limit.
					double lPressure=0.4 // lower pressure limit.
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line.
			 * 1: uPower
			 * 2: lPower
			 * 3: uPressure
			 * 4: lPressure
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
			 * set power.
			 */
			void set(double power);

			/*
			 * get pressure.
			 */
			double get()const;

		private:
			/* model parameter */
			double mUpperPower;
			double mLowerPower;
			double mUpperPressure;
			double mLowerPressure;

			/* for output */
			double mPressure;
	};
}
#endif
