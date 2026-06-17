package org.obsidium.graphics.surface;

import org.obsidium.graphics.transform.BufferedTransform;
import org.obsidium.graphics.transform.Transform;
import org.obsidium.math.Vector2;
import org.obsidium.math.Vector4;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.*;

public class ExtendableSurface {
    // corners
    protected BufferedImage topLeft;
    protected BufferedImage topRight;
    protected BufferedImage bottomLeft;
    protected BufferedImage bottomRight;

    protected BufferedImage top;
    protected BufferedImage left;
    protected BufferedImage right;
    protected BufferedImage bottom;

    protected Color centerColor;

    private int cornerSize;

    // borders

    public ExtendableSurface(Surface surface, int cornerSize, Color centerColor) { init(surface, cornerSize, centerColor); }
    public ExtendableSurface(Surface surface) { init(surface, calculateCornerSize(surface.getWidth(), surface.getHeight()), Color.BLACK); }

    protected void init(Surface surface, int cornerSize, Color centerColor) {
        this.centerColor = centerColor;
        this.cornerSize = cornerSize;
        int w = surface.getWidth();
        int h = surface.getHeight();

        BufferedImage bI = surface.getBufferedImage();

        topLeft = BufferedTransform.strictCrop(bI, 0, 0 , cornerSize, cornerSize);
        topRight = BufferedTransform.strictCrop(bI, w - cornerSize, 0, w, cornerSize);
        bottomLeft = BufferedTransform.strictCrop(bI, 0, h - cornerSize, cornerSize, h);
        bottomRight = BufferedTransform.strictCrop(bI, w- cornerSize, h - cornerSize, w, h);

        top = bI.getSubimage(cornerSize, 0, w - (cornerSize*2), cornerSize);
        right = bI.getSubimage(w-cornerSize, cornerSize, cornerSize, h - (cornerSize * 2));
        bottom = bI.getSubimage(cornerSize, h - cornerSize, w - (cornerSize * 2), cornerSize);
        right = bI.getSubimage(w - cornerSize, cornerSize, cornerSize, h - (cornerSize * 2));
    }

    public BufferedImage getTopLeft() { return topLeft; }
    public void setTopLeft(BufferedImage topLeft) { this.topLeft = topLeft; }

    public BufferedImage getTopRight() { return topRight; }
    public void setTopRight(BufferedImage topRight) { this.topRight = topRight; }

    public BufferedImage getBottomLeft() { return bottomLeft; }
    public void setBottomLeft(BufferedImage bottomLeft) { this.bottomLeft = bottomLeft; }

    private static int calculateCornerSize(int width, int height) {
        return Math.min(width, height) / 2;
    }

    public void render(SimpleSurface surface, int x, int y, int width, int height) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor(centerColor);
        g2d.fillRect(x + cornerSize, y + cornerSize, width - (cornerSize * 2), height - (cornerSize * 2));

        g2d.drawImage(top, x + cornerSize, y, width - (cornerSize * 2), cornerSize, null);
        g2d.drawImage(bottom, x + cornerSize, y + height - cornerSize, width - (cornerSize * 2), cornerSize, null);
        g2d.drawImage(left, x, y + cornerSize, cornerSize, height - (cornerSize * 2), null);
        g2d.drawImage(right, x + width - cornerSize, y + cornerSize, cornerSize, height - (cornerSize * 2), null);

        g2d.drawImage(topLeft, x, y, null);
        g2d.drawImage(topRight, x + width - cornerSize, y, null);
        g2d.drawImage(bottomLeft, x, y + height - cornerSize, null);
        g2d.drawImage(bottomRight, x + width - cornerSize, y + height - cornerSize, null);
    }

    public Surface render(int width, int height) {
        Surface surface = new Surface(width, height);
        render(surface, 0, 0, width, height);

        return surface;
    }
}