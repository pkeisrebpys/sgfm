// Component to model first order high pass filter.
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

#include <PrintPass.hpp>
#include <FirstOrderHPF.hpp>
namespace SGFM {

	void FirstOrderHPF::init(double tau,
			double dt,
			double initInput, double initOutput) {
		FirstOrderFilter::init(tau,1.0,tau,0.0,dt,initInput,initOutput);

	}

	int FirstOrderHPF::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf))	{
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			double tau = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			double dt = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			double x1 = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("");
				return EXIT_FAILURE;
			}
			double y1 = buf;

			init(tau,dt,x1,y1);
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int FirstOrderHPF::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << a() << std::endl;
			fout << dt() << std::endl;
			fout << x1() << std::endl;
			fout << y1() << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
}
