using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public static class ReaderExtensions {
        private static List<int> invalidCharacters = new List<int> { ' ', '\r', '\n', -1 };
        public static void SkipWhitespace(this StreamReader reader) {
            while (invalidCharacters.Contains(reader.Peek()))
                reader.Read();
        }
        public static string ReadUntilSpace(this StreamReader reader) {
            reader.SkipWhitespace();
            string str = "";
            do {
                str += (char)reader.Read();
            } while (!invalidCharacters.Contains(reader.Peek()));
            return str;
        }
    }
}
