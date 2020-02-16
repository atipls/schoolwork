using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hianyzasok {
    public class DefaultDictionary<TKey, TValue> : Dictionary<TKey, TValue> {
        public TValue DefaultValue { get; set; }
        public DefaultDictionary() : base() { }
        public DefaultDictionary(TValue defaultValue) : base() => DefaultValue = defaultValue;
        public new TValue this[TKey key] {
            get => TryGetValue(key, out var t) ? t : DefaultValue;
            set => base[key] = value;
        }
    }
}
