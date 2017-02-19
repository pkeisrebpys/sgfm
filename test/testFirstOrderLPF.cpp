// Test of first order filter.
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

#define PRINT_PASS(ARGS) fprintf(stderr,"%s,%d:%s\n",__FILE__,__LINE__,ARGS)
#include <cstdio>
#include <cstdlib>
#include <FirstOrderLPF.hpp>
#define MAX_NCYCLE 1000
int main(int argc, char **argv) {
	SGFM::FirstOrderLPF target;
	char *fout = *(argv+1);
	if (argc == 2) {
		PRINT_PASS("init parameters");
		target.init();
	} else if (argc == 3) {
		PRINT_PASS("read parameters");
		fout = *(argv+2);
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read");
			return EXIT_FAILURE;
		}

		for (int i=0; i < MAX_NCYCLE; i++) {
			double input = 1.0;
			target.set(1.0);
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
