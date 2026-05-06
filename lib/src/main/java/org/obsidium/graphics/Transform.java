package org.obsidium.graphics;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;

public class Transform {
    public static Surface scale(Surface surface, int x, int y) {
        BufferedImage original = surface.getBufferedImage();

        // unstable dpi FUCK YOU AWT!!! Bug i think hmmmm???

        BufferedImage resized = new BufferedImage(x, y, original.getType());
        Graphics2D graphics2D = resized.createGraphics();
        graphics2D.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        graphics2D.drawImage(original, 0, 0, x, y, 0, 0, original.getWidth(), original.getHeight(), null);
        graphics2D.dispose();
        return new Surface(resized);
    }
    public static Surface rotate(Surface surface, float deg) {
        return rotate(surface, deg, true);
    }

    public static Surface rotate(Surface surface, float deg, boolean scaleImage) {
        // THIS IS HARD i got this off a stack overflow form but doesn't work correctly???

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
        BufferedImage rotated = new BufferedImage(newW, newH, original.getType()); // new new 

        Graphics2D graphics2D = rotated.createGraphics();
        AffineTransform af = new AffineTransform();
        af.translate(newW/2, newW/2); // new new
        af.rotate(rads);
        af.translate(-w / 2.0, -h / 2.0);

        graphics2D.setTransform(af);
        graphics2D.drawImage(original, 0, 0, null);
        graphics2D.dispose();
        
        return new Surface(rotated);
    }
}