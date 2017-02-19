// Component to model control valve (CV) in thermal power plant.
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

#ifndef SGFM_CONTROL_VALVE_HPP
#define SGFM_CONTROL_VALVE_HPP

#include <Limitter.hpp>
#include <IntegratorLimited.hpp>

namespace SGFM {

	/*
	 * ControlValve - Control valve for steam turbine.
	 */
	class ControlValve {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double gain=5.0, // input gain
					double gainUpper=0.2, // gained signal upper limit [generator p.u.].
					double gainLower=-1000.0, // gained signal upper limit [generator p.u.].
					double intUpper=1.05, // integrated signal upper limit [generator p.u.].
					double intLower=0.0, // integrated signal lower limit [generator p.u.].
					double dt=0.1, // simulation interval time [s].
					double initSum=0.0, // initial integrator sum.
					double initOutput=0.0 // initial system output [p.u.]
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: filename in which parameters for Limitter gainLimitter is.
			 * 2: filename in which parameters for IntergratorLimited limintedInt is.
			 * 3: gain
			 * 4: initial output.
			 */
			int read(const char *filethis);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * set input steam pressure [p.u.].
			 */
			void set(double input);

			/*
			 * get turbin output [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mGain;

			/* model block */
			Limitter gainLimitter;
			IntegratorLimited limitedInt;

			/* internal parameter */
			double mOutput;

	};
}
#endif
