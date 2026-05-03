package org.obsidium.graphics;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;

public class Transform {
    public static Surface scale(Surface surface, int x, int y) {
        BufferedImage original = surface.getBufferedImage();
        // unstable dpi
        BufferedImage resized = new BufferedImage(x, y, original.getType());
        Graphics2D graphics2D = resized.createGraphics();
        graphics2D.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        graphics2D.drawImage(original, 0, 0, x, y, 0, 0, original.getWidth(), original.getHeight(), null);
        graphics2D.dispose();
        return new Surface(resized);
    }

    public static Surface rotate(Surface surface, float deg) {
        double rads = Math.toRadians(deg);
        double sin = Math.abs(Math.sin(rads)), cos = Math.cos(Math.cos(rads));
        int w = surface.getWidth();
        int h = surface.getHeight();

        int newW = (int) Math.floor(w * cos + h * sin);
        int newH = (int) Math.floor(h * cos + w * sin);

        BufferedImage original = surface.getBufferedImage();
        BufferedImage rotated = new BufferedImage(newW, newH, original.getType());

        Graphics2D graphics2D = rotated.createGraphics();
        AffineTransform tx = new AffineTransform();
        tx.translate(newW/2, newH/2);
        tx.rotate(rads);
        tx.translate(-w / 2.0, -h / 2.0);

        graphics2D.setTransform(tx);
        graphics2D.drawImage(original, 0, 0, null);
        graphics2D.dispose();
        
        return new Surface(rotated);
    }
}