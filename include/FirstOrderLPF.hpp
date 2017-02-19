// Component to model first order low pass filter.
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

#ifndef SGFM_FIRST_ORDER_LPF_HPP
#define SGFM_FIRST_ORDER_LPF_HPP

#include <FirstOrderFilter.hpp>

namespace SGFM {

	/*
	 * FirstOrderLPF - First order low pass filter.
	 * This component simulates filter described as 1/(1+sT).
	 */
	class FirstOrderLPF : public FirstOrderFilter {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double tau=10.0, // time constant [s]
					double dt=0.1, // simulation interval time [s].
					double initInput=0.0, // initial input.
					double initOutput=0.0 // initial output
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: tau [s]
			 * 2: dt [s]
			 * 3: initial input
			 * 4: initial output
			 */
			int read(const char *filename);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;


	};
}
#endif
