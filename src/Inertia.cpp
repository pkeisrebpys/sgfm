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

#include <Inertia.hpp>
#include <PrintPass.hpp>

namespace SGFM {

	void Inertia::init(double sb, double psyn, double kl, double m,
			double dt, double initPower, double initFreq) {
		FirstOrderFilter::init(m/(psyn*kl),1.0,0.0,sb/(psyn*kl),dt,initPower,initFreq);

	}
}
