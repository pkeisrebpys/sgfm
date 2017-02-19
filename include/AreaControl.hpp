// Area control model.
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

#ifndef SGFM_AREA_CONTROL_HPP
#define SGFM_AREA_CONTROL_HPP

#include <PrintPass.hpp>
#include <LFCUnit.hpp>
#include <EDCUnit.hpp>
namespace SGFM {

	/*
	 * AreaControl - Area control (LFC and EDC) model.
	 */
	class AreaControl {
		public:

			/*
			 * initialize with default value
			 */
			void init(
					int nEDC=2 // Number of EDC/LFC generator.
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: LFCUnit
			 * 2: EDCUnit
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
					double tieLinePower // power from local to other [p.u.].
					);

			/*
			 * get LFC signal.
			 * LFC power reference [p.u.].
			 * index: generator index.
			 */
			double LFCsignal(int index)const;

			/*
			 * get EDC signal.
			 * EDC power reference [p.u.].
			 * index: generator index.
			 */
			double EDCsignal(int index)const;

			/*
			 * log model state on stdout with tab separated format.
			 */
			void log(int mode=0)const;


			/*
			 * get simulation cycle.
			 */
			int cycle()const;

			/*
			 * number of LDC and EDC generators.
			 */
			int numGen()const;
		private:
			LFCUnit mLFCUnit;
			EDCUnit mEDCUnit;

	};
}
#endif
