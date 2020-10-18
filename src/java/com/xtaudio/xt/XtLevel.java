package com.xtaudio.xt;

public enum XtLevel {

    INFO,
    ERROR,
    FATAL;

    @Override
    public String toString() {
        return XtPrint.levelToString(this);
    }
}