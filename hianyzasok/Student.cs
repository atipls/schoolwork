using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public class Student : ICanSkipSchool, IHasFullName {
        public string FirstName { get; private set; }
        public string LastName { get; private set; }
        public string FullName => $"{FirstName} {LastName}";

        public List<ClassSkip> Classes { get; }
        public void AddClass(ClassSkip skip) => Classes.Add(skip);

        public Student(string firstName, string lastName) {
            FirstName = firstName;
            LastName = lastName;
            Classes = new List<ClassSkip>();
        }
    }
}
