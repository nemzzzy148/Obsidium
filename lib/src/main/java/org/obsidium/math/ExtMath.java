package org.obsidium.math;

public final class ExtMath {
    public static byte clamp(byte value, byte min, byte max) {
        return max(min, min(value, max));
    }
    public static int clamp(int value, int min, int max) {
        return Math.max(min, Math.min(value, max));
    }

    public static long clamp(long value, long min, long max) {
        return Math.max(min, Math.min(value, max));
    }

    public static float clamp(float value, float min, float max) {
        return Math.max(min, Math.min(value, max));
    }

    public static double clamp(double value, double min, double max) {
        return Math.max(min, Math.min(value, max));
    }

    public static byte max(byte a, byte b) {
        return (a >= b) ? a : b;
    }

    public static byte min(byte a, byte b) {
        return (a <= b) ? a : b;
    }
}
