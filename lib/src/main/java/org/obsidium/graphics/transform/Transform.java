package org.obsidium.graphics.transform;

import org.obsidium.graphics.surface.Surface;
import org.obsidium.math.ExtMath;
import org.obsidium.math.Vector2;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;

/**
 * A class with only static members that is used to transform images({@link Surface}).
 * Methods for transforming:
 * <ul>
 *  <li>{@link #scale(Surface, int, int)} - scales the surface to a set x and y coordinate.</li>
 *  <li>{@link #rotate(Surface, float, boolean)} - rotates the surface in degrees.</li>
 * </ul>
 * @since 1.0
 */
public final class Transform {

    /**
     * Scales the surface to a set x and y coordinate.
     * @param surface the surface you want to scale
     * @param x the final width of the returned surface
     * @param y the final height of the returned surface
     * @return the scaled surface
     * @since 1.0
     */
    public static Surface scale(Surface surface, int x, int y) {
        return new Surface(BufferedTransform.scale(surface.getBufferedImage(), x, y));
    }

    /**
     * Rotates the desired surface by a set angle.
     * <p> When the surface is returned, it most certainly will have a different width and height.
     * This occurs because Obsidium keeps in account that when you rotate an image like for example by 45 degrees, the turned rectangle will be bigger.
     * An easier example is like turning a paper by 45 degrees and then taking a photo of it, the edges will be cut of because your taking the image from the same viewpoint as the unrotated image.
     * This is called the bounding box effect. If you want to disable this feature, use this method {@link #rotate(Surface, float, boolean)} with {@code scaleImage = false}.</p>
     * @see <a href="https://forum.affinity.serif.com/uploads/monthly_2018_08/1667706833_cropreset.JPG.6de9823bc4e6dd5f32e19081e2bd82c1.JPG">Visual reference</a>
     * @param surface the surface that needs to be rotated
     * @param deg the angle of rotation
     * @return {@link Surface} that is rotated
     * @since 1.0
     */
    public static Surface rotate(Surface surface, float deg) {
        return rotate(surface, deg, true);
    }

    /**
     * Rotates the desired surface by a set angle.
     * <p> When {@code scaleImage = true}, the surface that will be returned will most certainly have a different width and height.
     * This occurs because Obsidium keeps in account that when you rotate an image like for example by 45 degrees, the turned rectangle will be bigger.
     * An easier example is like turning a paper by 45 degrees and then taking a photo of it, the edges will be cut of because your taking the image from the same viewpoint as the unrotated image.
     * This is called the bounding box effect.
     * If it is disabled, the corners will likely be cut off.</p>
     * @see <a href="https://forum.affinity.serif.com/uploads/monthly_2018_08/1667706833_cropreset.JPG.6de9823bc4e6dd5f32e19081e2bd82c1.JPG">Visual reference</a>
     * @param surface the surface that needs to be rotated
     * @param deg the angle of rotation
     * @param scaleImage determines if the image can be resized
     * @return {@link Surface} that is rotated
     * @since 1.0
     */
    public static Surface rotate(Surface surface, float deg, boolean scaleImage) {
        return new Surface(BufferedTransform.rotate(surface.getBufferedImage(), deg, scaleImage));
    }

    /**
     * Crops the surface.
     * <p>The given coordinates correspond to the coordinates in the original surface. If the given crop coordinates go outside the surface, then the rendered pixels outside that surface will become transparent.</p>
     * <p><b>Note:</b> The cropped surface can be bigger than the original surface.</p>
     * <pre>{@code
     * Returned surface:
     * #--------+
     * |        |
     * |        |
     * |        |
     * +--------@
     * # = top left
     * @ = bottom right
     * }</pre>
     * @param surface that needs to be cropped
     * @param topLeftX the top left x-coordinate of the returned surface
     * @param topLeftY the top left y-coordinate of the returned surface
     * @param bottomRightX the bottom right x-coordinate of the returned surface
     * @param bottomRightY the bottom right y-coordinate of the returned surface
     * @return {@link Surface} that has been cropped
     * @since 1.2
     */
    public static Surface crop(Surface surface, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        return new Surface(BufferedTransform.crop(surface.getBufferedImage(), topLeftX, topLeftY, bottomRightX, bottomRightY));
    }

    /**
     * Crops the surface.
     * <p>The given coordinates correspond to the coordinates in the original surface. If the given crop coordinates go outside the surface, then the rendered pixels outside that surface will become transparent.</p>
     * <p><b>Note:</b> The cropped area must fit entirely within the original surface. If you provide coordinates that fall outside the original surface, the program automatically pulls them back to the nearest valid edge. This ensures your crop never exceeds the original boundaries.</p>
     * <pre>{@code
     * Returned surface:
     * #--------+
     * |        |
     * |        |
     * |        |
     * +--------@
     * # = top left
     * @ = bottom right
     * }</pre>
     * @param surface that needs to be cropped
     * @param topLeftX the top left x-coordinate of the returned surface
     * @param topLeftY the top left y-coordinate of the returned surface
     * @param bottomRightX the bottom right x-coordinate of the returned surface
     * @param bottomRightY the bottom right y-coordinate of the returned surface
     * @return {@link Surface} that has been cropped
     * @since 1.2
     */
    public static Surface strictCrop(Surface surface, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        int w = surface.getWidth();
        int h = surface.getHeight();
        int tLX = ExtMath.clamp(topLeftX, 0, w);
        int tLY = ExtMath.clamp(topLeftY, 0, h);
        int bRX = ExtMath.clamp(bottomRightX, 0, w);
        int bRY = ExtMath.clamp(bottomRightY, 0, h);
        return crop(surface, tLX, tLY, bRX, bRY);
    }

    /**
     * Crops the surface.
     * <p>The given coordinates correspond to the coordinates in the original surface. If the given crop coordinates go outside the surface, then the rendered pixels outside that surface will become transparent.</p>
     * <p><b>Note:</b> The cropped area must fit entirely within the original surface. If you provide coordinates that fall outside the original surface, the program automatically pulls them back to the nearest valid edge. This ensures your crop never exceeds the original boundaries.</p>
     * <pre>{@code
     * Returned surface:
     * #--------+
     * |        |
     * |        |
     * |        |
     * +--------@
     * # = top left
     * @ = bottom right
     * }</pre>
     * @param surface that needs to be cropped
     * @param topLeft a vector containing the top left coordinated of the cropped surface
     * @param bottomRight a vector containing the bottom right coordinated of the cropped surface
     * @return {@link Surface} that has been cropped
     * @since 1.2
     */
    public static Surface strictCrop(Surface surface, Vector2 topLeft, Vector2 bottomRight) {
        return strictCrop(surface, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }

    /**
     * Crops the surface.
     * <p>The given coordinates correspond to the coordinates in the original surface. If the given crop coordinates go outside the surface, then the rendered pixels outside that surface will become transparent.</p>
     * <p><b>Note:</b> The cropped surface can be bigger than the original surface.</p>
     * <pre>{@code
     * Returned surface:
     * #--------+
     * |        |
     * |        |
     * |        |
     * +--------@
     * # = top left
     * @ = bottom right
     * }</pre>
     * @param surface that needs to be cropped
     * @param topLeft a vector containing the top left coordinated of the cropped surface
     * @param bottomRight a vector containing the bottom right coordinated of the cropped surface
     * @return {@link Surface} that has been cropped
     * @since 1.2
     */
    public static Surface crop(Surface surface, Vector2 topLeft, Vector2 bottomRight) {
        return crop(surface, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }
}