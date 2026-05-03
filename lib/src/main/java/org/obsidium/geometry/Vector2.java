package org.obsidium.geometry;

public class Vector2 {
    public int x;
    public int y;

    public Vector2(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public Vector2 plus(Vector2 other) {
        return new Vector2(x + other.x, y + other.y);
    }
    public Vector2 minus(Vector2 other) {
        return new Vector2(x - other.x, y - other.y);
    }
    public Vector2 times(Vector2 other) {
        return new Vector2(x * other.x, y * other.y);
    }
    public static int dot(Vector2 firstVector2, Vector2 secondVector2) {
        return firstVector2.x * secondVector2.x + firstVector2.y * secondVector2.y;
    }
}
