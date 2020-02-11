using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    class Program {
        string HetNapja(int honap, int nap) {
            var napnev = new string[] { "vasarnap", "hetfo", "kedd", "szerda", "csutortok",
"pentek", "szombat" };
            var napszam = new int[] { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 335 };
        static void Main(string[] args) {
            var manager = new SchoolDayManager();
            if (!manager.Load("naplo.txt")) {
                Console.WriteLine("Couldn't load the manager!");
            }
            Console.WriteLine(manager.SchoolDays.Count);
        }
    }
}
