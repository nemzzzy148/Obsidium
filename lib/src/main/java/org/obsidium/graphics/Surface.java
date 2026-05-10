package org.obsidium.graphics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * A class that represents an image.
 * 
 * @since 1.0
 */
public class Surface {
    private int width = 100;

    /**
     * Returns the width of the image in pixels.
     * 
     * @return the width
     * 
     * @since 1.0
     */
    public int getWidth() {
        return width;
    }

    private int height = 100;

    /**
     * Returns the height of the image in pixels.
     * 
     * @return the height
     * 
     * @since 1.0
     */
    public int getHeight() {
        return height;
    }

    private final BufferedImage bufferedImage;
    private final Graphics2D graphics2D;

    /**
     * Creates a surface with a set width an heigth.
     * 
     * @param width the width of the surface
     * @param height the height of the surface
     * 
     * @since 1.0
     */
    public Surface(int width, int height) {
        this.width = width;
        this.height = height;
        this.bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        this.graphics2D = this.bufferedImage.createGraphics();
    }

    /**
     * Creates a surface from a buffered image.
     * 
     * ---advanced---
     * 
     * <p> This is mostly used by obsidium to create surfaces in the process of transformation, or loading a surface from an image.
     * 
     * It automatically gets the width and height from the buffered image.</p>
     * 
     * @param bufferedImage
     * 
     * @since 1.0
     */
    public Surface(BufferedImage bufferedImage) {
        this.bufferedImage = bufferedImage;
        this.height = bufferedImage.getHeight();
        this.width = bufferedImage.getWidth();
        this.graphics2D = bufferedImage.createGraphics();
    }

    /**
     * Returns the drawing graphics used to draw things on this surface.
     * 
     * ---advanced---
     * 
     * @return {@link Graphics2D}
     * 
     * @since 1.0
     */
    public Graphics2D getGraphics2D() {
        return graphics2D;
    }

    /**
     * Frees some memory of the surface.
     * 
     * <p> Disposes of the drawing graphics. </p>
     * 
     * @since 1.0
     */
    public void dispose() {
        graphics2D.dispose();
    }

    /**
     * Returns the bufferd image of this surface.
     * 
     * ---advanced---
     * 
     * @return {@link Graphics2D}
     * 
     * @since 1.0
     */
    public BufferedImage getBufferedImage() {
        return bufferedImage;
    }

    /**
     * Blits a surface to this surface.
     * 
     * <p> This method is designed to be used for 'pasting' a surface onto this surface. 
     * For example, if you want to draw pieces of a map to this surface to later blit the assembly to the window. </p>
     * 
     * @param other the surface that you want to blit to this surface
     * @param x the x coordinate that specifies where you want the image to be blitted
     * @param y the y coordinate that specifies where you want the image to be blitted
     * 
     * @since 1.0
     */
    public void blit(Surface other, int x, int y) {
        if (other == null) return;
        graphics2D.drawImage(other.getBufferedImage(), null, x, y);
    }
}
