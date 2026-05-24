package org.obsidium.graphics;

import org.obsidium.math.Vector2;

import java.awt.*;
import java.awt.image.BufferedImage;

public class SimpleSurface {
    protected BufferedImage bufferedImage;

    /**
     * Returns the buffered image of this window's / surface's.
     * <b>---advanced---</b>
     * @return {@link Graphics2D}
     * @since 1.0
     */
    public BufferedImage getBufferedImage() {
        return bufferedImage;
    }

    protected Graphics2D graphics2D;

    /**
     * <b>---advanced---</b>
     * Returns the window's / surface's {@code Graphics2D}.
     * <p> Only use this if you know what you are doing </p>
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return Graphics2D
     * @since 1.0
     */
    public Graphics2D getGraphics2D() { return graphics2D; }


    protected int width = 100;

    /**
     * Returns the width of the surface/window in pixels.
     * @return the width
     * @since 1.2
     */
    public int getWidth() {
        return width;
    }

    protected int height = 100;

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

    /**
     * Returns the pixels color at the given coordinate.
     * <p>If the given x or y coordinates exceed the width/height or is below 0, it will be clamped.</p>
     * <p>In this instance clamped reefers to that a given value that is below 0 will be set to 0, or a value larger than the width or height will be set to the width or height.</p>
     * @param x the x-coordinate where the pixel is found
     * @param y the y-coordinate where the pixel is found
     * @return {@link Color} of the pixel
     * @since 1.2
     */
    public Color getPixel(int x, int y) {
        int v = getBufferedImage().getRGB(clampX(x), clampY(y));
        return Color.awtRGBAColor(v);
    }

    /**
     * Returns the pixels color at the given coordinate.
     * <p>If the given x or y coordinates exceed the width/height or is below 0, it will be clamped.</p>
     * <p>In this instance clamped reefers to that a given value that is below 0 will be set to 0, or a value larger than the width or height will be set to the width or height.</p>
     * @param position where the pixel can be found
     * @return {@link Color} of the specific pixel
     * @since 1.2
     */
    public Color getPixel(Vector2 position) {
        return getPixel(position.x, position.y);
    }

    public void setPixel(int x, int y, Color color) {
        int v = color.b | (color.g << 8) | (color.r << 16) | (color.a << 24);
        getBufferedImage().setRGB(clampX(x), clampY(y), v);
    }
    public void setPixel(Vector2 position, Color color) {
        setPixel(position.x, position.y, color);
    }

    protected int clampX(int x) {
        return Math.max(0, Math.min(x, width));
    }
    protected int clampY(int y) {
        return Math.max(0, Math.min(y, height));
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

    protected void newFrame() {
        if (bufferedImage != null) bufferedImage.flush();
        if (graphics2D != null) graphics2D.dispose();
        bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        graphics2D = bufferedImage.createGraphics();
    }
}
