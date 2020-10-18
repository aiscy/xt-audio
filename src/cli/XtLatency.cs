using System.Runtime.InteropServices;

namespace Xt
{
    [StructLayout(LayoutKind.Sequential)]
    public sealed class XtLatency
    {
        public double input;
        public double output;

        public override string ToString() => XtPrint.LatencyToString(this);
    }
}