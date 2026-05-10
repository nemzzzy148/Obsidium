package org.obsidium.graphics;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;

/**
 * A class with only static members that is used to transform images({@link Surface}).
 * 
 * Methods for transforming:
 * <ul>
 *  <li>{@link #scale(Surface, int, int)} - scales the surface to a set x and y coordinate.</li>
 *  <li>{@link #rotate(Surface, float, boolean)} - rotates the surface in degrees.</li>
 * </ul>
 * 
 * @since 1.0
 */
public class Transform {

    /**
     * Scales the surface to a set x and y coordinate.
     * 
     * @param surface the surface you want to scale
     * @param x the final width of the returned surface
     * @param y the final height of the returned surface
     * 
     * @return the scaled surface
     * 
     * @since 1.0
     */
    public static Surface scale(Surface surface, int x, int y) {
        BufferedImage original = surface.getBufferedImage();

        BufferedImage resized = new BufferedImage(x, y, original.getType());
        Graphics2D graphics2D = resized.createGraphics();
        graphics2D.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        graphics2D.drawImage(original, 0, 0, x, y, 0, 0, original.getWidth(), original.getHeight(), null);
        graphics2D.dispose();
        return new Surface(resized);
    }

    /**
     * Rotates the desired surface by a set angle.
     * 
     * <p> When the surface is returned, it most certainly will have a diffrent width and height.
     * This occurs because obbsidium keeps in account that when you rotate an image like for example by 45 degrees, the turned rectangle will be bigger.
     * An easier example is like turnining a paper by 45 degrees and than taking a photo of it, the edges will be cut of because your taking the image from the same viewpoint as the unrotated image.
     * This is called the bounding box effect. If you want to dissable this feature, use this method {@link #rotate(Surface, float, boolean)} with {@code scaleImage = false}.</p>
     * 
     * @see <a href="https://forum.affinity.serif.com/uploads/monthly_2018_08/1667706833_cropreset.JPG.6de9823bc4e6dd5f32e19081e2bd82c1.JPG">Visual reference</a>
     * 
     * @param surface the surface that needs to be rotated
     * @param deg the angle of rotation
     * 
     * @return {@link Surface} that is rotated
     * 
     * @since 1.0
     */
    public static Surface rotate(Surface surface, float deg) {
        return rotate(surface, deg, true);
    }

    /**
     * Rotates the desired surface by a set angle.
     * 
     * <p> When {@code scaleImage = true}, the surface that will be returned will most certainly have a diffrent width and height.
     * This occurs because obbsidium keeps in account that when you rotate an image like for example by 45 degrees, the turned rectangle will be bigger.
     * An easier example is like turnining a paper by 45 degrees and than taking a photo of it, the edges will be cut of because your taking the image from the same viewpoint as the unrotated image.
     * This is called the bounding box effect.
     * 
     * If it is disabled, the corners will likely be cut off.</p>
     * 
     * @see <a href="https://forum.affinity.serif.com/uploads/monthly_2018_08/1667706833_cropreset.JPG.6de9823bc4e6dd5f32e19081e2bd82c1.JPG">Visual reference</a>
     * 
     * @param surface the surface that needs to be rotated
     * @param deg the angle of rotation
     * @param scaleImage determines if the image can be resized
     * 
     * @return {@link Surface} that is rotated
     * 
     * @since 1.0
     */
    public static Surface rotate(Surface surface, float deg, boolean scaleImage) {
        double rads = Math.toRadians(deg);
        double sin = Math.abs(Math.sin(rads)), cos = Math.abs(Math.cos(rads));
        int w = surface.getWidth();
        int h = surface.getHeight();

        int newW = w;
        int newH = h;

        if (scaleImage) {
            newW = (int) Math.floor(w * cos + h * sin);
            newH = (int) Math.floor(h * cos + w * sin);
        }

        BufferedImage original = surface.getBufferedImage();
        BufferedImage rotated = new BufferedImage(newW, newH, original.getType());

        Graphics2D graphics2D = rotated.createGraphics();
        AffineTransform af = new AffineTransform();
        af.translate(newW/2, newW/2);
        af.rotate(rads);
        af.translate(-w / 2.0, -h / 2.0);

        graphics2D.setTransform(af);
        graphics2D.drawImage(original, 0, 0, null);
        graphics2D.dispose();
        
        return new Surface(rotated);
    }
}