package org.obsidium.graphics.transform;

import org.obsidium.graphics.surface.Surface;
import org.obsidium.math.ExtMath;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;

public final class BufferedTransform {
    public static BufferedImage scale(BufferedImage original, int x, int y) {
        BufferedImage resized = new BufferedImage(x, y, original.getType());
        Graphics2D graphics2D = resized.createGraphics();
        graphics2D.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        graphics2D.drawImage(original, 0, 0, x, y, 0, 0, original.getWidth(), original.getHeight(), null);
        graphics2D.dispose();
        return resized;
    }

    public static BufferedImage rotate(BufferedImage original, float deg, boolean scaleImage) {
        double rads = Math.toRadians(deg);
        double sin = Math.abs(Math.sin(rads)), cos = Math.abs(Math.cos(rads));
        int w = original.getWidth();
        int h = original.getHeight();

        int newW = w;
        int newH = h;

        if (scaleImage) {
            newW = (int) Math.floor(w * cos + h * sin);
            newH = (int) Math.floor(h * cos + w * sin);
        }

        BufferedImage rotated = new BufferedImage(newW, newH, original.getType());

        Graphics2D graphics2D = rotated.createGraphics();
        AffineTransform af = new AffineTransform();
        af.translate(newW/2, newH/2);
        af.rotate(rads);
        af.translate(-w / 2.0, -h / 2.0);

        graphics2D.setTransform(af);
        graphics2D.drawImage(original, 0, 0, null);
        graphics2D.dispose();

        return rotated;
    }

    public static BufferedImage crop(BufferedImage original, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        BufferedImage cropped = new BufferedImage(bottomRightX - topLeftX, bottomRightY - topLeftY, original.getType());
        Graphics2D g2d = cropped.createGraphics();

        g2d.drawImage(cropped, null, -topLeftX, -topLeftY);
        g2d.dispose();

        return cropped;
    }

    public static BufferedImage strictCrop(BufferedImage original, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        int w = original.getWidth();
        int h = original.getHeight();
        int tLX = ExtMath.clamp(topLeftX, 0, w);
        int tLY = ExtMath.clamp(topLeftY, 0, h);
        int bRX = ExtMath.clamp(bottomRightX, 0, w);
        int bRY = ExtMath.clamp(bottomRightY, 0, h);
        return crop(original, tLX, tLY, bRX, bRY);
    }
}
