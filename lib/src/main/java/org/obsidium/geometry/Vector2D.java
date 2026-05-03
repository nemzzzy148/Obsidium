package org.obsidium.geometry;

public class Vector2D {
    public double x;
    public double y;

    public Vector2D(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public Vector2D plus(Vector2D other) {
        return new Vector2D(x + other.x, y + other.y);
    }
    public Vector2D minus(Vector2D other) {
        return new Vector2D(x - other.x, y - other.y);
    }
    public Vector2D times(Vector2D other) {
        return new Vector2D(x * other.x, y * other.y);
    }
    public static double dot(Vector2D firstVector2, Vector2D secondVector2) {
        return firstVector2.x * secondVector2.x + firstVector2.y * secondVector2.y;
    }
}
