// LFC command data storage.
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

#ifndef SGFM_LFC_COMMAND_HPP
#define SGFM_LFC_COMMAND_HPP

#include <PrintPass.hpp>
#include <ChangeRateLimitter.hpp>

namespace SGFM {

	/*
	 * LFCCommands - Area LFC data strage.
	 */
	class LFCCommands {
		public:

			/*
			 * initialize with default value
			 */
			void init(int nLFC=2);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: file in which change rate of Thermal generators are stored.
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
			 * power [p.u.].
			 */
			void set(double AR);

			/*
			 * get LFC signal
			 * power [p.u.].
			 */
			double get(int generatorNum)const;

			int size()const;

		private:
			int mNGenerator;
			ChangeRateLimitter *mChangeRateLimitters;

	};
}
#endif
