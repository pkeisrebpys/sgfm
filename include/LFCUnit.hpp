// LFC calculation Unit.
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

#ifndef SGFM_LFC_UNIT_HPP
#define SGFM_LFC_UNIT_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <AreaReq.hpp>
#include <AreaReqSmoothing.hpp>
#include <DeadBand.hpp>
#include <AreaReqPI.hpp>
#include <LFCCommands.hpp>
namespace SGFM {

	/*
	 * LFCUnit - Area LFC model.
	 */
	class LFCUnit {
		public:

			/*
			 * initialize with default value
			 */
			void init(int nLFC=2, int LFCmode=1);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: filename in which parameters for AreaReq is.
			 * 2: filename in which parameters for AreaReqSmoothing is.
			 * 3: filename in which parameters for DeadBand is.
			 * 4: filename in which parameters for AreaReqPI is.
			 * 5: filename in which parameters for LFCData is.
			 * 6: mLFCmode
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
					double gridCapLocal, // local grid capacity [p.u.].
					double gridCapOther, // other grid capacity [p.u.].
					double tieLinePower // from local to other [p.u.].
					);

			/*
			 * get LFC signal
			 * LFC reference power [p.u.].
			 * index: Generator index
			 */
			double get(int index)const;

			/*
			 * number of generators for LFC and EDC.
			 */
			int size()const;

			static const int modeFFC = 0;
			static const int modeTBC = 1;
		private:
			int mLFCMode;
			AreaReq mAreaReq;
			AreaReqSmoothing mAreaReqSmoothing;
			DeadBand mDeadBand;
			AreaReqPI mAreaReqPI;
			LFCCommands mLFCCommands;

	};
}
#endif
