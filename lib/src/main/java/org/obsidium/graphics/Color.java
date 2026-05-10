package org.obsidium.graphics;

/**
 * A class that stores color values in integer form {@code 0-255}.
 * 
 * @since 1.0
 */
public class Color {
    /**
     * The value that represents the red component of this color.
     * 
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int r = 0;
    /**
     * The value that represents the green component of this color.
     * 
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int g = 0;
    /**
     * The value that represents the blue component of this color.
     * 
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int b = 0;
    /**
     * The value that represents the transparency of this color.
     * 
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int a = 255;

    /**
     * Creates a color object with the specified values.
     * 
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * @param a the transparency
     * 
     * @since 1.0
     */
    public Color(int r, int g, int b, int a) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }

    /**
     * Creates a color object with the specified values.
     * 
     * <p> The trancparency will be set to {@code 255} (opaque) by default.</p>
     * 
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * 
     * @since 1.0
     */
    public Color(int r, int g, int b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    /**
     * Creates a color object with the values:
     * <ul>
     *  <li>{@code r = 0}</li>
     *  <li>{@code g = 0}</li>
     *  <li>{@code b = 0}</li>
     *  <li>{@code a = 255} : opague</li>
     * </ul>
     * 
     * <p>This will result in a black and opaque color.</p>
     * 
     * @since 1.0
     */
    public Color() {}

    /**
     * Turns the Obsidium color format into the AWT <b>Abstract Window Toolkit</b> color format.
     * 
     * ---advanced---
     * 
     * <p> This method is primarily used by obsidium itself, but can be used to extend the functionality of obsidium.</p>
     * 
     * @param color that needs to be converted
     * 
     * @return {@link java.awt.Color}
     * 
     * @since 1.0
     */
    public static java.awt.Color awtColor(Color color) {
        return new java.awt.Color(color.r, color.g, color.b, color.a);
    }
}
