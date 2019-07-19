/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
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
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/gnuplot-helper.h"
#include "ns3/file-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
void gnuPlotFile();
int
main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));


  gnuPlotFile();

  Simulator::Stop();
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

void gnuPlotFile()
{
	  std::string probeType = "ns3::Ipv4PacketProbe";
	  std::string tracePath = "/NodeList/*/$ns3::Ipv4L3Protocol/Tx";

	  // Use GnuplotHelper to plot the packet byte count over time
	  GnuplotHelper plotHelper;

	  // Configure the plot.  The first argument is the file name prefix
	  // for the output files generated.  The second, third, and fourth
	  // arguments are, respectively, the plot title, x-axis, and y-axis labels
	  plotHelper.ConfigurePlot ("seventh-packet-byte-count",
	                            "Packet Byte Count vs. Time",
	                            "Time (Seconds)",
	                            "Packet Byte Count");

	  // Specify the probe type, trace source path (in configuration namespace), and
	  // probe output trace source ("OutputBytes") to plot.  The fourth argument
	  // specifies the name of the data series label on the plot.  The last
	  // argument formats the plot by specifying where the key should be placed.
	  plotHelper.PlotProbe (probeType,
	                        tracePath,
	                        "OutputBytes",
	                        "Packet Byte Count",
	                        GnuplotAggregator::KEY_BELOW);

	  // Use FileHelper to write out the packet byte count over time
	  FileHelper fileHelper;

	  // Configure the file to be written, and the formatting of output data.
	  fileHelper.ConfigureFile ("seventh-packet-byte-count",
	                            FileAggregator::FORMATTED);

	  // Set the labels for this formatted output file.
	  fileHelper.Set2dFormat ("Time (Seconds) = %.3e\tPacket Byte Count = %.0f");

	  // Specify the probe type, trace source path (in configuration namespace), and
	  // probe output trace source ("OutputBytes") to write.
	  fileHelper.WriteProbe (probeType,
	                         tracePath,
	                         "OutputBytes");

}

