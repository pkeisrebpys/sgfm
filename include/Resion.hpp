// Resion model.
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

#ifndef SGFM_RESION_HPP
#define SGFM_RESION_HPP

#include <TieLine.hpp>
#include <Area.hpp>

namespace SGFM {

	/*
	 * Resion - Grid model which includes 2 Areas and a tie line.
	 */
	class Resion {
		public:

			/*
			 * Initialize with default value.
			 */
			void init(int nEDC=2, int nBase=1, int nLoad=1);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: TieLine
			 * 2: Area
			 * 3: Area
			 */
			int read(const char *filename);

			/*
			 * Write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * Set input.
			 * Just proceed simulation step.
			 */
			void set();

			/*
			 * Get area frequency deviation.
			 */
			double get()const;

			/*
			 * Logging system state on stdout with tab separated format.
			 * When the mode == 0,
			 * print result of that simulation cycle.
			 * When the mode != 0,
			 * print the data header line.
			 */
			void log(int mode=0)const;

			/*
			 * Get available simulation cycle.
			 */
			int cycle()const;

		private:
			/* control block */
			TieLine mTieLine;
			Area mAreaLocal;
			Area mAreaOther;

	};
}
#endif
