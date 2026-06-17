package org.obsidium.math;

/**
 * A class that can be instantiated to hold 2 doubles that represent the coordinates {@code x} and {@code y}.
 * @since 1.0
 */
public class Vector2D {
    public double x;
    public double y;

    /**
     * The constructor of the {@link Vector2} class that stores the x and y coordinates in double form.
     * @param x the x-coordinate that needs to be stored
     * @param y the y-coordinate that needs to be stored
     * @since 1.0
     */
    public Vector2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
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
    public Vector2D plus(Vector2D other) {
        return new Vector2D(x + other.x, y + other.y);
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
    public Vector2D minus(Vector2D other) {
        return new Vector2D(x - other.x, y - other.y);
    }

    /**
     * This method multiplies the 2 specified vectors and returns the result.
     * 
     * @param other the second vector in the multiplication
     * 
     * @return the product of the 2 vectors
     * @since 1.0
     */
    public Vector2D times(Vector2D other) {
        return new Vector2D(x * other.x, y * other.y);
    }

    /**
     * Divides this vectors coordinates, by the other vectors coordinates.
     * <pre>{@code
     * newX = this.x / other.x
     * newY = this.x / other.y
     * }</pre>
     * @param other the denominator
     * @return the quotient vector
     * @since 1.2
     */
    public Vector2D divide(Vector2D other) { return new Vector2D(x / other.x, y / other.y); }

    /**
     * Computes the dot product of this vector and the specified vector.
     * @param firstVector2 the firs vector
     * @param secondVector2 the second vector
     * @return the scalar product of the 2 vectors
     * @since 1.0
     */
    public static double dot(Vector2D firstVector2, Vector2D secondVector2) {
        return firstVector2.x * secondVector2.x + firstVector2.y * secondVector2.y;
    }
}
