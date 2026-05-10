package org.obsidium.geometry;

/**
 * A class that can be instantiated to hold 2 integers that represent the coordinates {@code x} and {@code y}.
 * 
 * @since 1.0
 */
public class Vector2 {
    public int x;
    public int y;

    /**
     * The constructor of the {@link Vector2} class that stores the x and y coordinates in integer form.
     * 
     * @param x the x-coordinate that needs to be stored
     * @param y the y-coordinate that needs to be stored
     * 
     * @since 1.0
     */
    public Vector2(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * This method adds the 2 specified vectors and returns the result.
     * 
     * @param other the second vector in the addition
     * 
     * @return the sum of the 2 vectors
     * 
     * @since 1.0
     */
    public Vector2 plus(Vector2 other) {
        return new Vector2(x + other.x, y + other.y);
    }

    /**
     * This method subtracts the 2 specified vectors and returns the result.
     * 
     * @param other the second vector in the subtracts
     * 
     * @return the difference of the 2 vectors
     * 
     * @since 1.0
     */
    public Vector2 minus(Vector2 other) {
        return new Vector2(x - other.x, y - other.y);
    }

    /**
     * This method multiplies the 2 specified vectors and returns the result.
     * 
     * @param other the second vector in the multiplication
     * 
     * @return the procuct of the 2 vectors
     * 
     * @since 1.0
     */
    public Vector2 times(Vector2 other) {
        return new Vector2(x * other.x, y * other.y);
    }

    /**
     * Computes the dot product of this vector and the specified vector.
     * 
     * @param firstVector2 the firs vector
     * @param secondVector2 the second vector
     * 
     * @return the scalar product of the 2 vectors
     * 
     * @since 1.0
     */
    public static int dot(Vector2 firstVector2, Vector2 secondVector2) {
        return firstVector2.x * secondVector2.x + firstVector2.y * secondVector2.y;
    }
}
