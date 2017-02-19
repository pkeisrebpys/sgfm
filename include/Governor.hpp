// Component to model governor for thermal power plant.
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

#ifndef SGFM_GOVERNOR_HPP
#define SGFM_GOVERNOR_HPP

#include <FirstOrderLPF.hpp>

namespace SGFM {

	/*
	 * Governor - Governor.
	 */
	class Governor {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double speedRegulation=25.0, // P/f[generator p.u./p.u.]
					double tGovernor=0.2, // Governor delay time constant [s]
					double dt=0.1, // simulation interval time [s]
					double initDelayInput=0.0, // initial Governor delay input.
					double initDelayOutput=0.0 // initial Governor delay output
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are written in each line.
			 * 1: filename in which parameters for FirstOrderLPF mDelay is.
			 * 3: speedRegulation
			 */
			int read(const char *filegov);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * set input.
			 * freqDeviation [p.u.]
			 * loadConf [p.u.]
			 * loadLimit [p.u.]
			 */
			void set(double freqDeviation, double loadConf, double loadLimit);

			/*
			 * get governor output [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mSpeedRegulation;

			/* model block */
			FirstOrderLPF mDelay;

			/* for output */
			double mOutput;

	};
}
#endif
