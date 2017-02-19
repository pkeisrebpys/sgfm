// Component to model limitter.
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

#ifndef SGFM_LIMITTER_HPP
#define SGFM_LIMITTER_HPP

namespace SGFM {

	/*
	 * Limitter - Limitter model.
	 * This component simulates limitter.
	 */
	class Limitter {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double upper=1.0, // upper limit
					double lower=-1.0 // lower limit
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameter is written in each line.
			 * 1:upper limit.
			 * 2:lower limit.
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

			/* Model internal parameter */
			double mOutput;
	};
}
#endif
