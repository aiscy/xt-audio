package com.xtaudio.xt;

import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;

public final class XtService {

    private final Pointer s;

    XtService(Pointer s) {
        this.s = s;
    }

    @Override
    public String toString() {
        return getName();
    }

    public XtSystem getSystem() {
        return XtSystem.class.getEnumConstants()[XtNative.XtServiceGetSystem(s) - 1];
    }

    public String getName() {
        return XtNative.XtServiceGetName(s);
    }

    public int getCapabilities() {
        return XtNative.XtServiceGetCapabilities(s);
    }

    public int getDeviceCount() {
        IntByReference count = new IntByReference();
        XtNative.handleError(XtNative.XtServiceGetDeviceCount(s, count));
        return count.getValue();
    }

    public XtDevice openDevice(int index) {
        PointerByReference d = new PointerByReference();
        XtNative.handleError(XtNative.XtServiceOpenDevice(s, index, d));
        return new XtDevice(d.getValue());
    }

    public XtDevice openDefaultDevice(boolean output) {
        PointerByReference d = new PointerByReference();
        XtNative.handleError(XtNative.XtServiceOpenDefaultDevice(s, output, d));
        return d.getValue() == null ? null : new XtDevice(d.getValue());
    }

    public XtStream aggregateStream(XtDevice[] devices, XtChannels[] channels, double[] bufferSizes, int count, XtMix mix,
            boolean interleaved, boolean raw, XtDevice master, XtStreamCallback streamCallback, XtXRunCallback xRunCallback, Object user) {

        PointerByReference str = new PointerByReference();
        XtStream stream = new XtStream(raw, streamCallback, xRunCallback, user);
        XtNative.Mix nativeMix = XtNative.Mix.toNative(mix);
        Pointer ds = new Memory(count * Native.POINTER_SIZE);
        Pointer cs = new Memory(count * Native.getNativeSize(XtNative.ChannelsByValue.class));
        for (int d = 0; d < count; d++) {
            ds.setPointer(d * Native.POINTER_SIZE, devices[d].d);
            channels[d].doUseMemory(cs, d * Native.getNativeSize(XtNative.ChannelsByValue.class));
            channels[d].write();
        }
        XtNative.handleError(XtNative.XtServiceAggregateStream(s, ds, cs, bufferSizes, count, nativeMix, interleaved, master.d,
                stream.nativeStreamCallback, xRunCallback == null ? null : stream.nativeXRunCallback, null, str));
        stream.init(str.getValue());
        return stream;
    }
}