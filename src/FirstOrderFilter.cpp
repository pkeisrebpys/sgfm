// Component to model first order filter.
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
#include <FirstOrderFilter.hpp>
namespace SGFM {

	void FirstOrderFilter::init(
			double a, double b, double c, double d,
			double dt, double initInput, double initOutput)
	{
		ma = a;
		mb = b;
		mc = c;
		md = d;
		mdt = dt;
		mx1 = initInput;
		mOutput = my1 = initOutput;
	}

	int FirstOrderFilter::read(const char *filename) {
		try {
			std::ifstream fin(filename);
			double buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			ma = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mb = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mc = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			md = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mdt = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mx1 = buf;
			if(!(fin >> buf))	{
				PRINT_PASS("f>>b");
				return EXIT_FAILURE;
			}
			mOutput = my1 = buf;
		} catch (std::exception &e) {
			PRINT_PASS("exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int FirstOrderFilter::write(const char *filename)const {
		try {
			std::ofstream fout(filename);

			fout << std::scientific;
			fout << std::showpos;
			fout << std::setprecision(9);

			fout << ma << std::endl;
			fout << mb << std::endl;
			fout << mc << std::endl;
			fout << md << std::endl;
			fout << mdt << std::endl;
			fout << mx1 << std::endl;
			fout << my1 << std::endl;
		} catch (std::exception &e) {
			PRINT_PASS("exception");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	
	void FirstOrderFilter::set(double input) {
		mOutput = ((2.0*ma - mb*mdt)*my1 + (2.0*mc + md*mdt)*input + (md*mdt - 2.0*mc)*mx1)/(2.0*ma + mb*mdt);
		my1 = mOutput;
		mx1 = input;
	}

	double FirstOrderFilter::get()const {
		return mOutput;
	}

	void FirstOrderFilter::log(int mode)const {
		if (mode == 0) {
			std::cout << '\t' << my1;
		} else {
			std::cout << '\t' << "y1       ";
		}
	}

	double FirstOrderFilter::a()const {
		return ma;
	}
	double FirstOrderFilter::dt()const {
		return mdt;
	}
	double FirstOrderFilter::x1()const {
		return mx1;
	}
	double FirstOrderFilter::y1()const {
		return my1;
	}
}
