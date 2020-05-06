using System;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tort {
    class Tort {
        public int Szamlalo;
        public int Nevezo;

        public float Osztva => (Szamlalo * 1f) / (Nevezo * 1f);
        public int? Egesz => Osztva % 1 == 0 ? new int?((int)Osztva) : null;

        public static Tort Beker() {
            var szamlalo = Program.SzamBeker("Adja meg a számlálót: ");
            var nevezo = Program.SzamBeker("Adja meg a nevezőt: ");

            return new Tort {
                Szamlalo = szamlalo,
                Nevezo = nevezo,
            };
        }

        public Tort(params string[] values) {
            if (values.Length < 2)
                return;
            Szamlalo = int.Parse(values[0]);
            Nevezo = int.Parse(values[1]);
        }

        public Tort Egyszerusitve() {
            var lnko = LNKO(Szamlalo, Nevezo);

            return new Tort {
                Szamlalo = Szamlalo / lnko,
                Nevezo = Nevezo / lnko,
            };
        }

        public Tort Bovitve(Tort t1) {
            var lkkt = LKKT(Nevezo, t1.Nevezo);
            return new Tort { Szamlalo = (Szamlalo * lkkt) / Nevezo, Nevezo = lkkt };
        }

        // Törtek összeszorszása
        public static Tort operator *(Tort a, Tort b)
            => new Tort { Szamlalo = a.Szamlalo * b.Szamlalo, Nevezo = a.Nevezo * b.Nevezo };


        public static Tort operator +(Tort a, Tort b) {
            var b1 = a.Bovitve(b);
            var b2 = b.Bovitve(a);

            return new Tort { Szamlalo = b1.Szamlalo + b2.Szamlalo, Nevezo = b1.Nevezo };
        }

        // 2. feladat
        static int LNKO(int a, int b) {
            if (a == b) return a;
            if (a < b) return LNKO(a, b - a);
            if (a > b) return LNKO(a - b, b);

            throw new Exception("Nem elérhető!");
        }

        // 5. feladat
        static int LKKT(int a, int b) => a * b / LNKO(a, b);

        public override string ToString() => $"{Szamlalo}/{Nevezo}";
        public string Rovid => Egesz.HasValue ? $"{Egesz}" : $"{Szamlalo}/{Nevezo}";
    }

    class Program {
        public static int SzamBeker(string prompt) {
            Console.Write(prompt);
            return int.Parse(Console.ReadLine());
        }

        public static string Osszead(Tort t1, Tort t2) {
            var osszeadva = t1 + t2;
            return $"{t1} + {t2} = {t1.Bovitve(t2)} + {t2.Bovitve(t1)} = {osszeadva} = {osszeadva.Egyszerusitve().Rovid}";
        }

        public static string Osszeszoroz(Tort t1, Tort t2) {
            var szorozva = t1 * t2;
            return $"{t1} * {t2} = {szorozva} = {szorozva.Egyszerusitve().Rovid}";
        }

        static void Main(string[] args) {
            Console.WriteLine("1. feladat:");
            var tort1 = Tort.Beker();

            if (tort1.Egesz.HasValue)
                Console.WriteLine($"Felírható egész számként: {tort1.Osztva:0}");
            else Console.WriteLine("Nem egész.");


            Console.WriteLine("3. feladat:");
            Console.WriteLine($"{tort1} = {tort1.Egyszerusitve().Rovid}");

            Console.WriteLine("4. feladat:");
            var tort2 = Tort.Beker();
            Console.WriteLine(Osszeszoroz(tort1, tort2));

            Console.WriteLine("6. feladat:");
            Console.WriteLine(Osszead(tort1, tort2));

            Console.WriteLine("7. feladat:");
            var lines = File.ReadAllLines("adat.txt");
            StreamWriter sw = new StreamWriter("eredmeny.txt");
            for (int i = 0; i < lines.Length; i++) {
                var split = lines[i].Split(' ');
                var t1 = new Tort(split[0], split[1]);
                var t2 = new Tort(split[2], split[3]);

                switch (split[4]) {
                    case "+": sw.WriteLine(Osszead(t1, t2)); break;
                    case "*": sw.WriteLine(Osszeszoroz(t1, t2)); break;
                    default: throw new Exception("Nem elérhető!");
                }
                sw.Flush();
            }
            sw.Close();
            Console.WriteLine("Eredmény kiírva.");

            Console.ReadLine();
        }
    }
}
