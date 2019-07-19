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


#include <ns3/buildings-module.h>
#include <ns3/log.h>
#include "femtocellBlockAllocator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("FemtocellBlockAllocator");
NS_OBJECT_ENSURE_REGISTERED (FemtocellBlockAllocator);

FemtocellBlockAllocator::FemtocellBlockAllocator (Box area, uint32_t nApartmentsX, uint32_t nFloors)
  : m_area (area),
    m_nApartmentsX (nApartmentsX),
    m_nFloors (nFloors),
    m_xSize (nApartmentsX*10 + 20),
    m_ySize (70)
{
  m_xMinVar = CreateObject<UniformRandomVariable> ();
  m_xMinVar->SetAttribute ("Min", DoubleValue (area.xMin));
  m_xMinVar->SetAttribute ("Max", DoubleValue (area.xMax - m_xSize));
  m_yMinVar = CreateObject<UniformRandomVariable> ();
  m_yMinVar->SetAttribute ("Min", DoubleValue (area.yMin));
  m_yMinVar->SetAttribute ("Max", DoubleValue (area.yMax - m_ySize));
}

void FemtocellBlockAllocator::Create (uint32_t n)
{
  for (uint32_t i = 0; i < n; ++i)
    {
      Create ();
    }
}

void FemtocellBlockAllocator::Create ()
{
  Box box;
  uint32_t attempt = 0;
  do
    {
      NS_ASSERT_MSG (attempt < 100, "Too many failed attemtps to position apartment block. Too many blocks? Too small area?");
      box.xMin = m_xMinVar->GetValue ();
      box.xMax = box.xMin + m_xSize;
      box.yMin = m_yMinVar->GetValue ();
      box.yMax = box.yMin + m_ySize;
      ++attempt;
    }
  while (OverlapsWithAnyPrevious (box));

  NS_LOG_LOGIC ("allocated non overlapping block " << box);
  m_previousBlocks.push_back (box);
  Ptr<GridBuildingAllocator>  gridBuildingAllocator;
  gridBuildingAllocator = CreateObject<GridBuildingAllocator> ();
  gridBuildingAllocator->SetAttribute ("GridWidth", UintegerValue (1));
  gridBuildingAllocator->SetAttribute ("LengthX", DoubleValue (10*m_nApartmentsX));
  gridBuildingAllocator->SetAttribute ("LengthY", DoubleValue (10*2));
  gridBuildingAllocator->SetAttribute ("DeltaX", DoubleValue (10));
  gridBuildingAllocator->SetAttribute ("DeltaY", DoubleValue (10));
  gridBuildingAllocator->SetAttribute ("Height", DoubleValue (3*m_nFloors));
  gridBuildingAllocator->SetBuildingAttribute ("NRoomsX", UintegerValue (m_nApartmentsX));
  gridBuildingAllocator->SetBuildingAttribute ("NRoomsY", UintegerValue (2));
  gridBuildingAllocator->SetBuildingAttribute ("NFloors", UintegerValue (m_nFloors));
  gridBuildingAllocator->SetAttribute ("MinX", DoubleValue (box.xMin + 10));
  gridBuildingAllocator->SetAttribute ("MinY", DoubleValue (box.yMin + 10));
  gridBuildingAllocator->Create (2);
}

bool FemtocellBlockAllocator::OverlapsWithAnyPrevious (Box box)
{
	for (std::list<Box>::iterator it = m_previousBlocks.begin (); it != m_previousBlocks.end (); ++it)
	{
		if (AreOverlapping (*it, box))
			return true;
	}

  return false;
}

bool FemtocellBlockAllocator::AreOverlapping (Box a, Box b)
{
  return !((a.xMin > b.xMax) || (b.xMin > a.xMax) || (a.yMin > b.yMax) || (b.yMin > a.yMax));
}

}/* namespace ns3 */

