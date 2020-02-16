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
    public static class ClassSkipExtensions {
        public static bool DidSkip(this ClassSkip skip) => skip == ClassSkip.UnknownAway || skip == ClassSkip.ProvenAway;
    }
    public interface ICanSkipSchool : ISchoolDay<ClassSkip> { }
}
