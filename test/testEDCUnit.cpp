// Test of EDC unit.
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
#include <EDCUnit.hpp>

#define N_SEC 10
#define MAX_TIME 3700
#define FREQ 0.1
#define T_INTERVAL 0.1

int main(int argc, char **argv) {
	SGFM::EDCUnit target;
	char *fout = *(argv+1);
	if (argc == 2) {
		target.init();
	} else if (argc == 3) {
		fout = *(argv+2);
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read");
			return EXIT_FAILURE;
		}
		double elapedTIme = 0;
		for (int i=0; i < N_SEC*MAX_TIME; i++) {
			elapedTIme += T_INTERVAL;
			target.set();
			fprintf(stdout,"%lf",elapedTIme);
			for (int j=0; j < target.size(); j++) {
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
