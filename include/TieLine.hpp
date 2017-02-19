// Tie line model.
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

#ifndef SGFM_TIE_LINE_HPP
#define SGFM_TIE_LINE_HPP

namespace SGFM {

	/*
	 * TieLine - Tie line model.
	 */
	class TieLine {
		public:

			/*
			 * initialize with default value
			 */
			void init();

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
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
			 * set frequency deviation.
			 */
			void set(
					double srcAreaFreqDev, // delta f [p.u.] of local area.
					double dstAreaFreqDev // delta f [p.u.] of destination area.
					);

			/*
			 * get tie line power from srcArea to dstArea. [p.u.].
			 */
			double get()const;

			/*
			 * log model state on stdout with tab separated format.
			 * 1: TieLinePower
			 */
			void log(int mode=0)const;

		private:
			/* for output */
			double mTieLinePower;

	};
}
#endif
