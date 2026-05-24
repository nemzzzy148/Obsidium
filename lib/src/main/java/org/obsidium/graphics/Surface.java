package org.obsidium.graphics;

import java.awt.image.BufferedImage;

/**
 * A class that represents an image.
 * @since 1.0
 */
public class Surface extends SimpleSurface{
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
