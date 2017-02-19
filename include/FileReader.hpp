// Component to read load or generation power data.
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

#ifndef SGFM_FILE_READER_HPP
#define SGFM_FILE_READER_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

namespace SGFM {

	/*
	 * FileReader - read load or generation power data from file.
	 */
	class FileReader {
		public:

			/*
			 * Initialize datafile with 0.
			 */
			void init(
					int nData=3600, // Number of data in the file.
					double tSample=1.0, // Data sampling interval time [s].
					double dt=0.1, // Simulation interval time [s].
					int position=0, // Initial data index in the file.
					double elapsedTime=0.0 // Initial slapsed time [s].
					);

			/*
			 * Read config file and initialize component.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, parameters are stored in each line.
			 * 1: filename in which ts sec step load or power data is.
			 * 2: mPosition
			 * 3: dt simulation interval time [s].
			 * 4: ts data sampling interval time [s].
			 * 5: mElapsedTime [s]
			 *
			 * Data in the file data is stored in line 1 is power [grid p.u.].
			 * Generation is positive
			 * when the data is for base load generator.
			 * Sonsumption is positive
			 * when the data is for load and renewable.
			 */
			int read(const char *filename);

			/*
			 * Write config to file.
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 */
			int write(const char *filename)const;

			/*
			 * Set input.
			 * Just proceed one simulation step.
			 */
			void set();

			/*
			 * Get current power [p.u.].
			 * When the file stores base load generator data,
			 * generation is positive.
			 * When the file stores load or renewable data,
			 * consumption is positive.
			 */
			double get()const;

			/*
			 * Get number of data.
			 */
			int size()const;

			/*
			 * Get number of simulation cycle.
			 */
			int cycle()const;

		private:
			/* Model parameters */
			double mts; // Data sampling interval time.

			/* Simulation parameters */
			double mdt; // Simulation interval time.

			/* For internal parameters */
			unsigned int mPosition;
			double mElapsedTime;
			std::vector<double> mData;

			std::string mDataFileName;


	};
}
#endif
