#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/wifi-net-device.h"
#include "ns3/adhoc-wifi-mac.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/test.h"
#include "ns3/pointer.h"
#include "ns3/rng-seed-manager.h"
#include "ns3/config.h"
#include "ns3/boolean.h"
#include "ns3/string.h"
#include "ns3/packet-socket-address.h"
#include "ns3/packet-socket-server.h"
#include "ns3/packet-socket-client.h"
#include "ns3/packet-socket-helper.h"

using namespace ns3;

//Helper function to assign streams to random variables, to control
//randomness in the tests
static void
AssignWifiRandomStreams (Ptr<WifiMac> mac, int64_t stream)
{
  int64_t currentStream = stream;
  Ptr<RegularWifiMac> rmac = DynamicCast<RegularWifiMac> (mac);
  if (rmac)
    {
      PointerValue ptr;
      rmac->GetAttribute ("DcaTxop", ptr);
      Ptr<DcaTxop> dcaTxop = ptr.Get<DcaTxop> ();
      currentStream += dcaTxop->AssignStreams (currentStream);

      rmac->GetAttribute ("VO_EdcaTxopN", ptr);
      Ptr<EdcaTxopN> vo_edcaTxopN = ptr.Get<EdcaTxopN> ();
      currentStream += vo_edcaTxopN->AssignStreams (currentStream);

      rmac->GetAttribute ("VI_EdcaTxopN", ptr);
      Ptr<EdcaTxopN> vi_edcaTxopN = ptr.Get<EdcaTxopN> ();
      currentStream += vi_edcaTxopN->AssignStreams (currentStream);

      rmac->GetAttribute ("BE_EdcaTxopN", ptr);
      Ptr<EdcaTxopN> be_edcaTxopN = ptr.Get<EdcaTxopN> ();
      currentStream += be_edcaTxopN->AssignStreams (currentStream);

      rmac->GetAttribute ("BK_EdcaTxopN", ptr);
      Ptr<EdcaTxopN> bk_edcaTxopN = ptr.Get<EdcaTxopN> ();
      currentStream += bk_edcaTxopN->AssignStreams (currentStream);
    }
}




class WifiTest : public TestCase
{
public:
  WifiTest ();

  virtual void DoRun (void);


private:
  void RunOne (void);
  void CreateOne (Vector pos, Ptr<YansWifiChannel> channel);
  void SendOnePacket (Ptr<WifiNetDevice> dev);

  ObjectFactory m_manager;
  ObjectFactory m_mac;
  ObjectFactory m_propDelay;
};

WifiTest::WifiTest ()
  : TestCase ("Wifi")
{
}

void
WifiTest::SendOnePacket (Ptr<WifiNetDevice> dev)
{
  Ptr<Packet> p = Create<Packet> ();
  dev->Send (p, dev->GetBroadcast (), 1);
}

void
WifiTest::CreateOne (Vector pos, Ptr<YansWifiChannel> channel)
{
  Ptr<Node> node = CreateObject<Node> ();
  Ptr<WifiNetDevice> dev = CreateObject<WifiNetDevice> ();

  Ptr<WifiMac> mac = m_mac.Create<WifiMac> ();
  mac->ConfigureStandard (WIFI_PHY_STANDARD_80211a);
  Ptr<ConstantPositionMobilityModel> mobility = CreateObject<ConstantPositionMobilityModel> ();
  Ptr<YansWifiPhy> phy = CreateObject<YansWifiPhy> ();
  Ptr<ErrorRateModel> error = CreateObject<YansErrorRateModel> ();
  phy->SetErrorRateModel (error);
  phy->SetChannel (channel);
  phy->SetDevice (dev);
  phy->ConfigureStandard (WIFI_PHY_STANDARD_80211a);
  Ptr<WifiRemoteStationManager> manager = m_manager.Create<WifiRemoteStationManager> ();

  mobility->SetPosition (pos);
  node->AggregateObject (mobility);
  mac->SetAddress (Mac48Address::Allocate ());
  dev->SetMac (mac);
  dev->SetPhy (phy);
  dev->SetRemoteStationManager (manager);
  node->AddDevice (dev);

  Simulator::Schedule (Seconds (1.0), &WifiTest::SendOnePacket, this, dev);
}

void
WifiTest::RunOne (void)
{
  Ptr<YansWifiChannel> channel = CreateObject<YansWifiChannel> ();
  Ptr<PropagationDelayModel> propDelay = m_propDelay.Create<PropagationDelayModel> ();
  Ptr<PropagationLossModel> propLoss = CreateObject<RandomPropagationLossModel> ();
  channel->SetPropagationDelayModel (propDelay);
  channel->SetPropagationLossModel (propLoss);

  CreateOne (Vector (0.0, 0.0, 0.0), channel);
  CreateOne (Vector (5.0, 0.0, 0.0), channel);
  CreateOne (Vector (5.0, 0.0, 0.0), channel);

  Simulator::Stop (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
}

void
WifiTest::DoRun (void)
{
  m_mac.SetTypeId ("ns3::AdhocWifiMac");
  m_propDelay.SetTypeId ("ns3::ConstantSpeedPropagationDelayModel");

  m_manager.SetTypeId ("ns3::ArfWifiManager");
  RunOne ();
  m_manager.SetTypeId ("ns3::AarfWifiManager");
  RunOne ();
  m_manager.SetTypeId ("ns3::ConstantRateWifiManager");
  RunOne ();
  m_manager.SetTypeId ("ns3::OnoeWifiManager");
  RunOne ();
  m_manager.SetTypeId ("ns3::AmrrWifiManager");
  RunOne ();
  m_manager.SetTypeId ("ns3::IdealWifiManager");
  RunOne ();

  m_mac.SetTypeId ("ns3::AdhocWifiMac");
  RunOne ();
  m_mac.SetTypeId ("ns3::ApWifiMac");
  RunOne ();
  m_mac.SetTypeId ("ns3::StaWifiMac");
  RunOne ();


  m_propDelay.SetTypeId ("ns3::RandomPropagationDelayModel");
  m_mac.SetTypeId ("ns3::AdhocWifiMac");
  RunOne ();
}


