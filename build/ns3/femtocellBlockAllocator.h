/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */

#ifndef SRC_MMWAVE_MODEL_FEMTOCELLBLOCKALLOCATOR_H_
#define SRC_MMWAVE_MODEL_FEMTOCELLBLOCKALLOCATOR_H_

#include <ns3/core-module.h>
#include <ns3/object.h>
#include <ns3/box.h>
#include "femtocellBlockAllocator.h"

namespace ns3
{
	class FemtocellBlockAllocator : public Object
	{
		public:
		  FemtocellBlockAllocator (Box area, uint32_t nApartmentsX, uint32_t nFloors);
		  void Create (uint32_t n);
		  void Create ();
		  bool AreOverlapping (Box a, Box b);

		private:
		  bool OverlapsWithAnyPrevious (Box);
		  Box m_area;
		  uint32_t m_nApartmentsX;
		  uint32_t m_nFloors;
		  std::list<Box> m_previousBlocks;
		  double m_xSize;
		  double m_ySize;
		  Ptr<UniformRandomVariable> m_xMinVar;
		  Ptr<UniformRandomVariable> m_yMinVar;

	};
}/* namespace ns3 */

#endif /* SRC_MMWAVE_MODEL_FEMTOCELLBLOCKALLOCATOR_H_ */
