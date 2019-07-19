/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */
#ifndef SENSITIVITY_MODEL_60_GHZ
#define SENSITIVITY_MODEL_60_GHZ

#include <stdint.h>
#include "wifi-mode.h"
#include "error-rate-model.h"
#include "dsss-error-rate-model.h"
#include "wifi-tx-vector.h"

namespace ns3 {

class ErrorRateModel;

class SensitivityModel60GHz : public ErrorRateModel
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;

  SensitivityModel60GHz ();

  void Set80211adBandwidth (uint64_t bandwidth);
  double Get80211adBandwidth (void) const;

  virtual double GetChunkSuccessRate (WifiMode mode, WifiTxVector txVector, double snr, uint32_t nbits) const;

private:

  uint64_t m_80211ad_bandwidth;
};

} // namespace ns3

#endif /* SENSITIVITY_MODEL_60_GHZ */
