// Component to model first order filter.
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

#ifndef SGFM_FIRST_ORDER_FILTER_HPP
#define SGFM_FIRST_ORDER_FILTER_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace SGFM {

	/*
	 * FirstOrderFilter - First order filter component described as (cs+d)/(as+b).
	 */
	class FirstOrderFilter {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double a=1.0,
					double b=1.0,
					double c=0.0,
					double d=1.0,
					double dt=0.1, // simulation interval time [s].
					double initInput=0.0, // initial input value.
					double initOutput=0.0 // initial output value.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: a
			 * 2: b
			 * 3: c
			 * 4: d
			 * 5: dt
			 * 6: initial input
			 * 7: initial output
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
			void set(double input);

			/* 
			 * Get output value.
			 */
			double get()const;

			/*
			 * Log model state on stdout with tab separated format.
			 */
			void log(int mode=0)const;

			double a()const;
			double dt()const;
			double x1()const;
			double y1()const;

		private:
			/*
			 * Coefficients of filter.
			 */
			double ma;
			double mb;
			double mc;
			double md;

			/* simulation paramrter */
			double mdt;

			/*
			 * internal values.
			 */
			double mx1;
			double my1;

			/* output parameter */
			double mOutput;
	};
}
#endif
