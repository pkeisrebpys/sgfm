// Group of same type generators
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

#ifndef SGFM_GENERATOR_UNITS_HPP
#define SGFM_GENERATOR_UNITS_HPP

#include <DataBus.hpp>
#include <Generator.hpp>
#include <Thermal.hpp>
namespace SGFM {

	/*
	 * GeneratorUnit - Group of same type generators.
	 */
	class GeneratorUnit {
		public:
			/*
			 * initialize with default value.
			 * Default generators are Thermal.
			 * size: number of LFC and EDC generators.
			 */
			void init(int size=2);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each generator is stored is written one by one.
			 * Number of generators is counted by number of lines in the file.
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
			 */
			void set(
					double freqDeviation, // delta f [p.u.].
					const DataBus<double>& lfc,
					const DataBus<double>& edc
					);

			/*
			 * get sum of generator output power [p.u.].
			 */
			double get()const;

			/*
			 * log model state on stdout with tab separated format
			 */
			void log(int mode=0)const;

			/*
			 * get number of units
			 */
			int size()const;

		private:
			/* generators */
			int mSize; // number of generators.
			Generator **mUnit; // generator instances.

			/* for output */
			double mOutput; // sum of output power.

	};
}
#endif
