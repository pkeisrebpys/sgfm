// Test of data bus
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

#define MAX_TIME 3600
#define FREQ 0.01
#define N_SEC 10
#define N_DATA 2
int main(int argc, char **argv) {
	SGFM::DataBus<double> target;
	char *fout = *(argv+1);
	if (argc == 2) {
		target.init();
	} else if (argc == 3) {
		fout = *(argv+2);
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read");
			return EXIT_FAILURE;
		}
		for (int i=0; i < N_SEC*MAX_TIME; i++) {
			double t_s = (double)i / (double)N_SEC;
			double input = sin(2.0*M_PI*t_s*FREQ);
			target.set(0,input);
			target.set(1,target.get(0));
			fprintf(stdout,"%lf",t_s);
			for (int j=0; j < N_DATA; j++) {
				double output = target.get(j);
				fprintf(stdout,"\t%lf",output);
			}
			fprintf(stdout,"\n");
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
