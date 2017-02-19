// Group of file readers.
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

#ifndef SGFM_FILE_READER_UNIT_HPP
#define SGFM_FILE_READER_UNIT_HPP

#include <PrintPass.hpp>
#include <FileReader.hpp>
namespace SGFM {

	/*
	 * FileReaderUnit - Group of FileReader.
	 */
	class FileReaderUnit {
		public:

			/*
			 * initialize with default value.
			 * nData: number of files initialized.
			 */
			void init(int nData=1);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each FileReader is stored.
			 * Number of FileReaders is counted
			 * by number of lines in the file.
			 * At least 1 filename is required.
			 */
			int read(const char *filename);

			/*
			 * write config to file
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * Be care, When this method is called,
			 * allocated array for Thermal parameters are deleted.
			 */
			int write(const char *filename)const;

			/*
			 * set input.
			 * Just proceed reading data by one step.
			 */
			void set();

			/*
			 * get sum of load power
			 * P [p.u.].
			 * load consumption is positive 
			 * when the data is for load and renewable.
			 * generation is positive
			 * when the data is for generator or EDC signal.
			 */
			double get()const;

			/*
			 * get load power of index-th load.
			 * P [p.u.].
			 * load consumption is positive.
			 */
			double get(int index)const;

			/*
			 * log model state on stdout with tab separated format.
			 * 1: mData
			 */
			void log(int mode=0)const;

			/*
			 * get number of data.
			 */
			int size()const;

			/*
			 * get simulation cycle.
			 */
			int cycle()const;

		private:
			/* generators data */
			FileReader *mData;

			/* internal parameter */
			int mSize;

			/* for output */
			double mOutput; // sum of output power.
	};
}
#endif
