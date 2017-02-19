// Component to model PI controller.
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

#ifndef SGFM_PI_CONTROLLER_HPP
#define SGFM_PI_CONTROLLER_HPP

namespace SGFM {

	/*
	 * PIController - PI controller model.
	 * This component simulates PI controller.
	 * x--->    K_a   ------>y
	 *   |              +|+
	 *   -->1/(T_a*s)-----
	 * x: input error.
	 * y: output control value.
	 * K_a: P gain.
	 * T_a: time constant [s].
	 */
	class PIController {
		public:
			/*
			 * initialize component.
			 */
			void init(
					double ka=1.0, // P gain.
					double ta=1.0, // I integrator time constant [s].
					double dt=0.1, // Simulation interval time [s].
					double initErrorSum=0.0 // Initial integrator sum.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are sotred in each line.
			 * 1. ka
			 * 2: ta
			 * 3: dt
			 * 4: initErrorSum
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
			 * Set input error.
			 */
			void set(double error);

			/* 
			 * Get output control value.
			 */
			double get()const;

			double ka()const;
			double ta()const;
			double dt()const;
			double ErrorSum()const;

		protected:
			void setOutput(double output);

		private:
			/* Controller parameters */
			double mka;
			double mta;

			/* Simulation parameter */
			double mdt;

			/* Controller internal parameter */
			double mErrorSum;

			/* For output */
			double mOutput;
	};
}
#endif
