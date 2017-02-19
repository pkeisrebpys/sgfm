// Area model.
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

#ifndef SGFM_AREA_HPP
#define SGFM_AREA_HPP

#include <PrintPass.hpp>
#include <DataBus.hpp>
#include <AreaGrid.hpp>
#include <AreaControl.hpp>
namespace SGFM {

	/*
	 * Area - Area model.
	 */
	class Area {
		public:

			/*
			 * initialize with default value
			 */
			void init(int nEDC=2, int nBase=1, int nLoad=1, double gridCap=4.0);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: LFCBus
			 * 2: EDCBus
			 * 3: AreaGrid
			 * 4: AreaControl
			 * 5: mGridCap
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
					double gridCapOther, // other grid capacity [p.u.].
					double tieLinePower // from local to other [p.u].
					);

			/*
			 * get area frequency deviation [p.u.].
			 */
			double get()const;

			/*
			 * log model state on stdout with tab separated format.
			 * 1: LFCBus
			 * 2: EDCBus
			 * 3: AreaGrid
			 * 4: AreaControl
			 */
			void log(int mode=0)const;

			/*
			 * Get simulation cycle.
			 */
			int cycle()const;

			/*
			 * get grid capacity [p.u.].
			 */
			double gridCap()const;

		private:
			/* model parameter */
			double mGridCap;

			/* control block */
			DataBus<double> mLFCBus; // transfer LFC signal [p.u.].
			DataBus<double> mEDCBus; // transfer EDC signal [p.u.].

			AreaGrid mAreaGrid;
			AreaControl mAreaControl;

	};
}
#endif
