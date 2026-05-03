package org.obsidium.graphics;

public class Color {
    public int r = 0;
    public int g = 0;
    public int b = 0;
    public int a = 255;

    public Color(int r, int g, int b, int a) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }

    public Color(int r, int g, int b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }
    public Color() {}

    public static java.awt.Color awtColor(Color color) {
        return new java.awt.Color(color.r, color.g, color.b, color.a);
    }
}
