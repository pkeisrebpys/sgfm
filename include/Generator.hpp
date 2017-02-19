// Component to model geneerator.
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

#ifndef SGFM_GENERATOR_HPP
#define SGFM_GENERATOR_HPP

namespace SGFM {

	/*
	 * Generator - power plant model for grid frequency simulation.
	 */
	class Generator {
		public:
			virtual ~Generator() {}

			/*
			 * initialize with default value
			 */
			virtual void init(double capacity) = 0;

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line.
			 */
			virtual int read(const char *filename) = 0;

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			virtual int write(const char *filename)const = 0;

			/*
			 * set input.
			 */
			virtual void set(
					double freqDeviation, // delta f [p.u.].
					double refOutput // power reference [grid p.u.]
					) = 0;

			/*
			 * Get output power [grid p.u.].
			 */
			double get()const;

			virtual void log(int mode=0)const = 0;

			virtual std::string name()const = 0;

		protected:
			/* model parameter */
			double mCapacity; // [grid p.u.]

			/* internal parameters */
			double mOutput; // [generator p.u.]

		private:
	};
}
#endif
