package org.obsidium.graphics;

import java.awt.Canvas;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class Font {

    // build in fonts

    public static final int SERIF = 0;
    public static final int SANSSERIF = 1;
    public static final int MONOSPACED = 2;
    public static final int DIALOG = 3;
    public static final int DIALOGINPUT = 4;

    private java.awt.Font font;

    // required vars

    private float size;

    public void setSize(float size) {
        if (size < 1) return;
        font = font.deriveFont(size);
    }

    public float getSize() {
        return size;
    }

    private String path = "NO_PATH";

    public String getPath() {
        return path;
    }

    private int type = -1;

    public int getType() {
        return type;
    }

    public Font(String path, float size) {
        this.path = path;
        this.size = size;

        Path filePath = Path.of(path);

        try(InputStream is = Files.newInputStream(filePath)) {
            this.font = java.awt.Font.createFont(java.awt.Font.TRUETYPE_FONT, is);
        } catch (Exception e) {
            System.err.println("Obsidium loading font error: " + e.getMessage());
        }

        this.font = this.font.deriveFont(size);
    }
    public Font(int type, float size) {
        this.type = type < 0 || type > 4 ? 0 : type;
        this.size  = size < 1 ? 1 : size;

        String fontName = switch(this.type) {
            case SERIF -> java.awt.Font.SERIF;
            case SANSSERIF -> java.awt.Font.SANS_SERIF;
            case MONOSPACED -> java.awt.Font.MONOSPACED;
            case DIALOG -> java.awt.Font.DIALOG;
            case DIALOGINPUT -> java.awt.Font.DIALOG_INPUT;
            default -> java.awt.Font.SERIF;
        };

        this.font = new java.awt.Font(fontName, 1, (int)size);
    }

    public Surface render(String text, Color color) {
        Canvas c = new Canvas();
        FontMetrics fm = c.getFontMetrics(font);

        int width = fm.stringWidth(text);
        int height = fm.getHeight();
        int ascent = fm.getAscent();

        Surface surface = new Surface(Math.max(1, width), Math.max(1, height));

        renderOntoGraphics2D(surface.getGraphics2D(), 0, ascent, text, color);

        return surface;
    }
    public void render(Surface surface, int x, int y, String text, Color color) {
        renderOntoGraphics2D(surface.getGraphics2D(), x, y, text, color);
    }
    public void render(org.obsidium.Window window, int x, int y, String text, Color color) {
        renderOntoGraphics2D(window.getGraphics2D(), x, y, text, color);
    }
    private void renderOntoGraphics2D(Graphics2D graphics2D, int x, int y, String text, Color color) {
        graphics2D.setFont(font);
        graphics2D.setColor(Color.awtColor(color));

        graphics2D.drawString(text, x, y);
    }
}