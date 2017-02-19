// SGFM - standard grid frequency model.
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

#ifndef SGFM_HPP
#define SGFM_HPP


/**************************************************************
 * BASIC BLOCK COMPONENTS
 *************************************************************/
/*
 * 2 model parameters.
 * 0 simulation parameter.
 * 0 internal parameter.
 */
#include <Limitter.hpp>

/*
 * 2 model parameters.
 * 0 simulation parameter.
 * 0 internal parameter.
 */
#include <DeadBand.hpp>

/*
 * 1 model parameters.
 * 1 simulation parameter.
 * 1+n internal parameter.
 */
#include <Delay.hpp>

/* 
 * 1 model parameter.
 * 1 simulation parameter.
 * 1 internal parameter.
 */
#include <ChangeRateLimitter.hpp>

/* 
 * 4 model parameter.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <FirstOrderFilter.hpp>
/* 
 * 1 model parameter.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <FirstOrderHPF.hpp>
#include <FirstOrderLPF.hpp>

/*
 * 0 model parameter.
 * 1 simulation parameter.
 * 1 internal parameter.
 */
#include <Integrator.hpp>
/*
 * 2 model parameter.
 * 1 simulation parameter.
 * 1 internal parameter.
 */
#include <IntegratorLimited.hpp>

/*
 * 2 model parameter.
 * 1 simulation parameter.
 * 1 internal parameter.
 */
#include <PIController.hpp>
/*
 * 4 model parameter.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <PIControllerAntiWindup.hpp>

/*
 * n model parameters.
 * n simulation parameters.
 * n internal parameter.
 */
#include <FileReader.hpp>

/**************************************************************
 * BLOCKS FOR GENERATOR MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <Generator.hpp>

/*
 * 6 model parameters.
 * 0 simulation parameter.
 * 0 internal parameter.
 */
#include <FreqBias.hpp>

/*
 * 4 model parameters.
 * 0 simulation parameter.
 * 0 internal parameter.
 */
#include <MainPressureConf.hpp>

/*
 * 7 model parameters.
 * 1 simulation parameter.
 * 5 internal parameter.
 */
#include <SteamBoiler.hpp>


/*
 * 2 model parameters.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <Governor.hpp>

/*
 * 5 model parameters.
 * 1 simulation parameter.
 * 1 internal parameter.
 */
#include <AutoLoadLimitter.hpp>

/*
 * 5 model parameters.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <ControlValve.hpp>

/*
 * 3 model parameters.
 * 1 simulation parameter.
 * 4 internal parameter.
 */
#include <SteamTurbine.hpp>

/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <Thermal.hpp>

/**************************************************************
 * BLOCKS FOR COMMUNICATION MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameters.
 * n internal parameter.
 */
#include <DataBus.hpp>

/**************************************************************
 * BLOCKS FOR AREA GRID MODEL
 *************************************************************/
/*
 * 4 model parameters.
 * 1 simulation parameter.
 * 2 internal parameter.
 */
#include <Inertia.hpp>

/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <FileReaderUnit.hpp>

/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <GeneratorUnit.hpp>

/**************************************************************
 * BLOCKS FOR LFC UNIT
 *************************************************************/
#include <AreaReq.hpp>
#include <AreaReqSmoothing.hpp>
#include <AreaReqPI.hpp>
#include <LFCCommands.hpp>

/**************************************************************
 * BLOCKS FOR AREA CONTROL MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <LFCUnit.hpp>

/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <EDCUnit.hpp>

/**************************************************************
 * BLOCKS FOR AREA MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <AreaGrid.hpp>

/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <AreaControl.hpp>

/**************************************************************
 * AREA BLOCK
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <Area.hpp>

/**************************************************************
 * BLOCKS FOR TIE LINE MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <TieLine.hpp>

/**************************************************************
 * BLOCKS FOR RESION MODEL
 *************************************************************/
/*
 * n model parameters.
 * n simulation parameter.
 * n internal parameter.
 */
#include <Resion.hpp> /* not tested */

#endif
