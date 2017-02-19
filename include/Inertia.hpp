// Component to model grid inertia.
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

#ifndef SGFM_INERTIA_HPP
#define SGFM_INERTIA_HPP

#include <FirstOrderFilter.hpp>

namespace SGFM {

	/*
	 * Inertia - Grid inertia model.
	 * This component simulates grid inertia model described as
	 * $\delta f [p.u.] = (S_B/(P_{syn}*K_L)) / (1 + (M/(P_{syn}*K_L)s)) * \delta P [p.u.]$.
	 * delta f [p.u.] is frequency fluctuation, devided by base frequency f_0 = 50 or 60 Hz.
	 * delta P [p.u.] is load fluctuation, devided by base capacity sb.
	 * S_B [MVA] is grid base capacity.
	 * P_{syn} [MVA] is grid current load.
	 * K_L [%MW/%Hz] is load frequency characteristic.
	 * M [MW*s] is generator's inertia.
	 */
	class Inertia : public FirstOrderFilter {
		public:

			/*
			 * initialize component.
			 */
			void init(
					double sb=1.0, // grid base capacity [MVA]
					double psyn=4.0, // grid synchronous generator capacity [MW]
					double kl=2.0, // load frequency characterristic [%MW/%Hz]
					double m=4.0, // generator inertia [MW*s]
					double dt=0.1, // simulation interval time [s]
					double initPower=0.0, // initial power deviation input
					double initFreq=0.0 // initial frequency deviation output
					);


	};
}
#endif
