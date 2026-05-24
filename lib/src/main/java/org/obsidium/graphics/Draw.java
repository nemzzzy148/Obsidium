package org.obsidium.graphics;

import java.awt.*;

import org.obsidium.window.Window;

/**
 * A class with only static members that is used for drawing shapes to the window or a surface.
 * @since 1.0
 */
public class Draw {
    /**
     * Fills the window / surface with a specified color.
     * @param surface where will be drawn to
     * @param color that will cover the source
     * @since 1.0
     */
    public static void fill(SimpleSurface surface, Color color) {
        Graphics2D graphics2D = surface.getGraphics2D();
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillRect(0, 0, surface.width, surface.height);
    }

    /**
     * Draws a rectangle on the surface / window.
     * @param surface where will be drawn to
     * @param x the x-coordinate, relative to the surface, where you want to draw the rectangle 
     * @param y the y-coordinate, relative to the surface, where you want to draw the rectangle 
     * @param width the width of the rectangle
     * @param height the height of the rectangle
     * @param color the color of the rectangle
     * @since 1.0
     */
    public static void rect(SimpleSurface surface,  int x, int y, int width, int height, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor( Color.awtColor(color) );
        g2d.fillRect(x, y, width, height);
    }

    /**
     * Draws the outline of a rectangle onto the surface / window.
     * @param surface where it will be drawn on
     * @param x the x-coordinate, relative to the surface, where will be drawn to
     * @param y the y-coordinate, relative to the surface, where will be drawn to
     * @param width the width of the rectangle
     * @param height the height of the rectangle
     * @param thickness the thickness of the outline
     * @param color the color of the rectangle's outline
     * @since 1.2
     */
    public static void rectOutline(SimpleSurface surface, int x, int y, int width, int height, float thickness, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor( Color.awtColor(color) );
        g2d.drawRect(x, y, width, height);
    }

    /**
     * Draws a circle on the surface / window.
     * @param surface where will be drawn to
     * @param x the x-coordinate, relative to the window, where you want to draw the circle
     * @param y the y-coordinate, relative to the window, where you want to draw the circle 
     * @param r the radius of the circle
     * @param color the color of the circle
     * @since 1.0
     */
    public static void circle(SimpleSurface surface, int x, int y, int r, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor( Color.awtColor(color) );
        g2d.fillOval(x, y, r, r);
    }

    /**
     * Draws an oval onto the surface / window.
     * @param surface where is being drawn to
     * @param x the x-coordinate, relative to the window, where you want to draw the oval
     * @param y the y-coordinate, relative to the window, where you want to draw the oval
     * @param width the width of the oval
     * @param height the height of the oval
     * @param color the color of the oval
     * @since 1.2
     */
    public static void oval(SimpleSurface surface, int x, int y, int width, int height, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor(Color.awtColor(color));
        g2d.fillOval(x, y, width, height);
    }

    /**
     * Draws a filled in polygon on the surface / window.
     * <p> The amount of x-coordinates of the points have to match to amount of y-coordinates. </p>
     * @param surface where will be drawn to
     * @param xPoints the x-coordinates of the points where the x-coordinates are relative to the surface
     * @param yPoints the y-coordinates of the points where the y-coordinates are relative to the surface
     * @param color the color of the polygon
     * @since 1.0
     */
    public static void polygon(SimpleSurface surface, int[] xPoints, int[] yPoints, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setColor( Color.awtColor(color));
        g2d.fillPolygon(xPoints, yPoints, xPoints.length);
    }

    /**
     * Draws a line to the surface / window with a thickness of 1.
     * @param surface where will be drawn to
     * @param x1 the first x-coordinate that is relative to the surface
     * @param y1 the first y-coordinate that is relative to the surface
     * @param x2 the second x-coordinate that is relative to the surface
     * @param y2 the second y-coordinate that is relative to the surface
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(SimpleSurface surface, int x1, int y1, int x2, int y2, Color color) {
        line(surface, x1, y1, x2, y2, 1.0f, color);
    }

    /**
     * Draws a line to the surface / window.
     * @param surface where will be drawn to
     * @param x1 the first x-coordinate that is relative to the surface
     * @param y1 the first y-coordinate that is relative to the surface
     * @param x2 the second x-coordinate that is relative to the surface
     * @param y2 the second y-coordinate that is relative to the surface
     * @param thickness the thickness of the line in pixels
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(SimpleSurface surface, int x1, int y1, int x2, int y2, float thickness, Color color) {
        Graphics2D g2d = surface.getGraphics2D();
        g2d.setStroke(new BasicStroke(thickness));
        g2d.setColor( Color.awtColor(color) );
        g2d.drawLine(x1, y1, x2, y2);
    }
}