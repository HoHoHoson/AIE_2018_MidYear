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
            TcpClientChannel tcpClient = new TcpClientChannel();
            ChannelServices.RegisterChannel(tcpClient, false);

            string playerName = "ScrubRekker";
            string clientURL = "tcp://localhost:" + 12345 + "/" + "Player";
            Player client = (Player)Activator.GetObject(typeof(Player), clientURL);
            Console.Write("Welcome back " + playerName + "\n\n");

            while (true)
            {
                Console.Write(">>  ");
                string input = Console.ReadLine();

                client.Talk(playerName,input);
            }
        }
    }

    class Player : MarshalByRefObject
    {
        public void Talk(string user, string text)
        { }
    }
}
