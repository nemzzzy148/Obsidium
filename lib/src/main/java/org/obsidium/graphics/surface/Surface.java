package org.obsidium.graphics.surface;

import org.obsidium.graphics.Color;
import org.obsidium.math.Vector2;

import java.awt.*;
import java.awt.image.BufferedImage;

/**
 * A class that represents an image.
 * @since 1.0
 */
public class Surface extends SimpleSurface {
    private BufferedImage bufferedImage;

    /**
     * Returns the buffered image of this surface.
     * <b>---advanced---</b>
     * @return {@link Graphics2D}
     * @since 1.0
     */
    public BufferedImage getBufferedImage() {
        return bufferedImage;
    }

    /**
     * Returns the pixels color at the given coordinate.
     * <p>If the given x or y coordinates exceed the width/height or is below 0, it will be clamped.</p>
     * <p>In this instance clamped reefers to that a given value that is below 0 will be set to 0, or a value larger than the width or height will be set to the width or height.</p>
     * @param x the x-coordinate where the pixel is found
     * @param y the y-coordinate where the pixel is found
     * @return {@link org.obsidium.graphics.Color} of the pixel
     * @since 1.2
     */
    public org.obsidium.graphics.Color getPixel(int x, int y) {
        int v = getBufferedImage().getRGB(clampX(x), clampY(y));
        return org.obsidium.graphics.Color.awtRGBAColor(v);
    }

    /**
     * Returns the pixels color at the given coordinate.
     * <p>If the given x or y coordinates exceed the width/height or is below 0, it will be clamped.</p>
     * <p>In this instance clamped reefers to that a given value that is below 0 will be set to 0, or a value larger than the width or height will be set to the width or height.</p>
     * @param position where the pixel can be found
     * @return {@link org.obsidium.graphics.Color} of the specific pixel
     * @since 1.2
     */
    public org.obsidium.graphics.Color getPixel(Vector2 position) {
        return getPixel(position.x, position.y);
    }

    public void setPixel(int x, int y, org.obsidium.graphics.Color color) {
        int v = color.b | (color.g << 8) | (color.r << 16) | (color.a << 24);
        getBufferedImage().setRGB(clampX(x), clampY(y), v);
    }
    public void setPixel(Vector2 position, Color color) {
        setPixel(position.x, position.y, color);
    }

    /**
     * Creates a surface with a set width a height.
     * @param width the width of the surface
     * @param height the height of the surface
     * @since 1.0
     */
    public Surface(int width, int height) {
        this.width = width;
        this.height = height;
        bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        graphics2D = this.bufferedImage.createGraphics();
    }

    /**
     * Creates a surface from a buffered image.
     * <b>---advanced---</b>
     * <p> This is mostly used by obsidium to create surfaces in the process of transformation, or loading a surface from an image.
     * It automatically gets the width and height from the buffered image.</p>
     * @param bufferedImage that will be converted into a {@link java.awt.image.BufferedImage}
     * @since 1.0
     */
    public Surface(BufferedImage bufferedImage) {
        this.bufferedImage = bufferedImage;
        this.height = bufferedImage.getHeight();
        this.width = bufferedImage.getWidth();
        graphics2D = bufferedImage.createGraphics();
    }

    /**
     * Frees some memory of the surface.
     * <p> Disposes of the drawing graphics. </p>
     * @since 1.0
     */
    public void dispose() {
        graphics2D.dispose();
    }
}
