// Component to model integrator with limit.
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

#ifndef SGFM_INTEGRATOR_LIMITED_HPP
#define SGFM_INTEGRATOR_LIMITED_HPP

#include <string>
#include <Integrator.hpp>
#include <Limitter.hpp>
namespace SGFM {

	/*
	 * IntegratorLimited - Integrator model with limit.
	 */
	class IntegratorLimited : public Integrator {
		public:

			/*
			 * Initialize component.
			 */
			void init(
					double upwer=1.0, // Limitter upper limit.
					double lower=0.0, // Limitter lower limit.
					double dt=0.1, // Simulation interval time [s].
					double initSum=0.0 // Initial integrator sum.
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * 1: filename in which parameters for Integrator is.
			 * 2: filename in which parameters for Limitter is.
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

		private:
			/* Model internal block */
			Limitter limitter;
	};
}
#endif
