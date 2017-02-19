// Component to model PI controller with anti-windup control.
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

#ifndef SGFM_PI_CONTROLLER_ANTI_WINDUP_HPP
#define SGFM_PI_CONTROLLER_ANTI_WINDUP_HPP

#include <PIController.hpp>
#include <Limitter.hpp>

namespace SGFM {

	/*
	 * PIController - PI controller model.
	 * This component simulates PI controller.
	 *    ------ 1/K_a ----<---------
	 *    |              +^-        |
	 *    v-              |         |
	 * x---->    K_a   ------>limit--->y
	 *   |              +|+
	 *   -->1/T_a\int_si--
	 * x: input error.
	 * y: output control value.
	 * K_a: P gain.
	 * T_a: time constant [s].
	 */
	class PIControllerAntiWindup : public PIController {
		public:
			/*
			 * Initialize component.
			 */
			void init(
					double ka=0.5, // P gain
					double ta=30.0, // integrator time constant [s]
					double dt=0.1, // simulation interval time [s]
					double initErrorSum=0.0, // initial integrator sum
					double upper=1.20, // output upper limit
					double lower=0.00, // output lower limit
					double initAntiWindupFB=0.0 // initial anti-windup feedback value
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 * 1: filename in which parameters for PIController is.
			 * 2: filename in which parameters for Limitter is.
			 * 3: AntiWindupFB
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

		private:
			/* controller internal block */
			Limitter outputLimitter;
			/* controller internal parameters */
			double mAntiWindupFB;
	};
}
#endif
