using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public class SkipManager {
        private List<ICanSkipSchool> m_canSkipSchool;

        public SkipManager(List<ICanSkipSchool> canSkipSchool) {
            m_canSkipSchool = canSkipSchool;
        }
    }
}
