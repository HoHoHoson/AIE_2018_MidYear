using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels.Tcp;
using System.Runtime.Remoting.Channels;

namespace RPC_Hoson
{
    class Program
    {
        static void Main(string[] args)
        {
            TcpServerChannel tcpServer = new TcpServerChannel(12345);
            ChannelServices.RegisterChannel(tcpServer, false);

            RemotingConfiguration.RegisterWellKnownServiceType(typeof(Player), "Player", WellKnownObjectMode.SingleCall);

            Console.WriteLine("Standby for Titanfall...\n");
            Console.ReadLine();
        }
    }

    class Player : MarshalByRefObject
    {
        public void Talk(string user, string text)
        {
            Console.WriteLine(user + " >  " + text + "\n");
        }
    }
}
