package org.obsidium.graphics.shape;

import org.obsidium.graphics.Draw;
import org.obsidium.graphics.surface.SimpleSurface;

public class Rectangle extends Shape {
    public Rectangle(int width, int height) {
        super(width, height);
    }

    @Override
    public void draw(SimpleSurface surface, int x, int y) {
        Draw.rect(surface, x, y, width, height, color);
    }
}
