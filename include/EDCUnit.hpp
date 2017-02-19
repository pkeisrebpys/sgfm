// EDC calculation Unit.
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

#ifndef SGFM_EDC_UNIT_HPP
#define SGFM_EDC_UNIT_HPP

#include <FileReaderUnit.hpp>
namespace SGFM {

	/*
	 * EDCUnit - Area EDC model.
	 */
	class EDCUnit {
		public:

			/*
			 * initialize with default value
			 */
			void init(int nData=2);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for EDC data reader is stored.
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
			 * nothing to input.
			 * just proceed simulation step.
			 */
			void set();

			/*
			 * get EDC signal
			 * EDC power reference [p.u.].
			 * index: generator number.
			 */
			double get(int index)const;

			void log(int mode)const;

			/*
			 * get simulation cycle.
			 */
			int cycle()const;

			/*
			 * get number of EDC generator.
			 */
			int size()const;

		private:
			FileReaderUnit mEDCData;

	};
}
#endif
