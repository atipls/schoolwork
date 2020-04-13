using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace radio {
    class Program {
        class Radioamator {
            public int Nap { get; set; }
            public int Sorszam { get; set; }
            public string Uzenet { get; set; }
            public Radioamator(string[] data, ref int index) {
                var dsor = data[index++].Split(' ');
                Nap = int.Parse(dsor[0]);
                Sorszam = int.Parse(dsor[1]);
                Uzenet = data[index++];
            }
        }
        static List<Radioamator> Amarotok { get; set; } = new List<Radioamator>();

        public static bool szame(string szo) {
            var valasz = true;
            for (int i = 0; i < szo.Length; i++) {
                if (szo[i] < '0' || szo[i] > '9') {
                    valasz = false;
                    break;
                }
            }
            return valasz;
        }

        static void HelyreallitasKiserlet() {
            var sw = new StreamWriter("adaas.txt");
            for (int i = 1; i <= 11; i++) {
                sw.Write($"{i}. nap: ");
                var napadat = Amarotok.Where(x => x.Nap == i).Select(x => x.Uzenet);
                for (int j = 0; j < 90; j++) {
                    var chr = napadat.Select(x => x[j]).FirstOrDefault(x => x != '#');
                    if (chr == '\0')
                        chr = '#';
                    sw.Write(chr);
                }
                sw.WriteLine();
            }
            sw.Flush();
            sw.Close();
        }

        static void Egyedszam() {
            Console.WriteLine("7. feladat: ");
            Console.Write("Nap sorszáma: ");
            var napsorsz = int.Parse(Console.ReadLine());
            Console.Write("Rádióamatőr sorszáma: ");
            var radsorsz = int.Parse(Console.ReadLine());
            Console.Write("A megfigyelt egyedek száma: ");

            var amator = Amarotok.First(x => x.Nap == napsorsz && x.Sorszam == radsorsz);
            if (!char.IsNumber(amator.Uzenet[0])) {
                Console.WriteLine("Nincs ilyen feljegyzés.");
                return;
            }

            var eresz = amator.Uzenet.Split(' ')[0]; // Egyed rész
            if (eresz.Contains('#')) {
                Console.WriteLine("Nincs információ.");
                return;
            }

            var esplit = eresz.Split('/');
            var egyedek = int.Parse(esplit[0]) + int.Parse(esplit[1]);
            Console.WriteLine(egyedek);
        }

        static void Main(string[] _) {
            var vetel = File.ReadAllLines("veetel.txt");
            int index = 0;
            while (index < vetel.Length)
                Amarotok.Add(new Radioamator(vetel, ref index));

            Console.WriteLine("2. feladat: ");
            Console.WriteLine($"Az első üzenet rögzítője: {Amarotok.First().Sorszam}");
            Console.WriteLine($"Az utolsó üzenet rögzítője: {Amarotok.Last().Sorszam}");
            Console.WriteLine();

            Console.WriteLine("3. feladat: ");
            var amatorok = Amarotok.Where(x => x.Uzenet.Contains("farkas"));
            foreach (var amator in amatorok)
                Console.WriteLine($"{amator.Nap}. nap {amator.Sorszam}. rádióamatőr");
            Console.WriteLine();

            Console.WriteLine("4. feladat: ");
            for (int i = 1; i <= 11; i++) {
                var amatorsz = Amarotok.Count(x => x.Nap == i);
                Console.WriteLine($"{i}. nap: {amatorsz} rádióamatőr");
            }
            Console.WriteLine();

            //5. feladat
            HelyreallitasKiserlet();

            Egyedszam();
            Console.WriteLine();

            Console.ReadLine();
        }
    }
}
