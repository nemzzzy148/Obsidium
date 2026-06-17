package org.obsidium.graphics.shape;

import org.obsidium.graphics.Color;
import org.obsidium.graphics.surface.SimpleSurface;

import java.util.Random;

public abstract class Shape {
    public Color color = Color.WHITE;
    protected int height;
    protected int width;

    public Shape(int width, int height) {
        this.height = height;
        this.width = width;
    }

    public Color getColor() { return color; }
    public void setColor(Color color) { this.color = color; }

    public int getWidth() { return width; }
    public void setWidth(int width) { this.width = width; }

    public int getHeight() { return height; }
    public void setHeight(int height) { this.height = height; }

    public abstract void draw(SimpleSurface surface, int x, int y);
}
