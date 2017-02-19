// Component to model dead band.
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

#ifndef SGFM_DEAD_BAND_HPP
#define SGFM_DEAD_BAND_HPP

namespace SGFM {

	/*
	 * DeadBand - DeadBand model.
	 */
	class DeadBand {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double bandUpper=10.0, // Upper band width.
					double bandLower=-10.0 // Lower band width.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameter is written in each line.
			 * 1:upper band width.
			 * 2:lower band width.
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

		private:
			/* Model parameter */
			double mUpper;
			double mLower;

			/* For output*/
			double mOutput;
	};
}
#endif
