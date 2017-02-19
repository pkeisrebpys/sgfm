// Component to model change rate limitter.
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

#ifndef SGFM_CHANGE_RATE_LIMITTER_HPP
#define SGFM_CHANGE_RATE_LIMITTER_HPP

#include <cmath>

namespace SGFM {

	/*
	 * ChangeRateLimitter - Change rate limitter model.
	 */
	class ChangeRateLimitter {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double cr=0.0005, // Change rate [/s]
					double dt=0.1, // Simulation interval time [s]
					double initInput=0.0 // Initial input value.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: cr
			 * 2: dt
			 * 3: initInput
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
			 * Set current input.
			 */
			void set(double input);

			/*
			 * Get limitter output.
			 */
			double get()const;

			/*
			 * Get change rate border.
			 */
			double cr()const;

		private:
			/* model parameter */
			double mcr;
			double mdt;

			/* model internal parameter */
			double mOutput;
	};
}
#endif
