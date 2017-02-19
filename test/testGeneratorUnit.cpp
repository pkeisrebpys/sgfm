// Test of file generator units.
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

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <PrintPass.hpp>
#include <DataBus.hpp>
#include <GeneratorUnit.hpp>

#define T_FIN 3700.0
#define T_INTERVAL 0.1
#define FREQ 0.001

int main(int argc, char **argv) {
	SGFM::GeneratorUnit target;
	SGFM::DataBus<double> lfc;
	SGFM::DataBus<double> edc;
	char *fout = *(argv+1);
	if (argc == 2) {
		target.init();
	} else if (argc == 3) {
		fout = *(argv+2);
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read error");
			return EXIT_FAILURE;
		}
		lfc.init();
		edc.init();
		PRINT_PASS("start test");
		double elapsedTime = 0.0;
		while (elapsedTime < T_FIN) {
			elapsedTime += T_INTERVAL;
			double freqdev = 0.01*sin(2.0*M_PI*elapsedTime*FREQ);
			double lfcsignal = 100.0*sin(2.0*M_PI*elapsedTime*FREQ);
			double edcsignal = 1500.0;
			PRINT_PASS("start test");
			lfc.set(0,lfcsignal);
			PRINT_PASS("data set");
			lfc.set(1,lfcsignal);
			PRINT_PASS("data set");
			edc.set(0,edcsignal);
			PRINT_PASS("data set");
			edc.set(1,edcsignal);
			PRINT_PASS("data set");
			target.set(freqdev,lfc,edc);
			PRINT_PASS("data input");
			fprintf(stdout,"%lf\t",elapsedTime);
			double output = target.get();
			fprintf(stdout,"%lf\n",output);
		}
	} else {
		PRINT_PASS("read");
		return EXIT_FAILURE;
	}

	if (target.write(fout) != EXIT_SUCCESS) {
		PRINT_PASS("write");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
