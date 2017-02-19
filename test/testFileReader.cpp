// Test of file reader
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
#include <FileReader.hpp>

#define T_FIN 3700.0
#define T_INTERVAL 0.1

int main(int argc, char **argv) {
	SGFM::FileReader target;
	char *fout = *(argv+1);
	if (argc == 2) {
		PRINT_PASS("init");
		target.init();
	} else if (argc == 3) {
		fout = *(argv+2);
		PRINT_PASS("read");
		if (target.read(*(argv+1)) != EXIT_SUCCESS) {
			PRINT_PASS("read error");
			return EXIT_FAILURE;
		}
		PRINT_PASS("start test");
		double elapsedTime = 0.0;
		while (elapsedTime < T_FIN) {
			elapsedTime += T_INTERVAL;
			target.set();
			double output = target.get();
			fprintf(stdout,"%lf\t%lf\n",elapsedTime,output);
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
