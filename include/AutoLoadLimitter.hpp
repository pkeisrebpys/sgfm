// Component to model automatic load limitter for thermal power plant.
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

#ifndef SGFM_AUTO_LOAD_LIMITTER_HPP
#define SGFM_AUTO_LOAD_LIMITTER_HPP

#include <Limitter.hpp>
#include <IntegratorLimited.hpp>

namespace SGFM {

	/*
	 * AutoLoadLimitter - automatic load limitter.
	 */
	class AutoLoadLimitter {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double widthGF=0.05, // Governor free control width [generator p.u.]
					double upperGF=0.00083, // 0.05 / 60 [generator p.u.]
					double lowerGF=-0.00083, // 0.05 / 60 [generator p.u.]
					double upperInt=1.05, // [generator p.u.]
					double lowerInt=0.0, // [generator p.u.]
					double dt=0.1, // [s]
					double initInt=0.0 // integrators initial sum
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line
			 * 1: filename in which parameters for Limitter GFLimitter is stored.
			 * 2: filename in which parameters for IntegratorLimited IntLimitter is stored.
			 * 3: GF width. [p.u.]
			 * 4: mOutput
			 */
			int read(const char *filename);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * set input.
			 * governorConf
			 */
			void set(double governorConf);

			/*
			 * get load minit [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mWidthGF;

			/* model block */
			Limitter mGFLimitter;
			IntegratorLimited mIntLimitter;

			/* internal parameter */
			double mOutput;

	};
}
#endif
