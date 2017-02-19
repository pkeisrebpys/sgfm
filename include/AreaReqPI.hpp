// Component to model AR PI control.
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

#ifndef SGFM_AREA_REQ_PI_HPP
#define SGFM_AREA_REQ_PI_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <PIController.hpp>
namespace SGFM {

	/*
	 * AreaReqPI - Area requirement PI control. 
	 */
	class AreaReqPI {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double kp=1.0, // P gain.
					double ki=0.003, // I gain.
					double dt=0.1, // simulation interval time [s]
					double ts=2.0, // control interval [s]
					double initElapsed=0.0, // initial elapsed time from last calculation.
					double initSum=0.0 // initial PI error sum.
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameter is written in each line.
			 * 1: filename in which parameters for PIController is.
			 * 2: dt [s]
			 * 3: elapsed time [s]
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
			 * power [p.u.].
			 */
			void set(double AR);

			/*
			 * get AR.
			 * power [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mdt;
			double mElapsedT;

			/* model internal block */
			PIController mPIController;

	};
}
#endif
