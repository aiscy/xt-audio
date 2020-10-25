package com.xtaudio.xt.sample;

import static com.xtaudio.xt.NativeTypes.*;
import com.xtaudio.xt.XtAudio;
import com.xtaudio.xt.XtException;

public class Sample {

    public static void main(String[] args) throws Exception {
        int index = -1;
        if (args.length == 1) {
            index = Integer.parseInt(args[0]);
        }
        try {
            if (index == -1 || index == 0) {
                System.out.println("PrintSimple:");
                PrintSimple.main(args);
            }
            if (index == -1 || index == 1) {
                System.out.println("PrintDetailed:");
                PrintDetailed.main(args);
            }
            if (index == -1 || index == 2) {
                System.out.println("CaptureSimple:");
                CaptureSimple.main(args);
            }
            if (index == -1 || index == 3) {
                System.out.println("RenderSimple:");
                RenderSimple.main(args);
            }
            if (index == -1 || index == 4) {
                System.out.println("CaptureAdvanced:");
                CaptureAdvanced.main(args);
            }
            if (index == -1 || index == 5) {
                System.out.println("RenderAdvanced:");
                RenderAdvanced.main(args);
            }
            if (index == -1 || index == 6) {
                System.out.println("FullDuplex:");
                FullDuplex.main(args);
            }
            if (index == -1 || index == 7) {
                System.out.println("Aggregate:");
                Aggregate.main(args);
            }
        } catch (XtException e) {
            XtErrorInfo info = XtAudio.getErrorInfo(e.getError());
            System.out.println("Error:");
            System.out.println("\tSystem: " +info.system);
            System.out.println("\tCause: " + info.cause);
            System.out.println("\tFault: " + info.fault);
            System.out.println("\tText: " + info.text);
            e.printStackTrace();
        }
    }
}