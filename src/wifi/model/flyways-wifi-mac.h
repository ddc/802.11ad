/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006, 2009 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */
#ifndef FLYWAYS_WIFI_MAC_H
#define FLYWAYS_WIFI_MAC_H

#include "ns3/mac48-address.h"
#include "ns3/callback.h"
#include "ns3/packet.h"
#include "ns3/wifi-mac.h"
#include "ns3/qos-utils.h"
#include "ns3/amsdu-subframe-header.h"

namespace ns3 {

class EdcaTxopN;
class WifiMacHeader;
class WifiPhy;
class DcfManager;
class MacLow;
class MacRxMiddle;
class MgtAddBaRequestHeader;

class FlywaysWifiMac : public WifiMac
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;

  FlywaysWifiMac ();
  ~FlywaysWifiMac ();

  // all inherited from WifiMac base class.
  virtual void SetSlot (Time slotTime);
  virtual void SetSifs (Time sifs);
  virtual void SetEifsNoDifs (Time eifsNoDifs);
  virtual void SetAckTimeout (Time ackTimeout);
  virtual void SetCtsTimeout (Time ctsTimeout);
  virtual void SetPifs (Time pifs);
  virtual Time GetSlot (void) const;
  virtual Time GetSifs (void) const;
  virtual Time GetEifsNoDifs (void) const;
  virtual Time GetAckTimeout (void) const;
  virtual Time GetCtsTimeout (void) const;
  virtual Time GetPifs (void) const;
  virtual void SetWifiPhy (Ptr<WifiPhy> phy);
  virtual void SetWifiRemoteStationManager (Ptr<WifiRemoteStationManager> stationManager);
  virtual void Enqueue (Ptr<const Packet> packet, Mac48Address to, Mac48Address from);
  virtual void Enqueue (Ptr<const Packet> packet, Mac48Address to);
  virtual bool SupportsSendFrom (void) const;
  virtual void SetForwardUpCallback (Callback<void,Ptr<Packet>, Mac48Address, Mac48Address> upCallback);
  virtual void SetLinkUpCallback (Callback<void> linkUp);
  virtual void SetLinkDownCallback (Callback<void> linkDown);
  virtual Mac48Address GetAddress (void) const;
  virtual Ssid GetSsid (void) const;
  virtual void SetAddress (Mac48Address address);
  virtual void SetSsid (Ssid ssid);
  virtual Mac48Address GetBssid (void) const;
  virtual void SetBasicBlockAckTimeout (Time blockAckTimeout);
  virtual void SetCompressedBlockAckTimeout (Time blockAckTimeout);
  virtual Time GetBasicBlockAckTimeout (void) const;
  virtual Time GetCompressedBlockAckTimeout (void) const;


  virtual void SetRifs (Time rifs);
  virtual Time GetRifs (void) const;
  virtual void SetShortSlotTimeSupported (bool enable);
  virtual bool GetShortSlotTimeSupported (void) const;
  virtual void SetPromisc (void);
  virtual Ptr<WifiPhy> GetWifiPhy (void) const;
  virtual void ResetWifiPhy (void);
  virtual Ptr<WifiRemoteStationManager> GetWifiRemoteStationManager (void) const;

private:
  Callback<void, Ptr<Packet>, Mac48Address, Mac48Address> m_forwardUp;
  virtual void DoDispose (void);
  //void DoStart ();
  void Receive (Ptr<Packet> packet, const WifiMacHeader *hdr);
  void ForwardUp (Ptr<Packet> packet, Mac48Address from, Mac48Address to);
  FlywaysWifiMac &operator = (const FlywaysWifiMac &);
  FlywaysWifiMac (const FlywaysWifiMac &);
  void SendAddBaResponse (const MgtAddBaRequestHeader *reqHdr, Mac48Address originator);
  
  /**
  * When an A-MSDU is received, is deaggregated by this method and all extracted packets are
  * forwarded up.
  */
  void DeaggregateAmsduAndForward (Ptr<Packet> aggregatedPacket, const WifiMacHeader *hdr);

  typedef std::list<std::pair<Ptr<Packet>, AmsduSubframeHeader> > DeaggregatedMsdus;
  typedef std::list<std::pair<Ptr<Packet>, AmsduSubframeHeader> >::const_iterator DeaggregatedMsdusCI;

  virtual void FinishConfigureStandard (enum WifiPhyStandard standard);
  void SetQueue (enum AcIndex ac);
  Ptr<EdcaTxopN> GetVOQueue (void) const;
  Ptr<EdcaTxopN> GetVIQueue (void) const;
  Ptr<EdcaTxopN> GetBEQueue (void) const;
  Ptr<EdcaTxopN> GetBKQueue (void) const;

  Ptr<EdcaTxopN> m_queue;
  Ptr<MacLow> m_low;
  Ptr<WifiPhy> m_phy;
  Ptr<WifiRemoteStationManager> m_stationManager;
  MacRxMiddle *m_rxMiddle;
  MacTxMiddle *m_txMiddle;
  DcfManager *m_dcfManager;
  Ssid m_ssid;
  Time m_eifsNoDifs;
  bool m_shortSlotTimeSupported;
};

} //namespace ns3

#endif /* FLYWAYS_WIFI_MAC_H */
