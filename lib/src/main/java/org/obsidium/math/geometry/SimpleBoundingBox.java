package org.obsidium.math.geometry;

import org.obsidium.math.Vector2;

public class SimpleBoundingBox extends SimpleBox {
    public boolean insideBox(Vector2 point, Vector2 boxPosition) {
        return (point.x >= boxPosition.x &&
                point.y >= boxPosition.y &&
                point.x <= (boxPosition.x + width) &&
                point.y <= (boxPosition.y + height));
    }
    public SimpleBoundingBox(int width, int height) {
        this.height = height;
        this.width = width;
    }
}
