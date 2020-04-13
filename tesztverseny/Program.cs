using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tesztverseny {
    class Program {
        public class Verseny { //Az egész verseny.
            public class Versenyzo {
                public string Valaszok { get; private set; }
                public int Pontszam { get; private set; }
                public Versenyzo(string valaszok) {
                    Valaszok = valaszok;
                    Pontszam = 0;
                }
                public void CalculatePontszam(string megoldas, Func<int, int> feladatPontozas) {
                    for (int i = 0; i < Valaszok.Length; i++) {
                        if (Valaszok[i] == megoldas[i])
                            Pontszam += feladatPontozas(i);
                    }
                }
            }
            public string Megoldas { get; set; } = string.Empty;
            public Dictionary<string, Versenyzo> Versenyzok { get; private set; } = new Dictionary<string, Versenyzo>();
            public Verseny(string file) {
                var data = File.ReadAllLines(file);
                Megoldas = data[0];
                foreach (var str in data.Skip(1)) {
                    var ev = str.Split(' ');
                    AddVersenyzo(ev[0], ev[1]);
                }
            }
            public void AddVersenyzo(string nev, string valaszok) => Versenyzok.Add(nev, new Versenyzo(valaszok));
            public void CalculatePontszam(Func<int, int> feladatPontozas) {
                foreach (var versenyzo in Versenyzok)
                    versenyzo.Value.CalculatePontszam(Megoldas, feladatPontozas);
            }
        }
        public static int MegadottPontozas(int feladat) {
            if (feladat == 13)
                return 6;
            else if (feladat >= 10 && feladat <= 12)
                return 5;
            else if (feladat >= 5 && feladat <= 9)
                return 4;
            return 3;
        }
        static void Main(string[] _) {
            Console.WriteLine("1. feladat: Az adatok beolvasása");
            var verseny = new Verseny("valaszok.txt");

            Console.WriteLine($"2. feladat: A vetélketőn {verseny.Versenyzok.Count} versenyző indult.");

            Console.Write($"3. feladat: A versenyző azonosítója: ");
            string azon = Console.ReadLine();
            string valasz = verseny.Versenyzok[azon].Valaszok;
            Console.WriteLine($"{valasz}\t(a versenyző válasza)");

            Console.WriteLine("4. feladat: ");
            Console.WriteLine($"{verseny.Megoldas}\t(a helyes megoldás)");
            for (int i = 0; i < verseny.Megoldas.Length; i++)
                Console.Write($"{(verseny.Megoldas[i] == valasz[i] ? '+' : ' ')}");
            Console.Write("\t(a versenyző helyes válaszai)\n");

            Console.Write("5. feladat: A feladat sorszáma: ");
            int sorsz = int.Parse(Console.ReadLine()) - 1;
            int jo_valaszok = 0;
            foreach (var vz in verseny.Versenyzok) {
                if (vz.Value.Valaszok[sorsz] == verseny.Megoldas[sorsz])
                    jo_valaszok++;
            }
            Console.WriteLine($"A feladatra {jo_valaszok} fő, a versenyzők {(float)jo_valaszok / verseny.Versenyzok.Count * 100:0.00}%-a adott helyes\nválaszt.");

            Console.WriteLine("6. feladat: A versenyzők pontszámának meghatározása");
            verseny.CalculatePontszam(MegadottPontozas);

            Console.WriteLine($"7. feladat: A verseny legjobbjai:");
            var sortedVersenyzok = verseny.Versenyzok.OrderByDescending(x => x.Value.Pontszam).ToList();

            int helyezes = 0;
            int elozoPontszam = 0;
            for(int i = 0; i < sortedVersenyzok.Count; i++) {
                if (helyezes > 3)
                    break;
                var pontszam = sortedVersenyzok[i].Value.Pontszam;
                if (pontszam != elozoPontszam)
                    helyezes++;
                Console.WriteLine($"{pontszam}. díj ({pontszam} pont): {sortedVersenyzok[i].Key}");
            }

            Console.ReadLine();
        }
    }
}
