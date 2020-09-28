using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kutyák {
    public struct KutyaNev {
        public int ID;
        public string Nev;

        public KutyaNev(string[] data) {
            int.TryParse(data[0], out ID);
            Nev = data[1];
        }
    }

    public struct KutyaFajta {
        public int ID;
        public string Nev;
        public string EredetiNev;

        public KutyaFajta(string[] data) {
            int.TryParse(data[0], out ID);
            Nev = data[1];
            EredetiNev = data[2];
        }
    }

    public struct Kutya {
        public int ID;
        public int FajtaID;
        public int NevID;
        public int Eletkor;
        public string UtolsoOrvosiEllenorzes;

        public Kutya(string[] data) {
            int.TryParse(data[0], out ID);
            int.TryParse(data[1], out FajtaID);
            int.TryParse(data[2], out NevID);
            int.TryParse(data[3], out Eletkor);
            UtolsoOrvosiEllenorzes = data[4];
        }
    }

    public class Program {
        static List<KutyaNev> KutyaNevek = new List<KutyaNev>();
        static List<KutyaFajta> KutyaFajtak = new List<KutyaFajta>();
        static List<Kutya> Kutyak = new List<Kutya>();

        static void Main(string[] _) {
            var kutyaNevek = ReadCSVFileData("KutyaNevek.csv", ';');
            var kutyaFajtak = ReadCSVFileData("KutyaFajták.csv", ';');
            var kutyak = ReadCSVFileData("Kutyák.csv", ';');

            foreach (var nev in kutyaNevek) KutyaNevek.Add(new KutyaNev(nev));
            foreach (var fajta in kutyaFajtak) KutyaFajtak.Add(new KutyaFajta(fajta));
            foreach (var kutya in kutyak) Kutyak.Add(new Kutya(kutya));

            Console.WriteLine($"3. Feladat: {kutyaNevek.Count}. db kutyanév található.");
            Console.WriteLine($"6. Feladat: A Kutyák átlagéletkora: {Kutyak.Average(x => x.Eletkor):F2} év.");

            var legnagyobbEletkor = Kutyak.Max(x => x.Eletkor);
            var legidosebb = Kutyak.First(x => x.Eletkor == legnagyobbEletkor);
            Console.WriteLine($"7. Feladat: A legidősebb kutya neve és fajtája: {KutyaNevek.First(x => x.ID == legidosebb.NevID).Nev}, {KutyaFajtak.First(x => x.ID == legidosebb.FajtaID).Nev}");

            Console.WriteLine($"8. Feladat: Január 10.-én vizsgált kutya fajták: ");
            var jan10Kutyak = Kutyak.Where(x => x.UtolsoOrvosiEllenorzes == "2018.01.10").GroupBy(x => x.FajtaID);
            foreach (var jan10Kutya in jan10Kutyak)
                Console.WriteLine($"\t{KutyaFajtak.First(x => x.ID == jan10Kutya.Key).Nev}: {jan10Kutya.Count()} kutya");

            var naponKutyak = Kutyak.GroupBy(x => x.UtolsoOrvosiEllenorzes).OrderByDescending(x => x.Key).First();
            Console.WriteLine($"9. Feladat: Legjobban leterhelt nap: {naponKutyak.Key}: {naponKutyak.Count()} kutya");

            Console.WriteLine($"10. Feladat: névstatisztika.txt");

            var writer = new StreamWriter("névstatisztika.txt");
            var kutyaNevstat = Kutyak.GroupBy(x => x.NevID).OrderByDescending(x => x.Count());
            foreach (var nevstat in kutyaNevstat) {
                writer.WriteLine($"{KutyaNevek.First(x => x.ID == nevstat.Key).Nev};{nevstat.Count()}");
            }
            writer.Flush();
            writer.Close();

            Console.ReadLine();
        }

        public static List<string[]> ReadCSVFileData(string file, char delim) {
            var data = File.ReadAllLines(file).Skip(1);
            var final = new List<string[]>();
            foreach (var item in data)
                final.Add(item.Split(delim));
            return final;
        }
    }
}