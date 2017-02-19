// Component to model AR.
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

#ifndef SGFM_AR_HPP
#define SGFM_AR_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace SGFM {

	/*
	 * AreaReqFFC - Area requirement model for FFC.
	 */
	class AreaReq {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double gridConst=5.0 // grid constant [%MW/%Hz]
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameter is written in each line.
			 * 1:gridConst. [%MW/%Hz]
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
					double freqDeviation, // delta f [p.u.].
					double gridCapLocal, // local grid capacity [p.u.]
					double gridCapOther, // other grid capacity [p.u.]
					double tieLinePower // from local to other [p.u.].
					); 

			/*
			 * get AR.
			 * power [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mGridConst;

			/* for output */
			double mOutput;
	};
}
#endif
