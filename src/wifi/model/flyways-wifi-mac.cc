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
#include "ns3/pointer.h"
#include "ns3/log.h"
#include "ns3/string.h"
#include "ns3/simulator.h"
#include <iostream>

#include "ns3/qos-tag.h"
#include "ns3/edca-txop-n.h"
#include "ns3/flyways-wifi-mac.h"
#include "ns3/mac-low.h"
#include "ns3/dcf-manager.h"
#include "ns3/mac-rx-middle.h"
#include "ns3/mac-tx-middle.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/msdu-aggregator.h"
#include "ns3/amsdu-subframe-header.h"
#include "ns3/mgt-headers.h"

NS_LOG_COMPONENT_DEFINE ("FlywaysWifiMac");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (FlywaysWifiMac);

TypeId
FlywaysWifiMac::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::FlywaysWifiMac")
    .SetParent<WifiMac> ()
	.SetGroupName ("Wifi")
    .AddConstructor<FlywaysWifiMac> ()
    .AddAttribute ("VO_EdcaTxopN",
                   "Queue that manages packets belonging to AC_VO access class",
                   PointerValue (),
                   MakePointerAccessor(&FlywaysWifiMac::GetVOQueue),
                   MakePointerChecker<EdcaTxopN> ())
    .AddAttribute ("VI_EdcaTxopN",
                   "Queue that manages packets belonging to AC_VI access class",
                   PointerValue (),
                   MakePointerAccessor(&FlywaysWifiMac::GetVIQueue),
                   MakePointerChecker<EdcaTxopN> ())
    .AddAttribute ("BE_EdcaTxopN",
                   "Queue that manages packets belonging to AC_BE access class",
                   PointerValue (),
                   MakePointerAccessor(&FlywaysWifiMac::GetBEQueue),
                   MakePointerChecker<EdcaTxopN> ())
    .AddAttribute ("BK_EdcaTxopN",
                   "Queue that manages packets belonging to AC_BK access class",
                   PointerValue (),
                   MakePointerAccessor(&FlywaysWifiMac::GetBKQueue),
                   MakePointerChecker<EdcaTxopN> ())
    ;
  return tid;
}

TypeId
FlywaysWifiMac::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

FlywaysWifiMac::FlywaysWifiMac ()
{
  m_rxMiddle = new MacRxMiddle ();
  m_rxMiddle->SetForwardCallback (MakeCallback (&FlywaysWifiMac::Receive, this));

  m_txMiddle = new MacTxMiddle ();

  m_low = CreateObject<MacLow> ();
  m_low->SetRxCallback (MakeCallback (&MacRxMiddle::Receive, m_rxMiddle));

  m_dcfManager = new DcfManager ();
  m_dcfManager->SetupLowListener (m_low);

  SetQueue (AC_BE);
}

FlywaysWifiMac::~FlywaysWifiMac ()
{
  NS_LOG_FUNCTION (this);
}

void
FlywaysWifiMac::DoDispose (void)
{
  delete m_rxMiddle;
  m_rxMiddle = 0;
  delete m_txMiddle;
  m_txMiddle = 0;
  delete m_dcfManager;
  m_dcfManager = 0;
  m_low = 0;
  m_phy = 0;
  m_stationManager = 0;
  m_queue = 0;

  WifiMac::DoDispose ();
}

void
FlywaysWifiMac::SetSlot (Time slotTime)
{
  m_dcfManager->SetSlot (slotTime);
  m_low->SetSlotTime (slotTime);
}

void
FlywaysWifiMac::SetSifs (Time sifs)
{
  m_dcfManager->SetSifs (sifs);
  m_low->SetSifs (sifs);
}

void
FlywaysWifiMac::SetEifsNoDifs (Time eifsNoDifs)
{
  m_dcfManager->SetEifsNoDifs (eifsNoDifs);
  m_eifsNoDifs = eifsNoDifs;
}

void
FlywaysWifiMac::SetAckTimeout (Time ackTimeout)
{
  m_low->SetAckTimeout (ackTimeout);
}

void
FlywaysWifiMac::SetBasicBlockAckTimeout (Time blockAckTimeout)
{
  m_low->SetBasicBlockAckTimeout (blockAckTimeout);
}

void
FlywaysWifiMac::SetCompressedBlockAckTimeout (Time blockAckTimeout)
{
  m_low->SetCompressedBlockAckTimeout (blockAckTimeout);
}

void
FlywaysWifiMac::SetCtsTimeout (Time ctsTimeout)
{
  m_low->SetCtsTimeout (ctsTimeout);
}

void
FlywaysWifiMac::SetPifs (Time pifs)
{
  m_low->SetPifs (pifs);
}

Time
FlywaysWifiMac::GetSlot (void) const
{
  return m_low->GetSlotTime ();
}

Time
FlywaysWifiMac::GetSifs (void) const
{
  return m_low->GetSifs ();
}

Time
FlywaysWifiMac::GetEifsNoDifs (void) const
{
  return m_eifsNoDifs;
}

Time
FlywaysWifiMac::GetAckTimeout (void) const
{
  return m_low->GetAckTimeout ();
}

Time
FlywaysWifiMac::GetBasicBlockAckTimeout (void) const
{
  return m_low->GetBasicBlockAckTimeout ();
}

Time
FlywaysWifiMac::GetCompressedBlockAckTimeout (void) const
{
  return m_low->GetCompressedBlockAckTimeout ();
}

Time
FlywaysWifiMac::GetCtsTimeout (void) const
{
  return m_low->GetCtsTimeout ();
}

Time
FlywaysWifiMac::GetPifs (void) const
{
  return m_low->GetPifs ();
}

void
FlywaysWifiMac::SetWifiPhy (Ptr<WifiPhy> phy)
{
  m_phy = phy;
  m_dcfManager->SetupPhyListener (phy);
  m_low->SetPhy (phy);
}

void
FlywaysWifiMac::SetWifiRemoteStationManager (Ptr<WifiRemoteStationManager> stationManager)
{
  m_stationManager = stationManager;
  m_queue->SetWifiRemoteStationManager(stationManager);
  m_low->SetWifiRemoteStationManager (stationManager);
}

void
FlywaysWifiMac::SetRifs (Time rifs)
{
  m_low->SetRifs (rifs);
}

Time
FlywaysWifiMac::GetRifs (void) const
{
  return m_low->GetRifs ();
}

void
FlywaysWifiMac::SetShortSlotTimeSupported (bool enable)
{
  m_shortSlotTimeSupported = enable;
}

bool
FlywaysWifiMac::GetShortSlotTimeSupported (void) const
{
  return m_shortSlotTimeSupported;
}

void
FlywaysWifiMac::SetPromisc (void)
{
  m_low->SetPromisc ();
}

Ptr<WifiPhy>
FlywaysWifiMac::GetWifiPhy (void) const
{
  return m_phy;
}

void
FlywaysWifiMac::ResetWifiPhy (void)
{
  m_low->ResetPhy ();
  m_dcfManager->RemovePhyListener (m_phy);
  m_phy = 0;
}

Ptr<WifiRemoteStationManager>
FlywaysWifiMac::GetWifiRemoteStationManager () const
{
  return m_stationManager;
}

void
FlywaysWifiMac::Enqueue (Ptr<const Packet> packet, Mac48Address to, Mac48Address from)
{
  NS_FATAL_ERROR ("Adhoc does not support a from != m_low->GetAddress ()");
}

void
FlywaysWifiMac::Enqueue (Ptr<const Packet> packet, Mac48Address to)
{
  /* For now Qos adhoc stations sends only Qos frame. In the future they
   * should be able to send frames also to Non-Qos Stas.
   */
  NS_LOG_FUNCTION (packet->GetSize () << to);
  WifiMacHeader hdr;
  hdr.SetType (WIFI_MAC_QOSDATA);
  hdr.SetQosAckPolicy (WifiMacHeader::NORMAL_ACK);
  hdr.SetQosNoEosp ();
  hdr.SetQosNoAmsdu ();
  /* Transmission of multiple frames in the same
     Txop is not supported for now */
  hdr.SetQosTxopLimit (0);

  hdr.SetAddr1 (to);
  hdr.SetAddr2 (m_low->GetAddress ());
  hdr.SetAddr3 (GetBssid ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();

  if (m_stationManager->IsBrandNew (to))
    {
      // in adhoc mode, we assume that every destination
      // supports all the rates we support.
      for (uint32_t i = 0; i < m_phy->GetNModes (); i++)
        {
          m_stationManager->AddSupportedMode (to, m_phy->GetMode (i));
        }
      m_stationManager->RecordDisassociated (to);
    }

  hdr.SetQosTid (2); /// AC_VI = 2  ** Video */
  m_queue->Queue (packet, hdr);
}

bool
FlywaysWifiMac::SupportsSendFrom (void) const
{
  return false;
}

void
FlywaysWifiMac::SetForwardUpCallback (Callback<void,Ptr<Packet>, Mac48Address, Mac48Address> upCallback)
{
  m_forwardUp = upCallback;
}

void
FlywaysWifiMac::SetLinkUpCallback (Callback<void> linkUp)
{
  // an Adhoc network is always UP.
  linkUp ();
}

void
FlywaysWifiMac::SetLinkDownCallback (Callback<void> linkDown)
{}

Mac48Address
FlywaysWifiMac::GetAddress (void) const
{
  return m_low->GetAddress ();
}

Ssid
FlywaysWifiMac::GetSsid (void) const
{
  return m_ssid;
}

void
FlywaysWifiMac::SetAddress (Mac48Address address)
{
  m_low->SetAddress (address);
  m_low->SetBssid (address);
}

void
FlywaysWifiMac::SetSsid (Ssid ssid)
{
  m_ssid = ssid;
}

Mac48Address
FlywaysWifiMac::GetBssid (void) const
{
  return m_low->GetBssid ();
}

void
FlywaysWifiMac::ForwardUp (Ptr<Packet> packet, Mac48Address from, Mac48Address to)
{
  m_forwardUp (packet, from, to);
}

void
FlywaysWifiMac::Receive (Ptr<Packet> packet, const WifiMacHeader *hdr)
{
  NS_ASSERT (!hdr->IsCtl ());
  Mac48Address from = hdr->GetAddr2 ();
  Mac48Address to = hdr->GetAddr1 ();
  if (hdr->IsData ())
    {
      if (hdr->IsQosData () && hdr->IsQosAmsdu ())
        {
          NS_LOG_DEBUG ("Received A-MSDU from"<<from);
          DeaggregateAmsduAndForward (packet, hdr);
        }
      else
        {
          ForwardUp (packet, from, to);
        }
    }
  else if (hdr->IsMgt ())
    {
      if (hdr->IsAction ())
        {
          WifiActionHeader actionHdr;
          packet->RemoveHeader (actionHdr);
          if (actionHdr.GetCategory () == WifiActionHeader::BLOCK_ACK &&
              actionHdr.GetAction().blockAck == WifiActionHeader::BLOCK_ACK_ADDBA_REQUEST)
            {
              MgtAddBaRequestHeader reqHdr;
              packet->RemoveHeader (reqHdr);
              SendAddBaResponse (&reqHdr, hdr->GetAddr2 ());
            }
          else if (actionHdr.GetCategory () == WifiActionHeader::BLOCK_ACK &&
                   actionHdr.GetAction().blockAck == WifiActionHeader::BLOCK_ACK_ADDBA_RESPONSE)
            {
              MgtAddBaResponseHeader respHdr;
              packet->RemoveHeader (respHdr);
              m_queue->GotAddBaResponse (&respHdr, hdr->GetAddr2 ());
            }
          else if (actionHdr.GetCategory () == WifiActionHeader::BLOCK_ACK &&
                   actionHdr.GetAction().blockAck == WifiActionHeader::BLOCK_ACK_DELBA)
            {
              MgtDelBaHeader delBaHdr;
              packet->RemoveHeader (delBaHdr);
              if (delBaHdr.IsByOriginator ())
                {
                  /* Delba frame was sent by originator, this means that an ingoing established
                     agreement exists in MacLow */
                     m_low->DestroyBlockAckAgreement (hdr->GetAddr2 (), delBaHdr.GetTid ());                }
              else
                {
                  /* We must notify correct queue tear down of agreement */
                  m_queue->GotDelBaFrame (&delBaHdr, hdr->GetAddr2 ());
                }
            }
        }
    }
}

void
FlywaysWifiMac::DeaggregateAmsduAndForward (Ptr<Packet> aggregatedPacket,
                                           const WifiMacHeader *hdr)
{
  DeaggregatedMsdus packets = MsduAggregator::Deaggregate (aggregatedPacket);
  for (DeaggregatedMsdusCI i = packets.begin (); i != packets.end (); ++i)
    {
      ForwardUp ((*i).first, (*i).second.GetSourceAddr (),
                 (*i).second.GetDestinationAddr ());
    }
}

Ptr<EdcaTxopN>
FlywaysWifiMac::GetVOQueue (void) const
{
  return m_queue;
}

Ptr<EdcaTxopN>
FlywaysWifiMac::GetVIQueue (void) const
{
  return m_queue;
}

Ptr<EdcaTxopN>
FlywaysWifiMac::GetBEQueue (void) const
{
  return m_queue;
}
//void
//FlywaysWifiMac::DoStart ()
//{
//  m_queue->Start();
//  WifiMac::DoStart ();
//}

Ptr<EdcaTxopN>
FlywaysWifiMac::GetBKQueue (void) const
{
  return m_queue;
}

void
FlywaysWifiMac::SetQueue (enum AcIndex ac)
{
  if (ac != AC_VI) {
	  NS_LOG_DEBUG("ignoring AC=" << ac);
	  return;
  }

  Ptr<EdcaTxopN> edca = CreateObject<EdcaTxopN> ();
  edca->SetLow (m_low);
  edca->SetManager (m_dcfManager);
  edca->SetTypeOfStation (ADHOC_STA);
  edca->SetTxMiddle (m_txMiddle);
  edca->SetAccessCategory (ac);
  edca->CompleteConfig ();
  m_queue = edca;
}

void
FlywaysWifiMac::FinishConfigureStandard (enum WifiPhyStandard standard)
{
  switch (standard)
    {
    case WIFI_PHY_STANDARD_80211ad_OFDM:
      ConfigureDcf (m_queue, 3, 1023, AC_VI);
      break;
    case WIFI_PHY_STANDARD_80211a:
      ConfigureDcf (m_queue, 15, 1023, AC_BE);
      break;
    case WIFI_PHY_STANDARD_80211b:
      ConfigureDcf (m_queue, 31, 1023, AC_BE);
      break;
    default:
      NS_FATAL_ERROR ("invalid standard must be 11ad");
      break;
    }
}

void
FlywaysWifiMac::SendAddBaResponse (const MgtAddBaRequestHeader *reqHdr, Mac48Address originator)
{
  WifiMacHeader hdr;
  hdr.SetAction ();
  hdr.SetAddr1 (originator);
  hdr.SetAddr2 (m_low->GetAddress ());
  hdr.SetAddr3 (m_low->GetAddress ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();

  MgtAddBaResponseHeader respHdr;
  StatusCode code;
  code.SetSuccess ();
  respHdr.SetStatusCode (code);
  //Here a control about queues type?
  respHdr.SetAmsduSupport (reqHdr->IsAmsduSupported ());

  if (reqHdr->IsImmediateBlockAck ())
    {
      respHdr.SetImmediateBlockAck ();
    }
  else
    {
      respHdr.SetDelayedBlockAck ();
    }
  respHdr.SetTid (reqHdr->GetTid ());
  /* For now there's not no control about limit of reception.
     We assume that receiver has no limit on reception.
     However we assume that a receiver sets a bufferSize in order to satisfy
     next equation:
     (bufferSize + 1) % 16 = 0
     So if a recipient is able to buffer a packet, it should be also able to buffer
     all possible packet's fragments.
     See section 7.3.1.14 in IEEE802.11e for more details. */
  respHdr.SetBufferSize (1023);
  respHdr.SetTimeout (reqHdr->GetTimeout ());

  WifiActionHeader actionHdr;
  WifiActionHeader::ActionValue action;
  action.blockAck = WifiActionHeader::BLOCK_ACK_ADDBA_RESPONSE;
  actionHdr.SetAction (WifiActionHeader::BLOCK_ACK, action);

  Ptr<Packet> packet = Create<Packet> ();
  packet->AddHeader (respHdr);
  packet->AddHeader (actionHdr);

  /* ns3::MacLow have to buffer all correctly received packet for this block ack session */
  m_low->CreateBlockAckAgreement (&respHdr, originator, reqHdr->GetStartingSequence ());

  //Better a management queue?
  m_queue->PushFront (packet, hdr);
}
} //namespace ns3
