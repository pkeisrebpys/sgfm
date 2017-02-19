// Component to model Integrator.
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

#ifndef SGFM_INTEGRATOR_HPP
#define SGFM_INTEGRATOR_HPP

namespace SGFM {

	/*
	 * Integrator - Integrator model described as 1/s.
	 */
	class Integrator {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double dt=0.1, // Simulation interval time [s].
					double initSum=0.0 // Initial integrator sum.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line.
			 * 1: dt
			 * 2: initisum
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

		protected:
			/*
			 * Reset integrator sum.
			 */
			void setOutput(double input);

		private:
			/*
			 * Simulation parameter.
			 */
			double mdt;

			/*
			 * Internal parameter
			 */
			double mOutput;

	};
}
#endif
