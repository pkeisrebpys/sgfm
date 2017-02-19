// Component to model steam boiler for thermal power plant.
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

#ifndef SGFM_STEAM_BOILER_HPP
#define SGFM_STEAM_BOILER_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <FirstOrderLPF.hpp>
#include <MainPressureConf.hpp>

namespace SGFM {

	/*
	 * SteamBoiler - Steam boiler model for thermal power plant.
	 */
	class SteamBoiler {
		public:

			/*
			 * initialize component.
			 *
			 * tBoilSteam: Steam generation delay of Boiler [s].
			 * mainPowerUpper: power upper limit of main pressure configurator.
			 * mainPowerLower: power lower limit of main pressure configurator.
			 * mainPressureUpper: pressure upper limit of main pressure configurator.
			 * mainPressureLower: pressure lower limit of main pressure configurator.
			 * tBoiler: boiler delay time constant [s].
			 * tControl: pressure control delay time constant [s].
			 *
			 * dt: simulation interval time [s].
			 *
			 * initRefInput: initial boiler input reference MWD'.
			 * initBoidSteam: initial boiler steam generation.
			 * initSteamError: initial steam flow error.
			 * initBoilerError: initial boiler steam flow error..
			 * initControlError: initial boiler control error.
			 */
			void init(
					double tBoilSteam=120.0, // Steam generation delay [s]
					double mainPowerUpper=0.9, // main pressure controller input upper limit [generator p.u.].
					double mainPowerLower=0.3, // main pressure controller input lower limit [generator p.u.].
					double mainPressureUpper=1.0, // main pressure controller output upper limit [generator p.u.]
					double mainPressureLower=0.4, // main pressure controller output lower limit [generator p.u.]
					double tBoiler=60.0, // boiler characteristic delay [s]
					double tContorl=150.0, // pressure control delay [s]
					double dt=0.1, // simulation interval time [s]
					double initRefInput=0.0, // initial output power reference
					double initBoilSteam=0.0, // initial boiler steam output
					double initSteamError=0.0, // initial steam generation error
					double initBoilerError=0.0, // initial boiler characteristic error
					double initControlError=0.0 // initial control error
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * 1: filename in which parameters for FirstOrderLPF mDelayBoidSteam is.
			 * 2: filename in which parameters for MainPressureConf mMainPConf is.
			 * 3: filename in which parameters for FirstOrderLPF mDelayBoilError is.
			 * 4: filename in which parameters for FirstOrderLPF mDelayControl is.
			 * 5: mDeviation
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
			 * set boiler input.
			 *
			 * powerRef: output power reference.
			 * outputFlow
			 */
			void set(double powerRef, double outputFlow);

			/*
			 * get outputPressure
			 */
			double get()const;

			/*
			 * get mainPressureDeviation
			 */
			double getDeviation()const;

		private:
			/* internal blocks */
			FirstOrderLPF mDelayBoilSteam;
			MainPressureConf mMainPConf;
			FirstOrderLPF mDelayBoilError;
			FirstOrderLPF mDelayControl;

			/* internal parameter */
			double mDeviation;

			/* for output */
			double mPressure;

	};
}
#endif
