// grid frequency model sample.
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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

#include <sgfm.hpp>

/*
 * Usage:
 * ./main init nEDC nBase nLoad <initfile>
 *		Generate initial condition files named as <initfile>*.
 *		Before start simulation, modify <initfile>*
 *		to change simulation conditions.
 *
 * ./main mod [EDC|BASE|LOAD] <num> <initfile>
 *		Generate load or generation power data for <initfile>*.
 *
 * ./main run <initfile> <outfile>
 *		Start simulation with initial conditions described in <initfile>*.
 *		Conditions at the end of simulation is stored in <outfile>*.
 *		Simulation results are printed on stdout.
 *
 * ./main run <outfile> <outfile2>
 *		Continue simulation with conditions when the <outfile>* were generated.
 *		Conditions at the end of simulation is stored in <outfile2>*.
 *		Simulation results are printed on stdout.
 */
#define N_DATA 3600
int main(int argc, char **argv) {
	std::string simMode;
	if (argc >= 2) {
		simMode = *(argv+1);
	} else {
		PRINT_PASS("invalid arguments");
		return EXIT_FAILURE;
	}
	std::string initMode = "init";
	std::string runMode = "run";
	std::string modMode = "mod";
	if (simMode == initMode) {
		if (argc < 6) {
			PRINT_PASS("invalid arguments");
			return EXIT_FAILURE;
		}
		SGFM::Resion target;
		target.init(atoi(*(argv+2)),atoi(*(argv+3)),atoi(*(argv+4)));
		if (target.write(*(argv+5)) != EXIT_SUCCESS) {
			PRINT_PASS("file write error.");
			return EXIT_FAILURE;
		}
	} else if (simMode == modMode) {
		if (argc < 5) {
			return EXIT_FAILURE;
		}
		std::string unit = *(argv+2);
		std::string EDCUnit = "EDC";
		std::string BASEUnit = "BASE";
		std::string LOADUnit = "LOAD";
		std::string pre = *(argv+4);
		if (unit == EDCUnit) {
			pre += "_lo_ct_edc_dt_";
			pre += *(argv+3);
			pre += "_dt";
			try {
				std::ofstream fout(pre.c_str());
				double input = 1.5;
				for (int i = 0; i < N_DATA; i++) {
					fout << input << std::endl;
				}
			} catch (std::exception &e) {
				return EXIT_FAILURE;
			}
		} else if (unit == BASEUnit) {
			pre += "_lo_gr_bu_";
			pre += *(argv+3);
			pre += "_dt";
			try {
				std::ofstream fout(pre.c_str());
				double input = 0.0;
				for (int i = 0; i < N_DATA; i++) {
					fout << input << std::endl;
				}
			} catch (std::exception &e) {
				return EXIT_FAILURE;
			}
		} else if (unit == LOADUnit) {
			pre += "_lo_gr_lu_";
			pre += *(argv+3);
			pre += "_dt";
			try {
				std::ofstream fout(pre.c_str());
				double input = 3.0;
				for (int i = 0; i < N_DATA; i++) {
					double output = input + 0.3 *sin(2.0*M_PI*(double)i/(double)N_DATA);
					fout << output << std::endl;
				}
			} catch (std::exception &e) {
				return EXIT_FAILURE;
			}
		}
	} else if (simMode == runMode) {
		if (argc < 4) {
			PRINT_PASS("invalid arguments");
			return EXIT_FAILURE;
		}
		SGFM::Resion target;
		if (target.read(*(argv+2)) != EXIT_SUCCESS) {
			PRINT_PASS("file read error");
			return EXIT_FAILURE;
		}
		std::cout << "#time    ";
		target.log(-1);
		std::cout << std::endl;
		std::cout << std::scientific;
		std::cout << std::showpos;
		std::cout << std::setprecision(3);

		int nCycle = target.cycle();
		for (int i=0; i < nCycle; i++) {
			target.set();
			std::cout << (double)i;
			target.log();
			std::cout << std::endl;
		}
		if (target.write(*(argv+3)) != EXIT_SUCCESS) {
			PRINT_PASS("file write error.");
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
	std::cerr << "OK" << std::endl;
	return EXIT_SUCCESS;
}
