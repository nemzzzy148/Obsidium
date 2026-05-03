package org.obsidium.graphics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public class Surface {
    private int width = 100;

    public int getWidth() {
        return width;
    }

    private int height = 100;

    public int getHeight() {
        return height;
    }

    private final BufferedImage bufferedImage;
    private final Graphics2D graphics2D;

    public Surface(int width, int height) {
        this.width = width;
        this.height = height;
        this.bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        this.graphics2D = this.bufferedImage.createGraphics();
    }
    public Surface(BufferedImage bufferedImage) {
        this.bufferedImage = bufferedImage;
        this.height = bufferedImage.getHeight();
        this.width = bufferedImage.getWidth();
        this.graphics2D = bufferedImage.createGraphics();
    }

    public Graphics2D getGraphics2D() {
        return graphics2D;
    }
    public void dispose() {
        graphics2D.dispose();
    }
    public BufferedImage getBufferedImage() {
        return bufferedImage;
    }
    public void blit(Surface other, int x, int y) {
        if (other == null) return;
        graphics2D.drawImage(other.getBufferedImage(), null, x, y);
    }
}
