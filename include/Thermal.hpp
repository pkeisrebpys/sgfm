// Component to model thermal power plant for grid frequency simulation.
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

#ifndef SGFM_THERMAL_HPP
#define SGFM_THERMAL_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <Generator.hpp>

#include <FreqBias.hpp>
#include <ChangeRateLimitter.hpp>
#include <Limitter.hpp>
#include <SteamBoiler.hpp>
#include <PIControllerAntiWindup.hpp>
#include <Governor.hpp>
#include <AutoLoadLimitter.hpp>
#include <ControlValve.hpp>
#include <SteamTurbine.hpp>

namespace SGFM {

	/*
	 * Thermal - Thermal power plant model for grid frequency simulation.
	 */
	class Thermal : public Generator {
		public:

			/*
			 * initialize with default value
			 */
			void init(double capacity);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line.
			 * 1: filename in which parameters for FreqBias mFreqBias is
			 * 2: filename in which parameters for ChangeRateLimitter mRefChangeLimitter is.
			 * 3: filename in which parameters for Limitter mRefLimitter is.
			 * 4: filename in which parameters for SteamBoiler mSteamBoiler is.
			 * 5: filename in which parameters for PIControllerAntiWindup mLoadRefPI is.
			 * 6: filename in which parameters for Governor mGovernor is.
			 * 7: filename in which parameters for AutoLoadLimitter mAutoLoadLimitter is.
			 * 8: filename in which parameters for ControlValve mControlValve is.
			 * 9: filename in which parameters for SteamTurbine mSteamTurbine is.
			 * 10: mCapacity [grid p.u.]
			 * 11: mOutput.
			 * 12: mSteamFlow.
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
			 */
			void set(
					double freqDeviation, // delta f [p.u.].
					double refOutput // power reference [grid p.u.].
					);

			std::string name()const;

			void log(int mode=0)const;

		private:
			/* control blocks */
			FreqBias mFreqBias;
			ChangeRateLimitter mRefChangeLimitter;
			Limitter mRefLimitter;
			SteamBoiler mSteamBoiler;
			PIControllerAntiWindup mLoadRefPI;
			Governor mGovernor;
			AutoLoadLimitter mAutoLoadLimitter;
			ControlValve mControlValve;
			SteamTurbine mSteamTurbine;

			/* internal parameters */
			double mSteamFlow;

	};
}
#endif
