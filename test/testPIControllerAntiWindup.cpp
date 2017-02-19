// Test of PI controller with anti-windup.
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
#include <PIControllerAntiWindup.hpp>

#define MAX_TIME 3600
#define FREQ 0.01
#define N_SEC 10
int main(int argc, char **argv) {
	SGFM::PIControllerAntiWindup target;
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
			double input = 0.1;
			if (i > 10000) {
				double t_s = (double)i / (double)N_SEC;
				input = 0.0+0.1*sin(2.0*M_PI*t_s*FREQ);
			}
			target.set(input);
			double output = target.get();
			fprintf(stdout,"%lf\t%lf\n",input,output);
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