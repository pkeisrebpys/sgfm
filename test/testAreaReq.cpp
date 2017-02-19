// Test of area requirement calculation unit.
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
#include <AreaReq.hpp>

#define MAX_NCYCLE 1000
#define GRID_CAP_LOCAL 2000.0
#define GRID_CAP_OTHER 0.0
#define TIE_LINE_POWER 0.0
int main(int argc, char **argv) {
	SGFM::AreaReq target;
	char *fout = *(argv+1);
	if (argc == 2) {
		target.init();
	} else if (argc == 3) {
		fout = *(argv+2);
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read");
			return EXIT_FAILURE;
		}
		for (int i=0; i < MAX_NCYCLE; i++) {
			double input = 0.02*(double)(2*i-MAX_NCYCLE)/(double)MAX_NCYCLE;
			target.set(input,GRID_CAP_LOCAL,GRID_CAP_OTHER,TIE_LINE_POWER);;
			double output = target.get();
			fprintf(stdout,"%lf\t%lf\n",input,output);
		}
		for (int i=0; i < MAX_NCYCLE; i++) {
			double input = 0.02*(double)(MAX_NCYCLE-2*i)/(double)MAX_NCYCLE;
			target.set(input,GRID_CAP_LOCAL,GRID_CAP_OTHER,TIE_LINE_POWER);;
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
