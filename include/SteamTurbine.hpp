// Component to model steam turbine for thermal power plant.
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

#ifndef SGFM_STEAM_TURBINE_HPP
#define SGFM_STEAM_TURBINE_HPP

#include <FirstOrderLPF.hpp>

namespace SGFM {

	/*
	 * SteamTurbine - Steam turbine model for thermal power plant.
	 */
	class SteamTurbine {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double tall=0.25, // All turbin delay [s]
					double tlow=9.0, // low pressure turbine delay [s]
					double ratehp=0.3, // high pressure turbine output ratio
					double dt=0.1, // simulation interval time [s]
					double initAllInput=0.0, // initial all turbine delay input
					double initAllOutput=0.0, // initial all turbine delay output
					double initLowInput=0.0, // initial low turbine delay input
					double initLowOutput=0.0 // initial low turbine delay output
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line
			 * 1: filename in which parameters for FirstOrderLPF mAllDelay is
			 * 2: filename in which parameters for FirstOrderLPF mLowDelay is
			 * 3: mRatedHP
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
			 * set input steam pressure [p.u.].
			 */
			void set(double steamPressure);

			/*
			 * get turbin output [p.u.].
			 */
			double get()const;

		private:
			/* model parameter */
			double mRateHP;

			/* model block */
			FirstOrderLPF mAllDelay;
			FirstOrderLPF mLowDelay;

			/* for output */
			double mOutput;

	};
}
#endif
