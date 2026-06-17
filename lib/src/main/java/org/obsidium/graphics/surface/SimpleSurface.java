package org.obsidium.graphics.surface;

import org.obsidium.math.Vector2;

import java.awt.*;

public class SimpleSurface {
    protected Graphics2D graphics2D;
    protected int width = 100;
    protected int height = 100;

    /**
     * <b>---advanced---</b>
     * Returns the window's / surface's {@code Graphics2D}.
     * <p> Only use this if you know what you are doing </p>
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return Graphics2D
     * @since 1.0
     */
    public Graphics2D getGraphics2D() { return graphics2D; }

    /**
     * Returns the width of the surface/window in pixels.
     * @return the width
     * @since 1.2
     */
    public int getWidth() {
        return width;
    }

    /**
     * Returns the height of the surface / window in pixels.
     * @return the height
     * @since 1.2
     */
    public int getHeight() {
        return height;
    }

    /**
     * Returns the window's / surface's dimensions in {@link Vector2} form.
     * @return {@link Vector2} that contains the dimensions
     * @since 1.2
     */
    public Vector2 getSize() {
        return new Vector2(this.width, this.height);
    }

    protected int clampX(int x) {
        return Math.max(0, Math.min(x, width));
    }
    protected int clampY(int y) {
        return Math.max(0, Math.min(y, height));
    }

    public void setRenderingHints() {

    }

    /**
     * Blits a surface to this surface / window.
     * <p> This method is designed to be used for 'pasting' a surface onto this surface / window.
     * For example, if you want to draw pieces of a map to this surface to later blit the assembly to the surface / window. </p>
     * @param other the surface that you want to blit to this surface / window
     * @param x the x coordinate that specifies where you want the image to be blitted
     * @param y the y coordinate that specifies where you want the image to be blitted
     * @since 1.0
     */
    public void blit(Surface other, int x, int y) {
        if (other == null) return;
        graphics2D.drawImage(other.getBufferedImage(), null, x, y);
    }
}
