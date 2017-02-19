// Area grid model.
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

#ifndef SGFM_AREA_GRID_HPP
#define SGFM_AREA_GRID_HPP

#include <DataBus.hpp>
#include <Inertia.hpp>
#include <FileReaderUnit.hpp>
#include <GeneratorUnit.hpp>
namespace SGFM {

	/*
	 * AreaGrid - Area grid model.
	 */
	class AreaGrid {
		public:

			/*
			 * initialize with default value
			 */
			void init(
					int nEDC=2, // Number of EDC/LFC generator.
					int nBase=1, // Number of Base Generator.
					int nLoad=1 // Number of Loads
					);

			/*
			 * read config file and initialize component
			 *
			 * On success, returns EXIT_SUCCESS.
			 * On error, returns EXIT_FAILURE.
			 *
			 * In the input file, filename in which parameters
			 * for each grid units is stored is written one by one.
			 * 1: Inertia
			 * 2: LoadUnit
			 * 3: BaseGeneratorUnit
			 * 4: ThermalUnit
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
					double tieLinePower, // from local to other is positive [p.u.]
					const DataBus<double>& lfc, // LFC signal
					const DataBus<double>& edc // EDC signal
					);

			/*
			 * get frequency deviation of the area.
			 * delta f [p.u.].
			 */
			double get()const;

			/*
			 * log model state on stdout with tab separated format.
			 * 1: Inertia
			 * 2: LoadUnit
			 * 3: BaseUnit
			 * 4: GeneratorUnit
			 */
			void log(int mode=0)const;

			/*
			 * simulation cycle.
			 */
			int cycle()const;

			/*
			 * number of LDC and EDC generators.
			 */
			int numGen()const;

		private:
			/* Inertia */
			Inertia mInertia; // Inertia model.

			/* Loads and renewables */
			FileReaderUnit mLoadUnit; // Load units contains renewable energies.

			/* Base generators */
			FileReaderUnit mBaseUnit; // Base load generators.

			/* controllable generators */
			GeneratorUnit mGeneratorUnit;

	};
}
#endif
