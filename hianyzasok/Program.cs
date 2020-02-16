using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    class Program {
        //4. feladat
        public static string HetNapja(int honap, int nap) {
            var napnev = new string[] { "vasarnap", "hetfo", "kedd", "szerda", "csutortok", "pentek", "szombat" };
            var napszam = new int[] { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 335 };
            var napsorszam = (napszam[honap - 1] + nap) % 7;
            return napnev[napsorszam];
        }

        static void Main(string[] _) {
            var manager = new SchoolDayManager();
            if (!manager.Load("naplo.txt")) {
                Console.WriteLine("Nem tudtam betölteni a naplót!");
            }

            var bejegyzesek = manager.SchoolDays.Sum(x => x.Students.Count);
            Console.WriteLine($"2. feladat:\nA naplóban {bejegyzesek} bejegyzés van.");

            var igazolt = manager.SchoolDays.Sum(x => x.Students.Sum(s => s.Classes.Count(c => c == ClassSkip.ProvenAway)));
            var igazolatlan = manager.SchoolDays.Sum(x => x.Students.Sum(s => s.Classes.Count(c => c == ClassSkip.UnknownAway)));
            Console.WriteLine($"3. feladat:\nAz igazolt hiányzások száma {igazolt}, az igazolatlanoké {igazolatlan} óra.");

            Console.WriteLine("5. feladat:");
            Console.Write("A hónap sorszáma: ");
            var honap_cvt = Console.ReadLine();
            Console.Write("A nap sorszáma: ");
            var nap_cvt = Console.ReadLine();
            Console.WriteLine($"Azon a napon {HetNapja(int.Parse(honap_cvt.Trim()), int.Parse(nap_cvt.Trim()))} volt.");

            Console.WriteLine("6. feladat:");
            Console.Write("A nap neve: ");
            var nap_hianyzas = Console.ReadLine().Trim().ToLower();
            Console.Write("Az óra sorszáma: ");
            var ora_hianyzas = Console.ReadLine();

            var ora_szam = int.Parse(ora_hianyzas);
            if (ora_szam > 6)
                ora_szam = 6;

            var hianyzasok = manager.SchoolDays.Sum(x => x.IsDayStr(nap_hianyzas) ? x.Students.Count(y => y.Classes[ora_szam - 1].DidSkip()) : 0);
            Console.WriteLine($"Ekkor összesen {hianyzasok} óra hiányzás történt.");

            var osszes_hianyzo = new DefaultDictionary<string, int>(0);
            foreach (var diak in manager.SchoolDays.SelectMany(x => x.Students))
                osszes_hianyzo[diak.FullName] += diak.Classes.Count(x => x.DidSkip());

            var max_hianyzas = osszes_hianyzo.Max(x => x.Value);
            var legtobbet_hianyzok = osszes_hianyzo.Where(x => x.Value == max_hianyzas);
            Console.WriteLine($"7. feladat:\nA legtöbbet hiányzó tanulók: {string.Join(", ", legtobbet_hianyzok.Select(x => x.Key).ToArray())}");

            Console.ReadLine();
        }
    }
}
