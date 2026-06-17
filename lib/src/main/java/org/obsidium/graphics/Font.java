package org.obsidium.graphics;

import org.obsidium.graphics.surface.SimpleSurface;
import org.obsidium.graphics.surface.Surface;

import java.awt.Canvas;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * A class that represents a font with methods to render text with this font.
 * Available built-in font types:
 * <ul>
 *  <li>{@code SERIF = 0}</li>
 *  <li>{@code SANSSERIF = 1}</li>
 *  <li>{@code MONOSPACED = 2}</li>
 *  <li>{@code DIALOG = 3}</li>
 *  <li>{@code DIALOGINPUT = 4}</li>
 * </ul>
 * @since 1.0
 */
public class Font {

    // build in fonts

    /** A built-in font type. 
     * @since 1.0*/
    public static final int SERIF = 0;

    /** A built-in font type. 
     * @since 1.0*/
    public static final int SANS_SERIF = 1;

    /** A built-in font type. 
     * @since 1.0*/
    public static final int MONOSPACED = 2;

    /** A built-in font type. 
     * @since 1.0*/
    public static final int DIALOG = 3;

    /** A built-in font type. 
     * @since 1.0*/
    public static final int DIALOG_INPUT = 4;

    private java.awt.Font font;

    // required vars

    private float size;

    /**
     * Sets the size of the font.
     * @param size of the font
     * @since 1.0
     */
    public void setSize(float size) {
        if (size < 1) return;
        font = font.deriveFont(size);
        this.size = size;
    }

    /**
     * Returns the font size.
     * @return {@code size}
     * @since 1.0
     */
    public float getSize() {
        return size;
    }

    private String path = "NO_PATH";

    /**
     * Returns the path of the font.
     * <p> If this is a custom font, it will return the path. Otherwise, it will return {@code NO_PATH}.</p>
     * @return {@code path}
     * @since 1.0
     */
    public String getPath() {
        return path;
    }

    private int type = -1;

    /**
     * Returns the type of font.
     * Available types:
     * <ul>
     *  <li>{@code SERIF = 0}</li>
     *  <li>{@code SANSSERIF = 1}</li>
     *  <li>{@code MONOSPACED = 2}</li>
     *  <li>{@code DIALOG = 3}</li>
     *  <li>{@code DIALOGINPUT = 4}</li>
     * </ul>
     * <p> This will return a valid type {@code 0 - 4} if it isn't a custom font, otherwise it will return 1.</p>
     * @return {@code type}
     * @since 1.0
     */
    public int getType() {
        return type;
    }

    /**
     * Creates a font of a .ttf file at the given path.
     * For built-in fonts use {@link #Font(int, float)}
     * @param path of the .ttf file
     * @param size of the font
     * @since 1.0
     */
    public Font(String path, float size) {
        this.path = path;
        this.size = size;

        Path filePath = Path.of(path);

        try(InputStream is = Files.newInputStream(filePath)) {
            this.font = java.awt.Font.createFont(java.awt.Font.TRUETYPE_FONT, is);
        } catch (Exception e) {
            System.err.println("Obsidium loading font error: " + e.getMessage());
        }

        assert this.font != null;
        this.font = this.font.deriveFont(size);
    }

    /**
     * Creates a font from a built-in type.
     * Available built-in font types:
     * <ul>
     *  <li>{@code SERIF = 0}</li>
     *  <li>{@code SANSSERIF = 1}</li>
     *  <li>{@code MONOSPACED = 2}</li>
     *  <li>{@code DIALOG = 3}</li>
     *  <li>{@code DIALOGINPUT = 4}</li>
     * </ul>
     * @param type of the font
     * @param size of the font
     * @since 1.0
     */
    public Font(int type, float size) {
        this.type = type < 0 || type > 4 ? 0 : type;
        this.size  = size < 1 ? 1 : size;

        String fontName = switch(this.type) {
            case SANS_SERIF -> java.awt.Font.SANS_SERIF;
            case MONOSPACED -> java.awt.Font.MONOSPACED;
            case DIALOG -> java.awt.Font.DIALOG;
            case DIALOG_INPUT -> java.awt.Font.DIALOG_INPUT;
            default -> java.awt.Font.SERIF;
        };

        this.font = new java.awt.Font(fontName, 1, (int)size);
    }

    /**
     * Renders the font on a new surface.
     * <p> The width and height will automatically be calculated. </p>
     * @param text that will be rendered
     * @param color of the text
     * @return {@link Surface}
     * @since 1.0
     */
    public Surface render(String text, Color color) {
        Canvas c = new Canvas();
        FontMetrics fm = c.getFontMetrics(font);

        int width = fm.stringWidth(text);
        int height = fm.getHeight();
        int ascent = fm.getAscent();

        Surface surface = new Surface(Math.max(1, width), Math.max(1, height));

        render(surface, 0, ascent, text, color);

        return surface;
    }

    /**
     * Renders the font on this surface / window.
     * @param surface that the text will be rendered too
     * @param x the x-coordinate where the text will be rendered to, relative to the surface
     * @param y the y-coordinate where the text will be rendered to, relative to the surface
     * @param text the text that will be rendered
     * @param color the color of the text
     * @since 1.0
     */
    public void render(SimpleSurface surface, int x, int y, String text, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setFont(font);
        g2d.setColor(Color.awtColor(color));

        g2d.drawString(text, x, y);
    }
}