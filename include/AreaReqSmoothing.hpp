// Component to model AR smoothing
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

#ifndef SGFM_AR_SMOOTHING_HPP
#define SGFM_AR_SMOOTHING_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace SGFM {

	/*
	 * AreaReqSmoothing - Area requirement smoothing
	 */
	class AreaReqSmoothing {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double coSmoothing=0.15, // AR smoothing coefficient.
					double tControl=2.0, // control interval [s]
					double dt=0.1, // simulation interval time [s]
					double elapsedTime=0.0, // init elapsed time.
					double initAR=0.0 // init pre-smoothing AR input.
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameter is written in each line.
			 * 1: coSmoothing
			 * 2: tControl [s]
			 * 3: dt [s]
			 * 4: initAR [p.u.]
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
			 * set current input.
			 */
			void set(
					double AR // power [p.u.].
					);

			/*
			 * get AR.
			 * power [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mCoSmoothing;
			double mtControl;
			double mdt;

			/* model internal parameter */
			double mElapsedTime;
			double mOutput;
	};
}
#endif
