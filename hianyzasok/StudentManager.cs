using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public class SchoolDayManager {
        public class SchoolDay {
            public int Month;
            public int Day;
            public List<Student> Students;
            public SchoolDay(int month, int day, List<Student> students) {
                Month = month;
                Day = day;
                Students = students;
            }

            public void AddStudent(Student student) => Students.Add(student);
        }
        public List<SchoolDay> SchoolDays;
        public SchoolDayManager() { SchoolDays = new List<SchoolDay>(); }
        public bool Load(string file) {
            if (!File.Exists(file))
                return false;
            SchoolDay current = null;
            using (var contents = new StreamReader(file)) {
                do {
                    contents.SkipWhitespace();
                    var ch = (char)contents.Read();
                    if (ch == '#') {
                        var s_month = contents.ReadUntilSpace();
                        var s_day = contents.ReadUntilSpace();
                        int.TryParse(s_month, out int month);
                        int.TryParse(s_day, out int day);

                        if (current != null) {
                            SchoolDays.Add(current);
                            current = null;
                        }
                        current = new SchoolDay(month, day, new List<Student>());
                    } else {
                        var firstName = contents.ReadUntilSpace();
                        var lastName = contents.ReadUntilSpace();
                        var student = new Student(firstName, lastName);

                        var skips = contents.ReadUntilSpace();
                        for (int i = 0; i < skips.Length; i++) {
                            switch (skips[i]) {
                                case 'O': student.AddClass(ClassSkip.NotSkipped); break;
                                case 'X': student.AddClass(ClassSkip.ProvenAway); break;
                                case 'I': student.AddClass(ClassSkip.UnknownAway); break;
                                case 'N': student.AddClass(ClassSkip.NoClassToSkip); break;
                                default: break;
                            }
                        }

                        current?.AddStudent(student);
                    }
                } while (contents.Peek() != -1);
            }
            if (current != null)
                SchoolDays.Add(current);
            return true;
        }
    }
}
