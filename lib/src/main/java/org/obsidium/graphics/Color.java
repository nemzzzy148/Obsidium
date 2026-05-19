package org.obsidium.graphics;

/**
 * A class that stores color values in integer form {@code 0-255}.
 * @since 1.0
 */
public class Color {
    /**
     * The value that represents the red component of this color.
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int r = 0;
    /**
     * The value that represents the green component of this color.
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int g = 0;
    /**
     * The value that represents the blue component of this color.
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int b = 0;
    /**
     * The value that represents the transparency of this color.
     * Between {@code 0 - 255}
     * 
     * @since 1.0
     */
    public int a = 255;

    /**
     * Creates a color object with the specified values.
     * <p>The allowed values for each component range from {@code 0 - 255}.
     * If these color values are out of the range, they will be clamped.</p>
     * 
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * @param a the transparency
     * 
     * @since 1.0
     */
    public Color(int r, int g, int b, int a) {
        setColor(r, g, b, a);
    }

    /**
     * Creates a color object with the specified values.
     * 
     * <p> The transparency will be set to {@code 255} (opaque) by default.</p>
     * <p>The allowed values for each component range from {@code 0 - 255}.
     * If these color values are out of the range, they will be clamped.</p>
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * 
     * @since 1.0
     */
    public Color(int r, int g, int b) {
        setColor(r, g, b, 255);
    }

    /**
     * Changes the r, g, b, a components of the color.
     *
     * <p>The allowed values for each component range from {@code 0 - 255}.
     * If these color values are out of the range, they will be clamped.</p>
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * @param a the transparency
     * @since 1.2
     */
    public void setColor(int r, int g, int b, int a) {
        this.r = Math.min(255, Math.max(r, 0));
        this.g = Math.min(255, Math.max(g, 0));
        this.b = Math.min(255, Math.max(b, 0));
        this.a = Math.min(255, Math.max(a, 0));
    }

    /**
     * Changes the r, g, b components of the color.
     *
     * <p>The allowed values for each component range from {@code 0 - 255}.
     * If these color values are out of the range, they will be clamped.</p>
     * @param r the red component
     * @param g the green component
     * @param b the blue component
     * @since 1.2
     */
    public void setColor(int r, int g, int b) {
        setColor(r, g, b, this.a);
    }

    /**
     * Creates a color object with the values:
     * <ul>
     *  <li>{@code r = 0}</li>
     *  <li>{@code g = 0}</li>
     *  <li>{@code b = 0}</li>
     *  <li>{@code a = 255} : transparency</li>
     * </ul>
     * 
     * <p>This will result in a black and opaque color.</p>
     * 
     * @since 1.0
     */
    public Color() {}

    /**
     * Turns the Obsidium color format into the AWT <b>Abstract Window Toolkit</b> color format.
     * <b>---advanced---</b>
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
