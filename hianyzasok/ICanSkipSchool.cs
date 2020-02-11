using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public enum ClassSkip {
        NotSkipped,
        ProvenAway,
        UnknownAway,
        NoClassToSkip,
    }
    public interface ICanSkipSchool : ISchoolDay<ClassSkip> { }
}
