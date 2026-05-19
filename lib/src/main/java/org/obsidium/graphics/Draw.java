package org.obsidium.graphics;

import java.awt.*;

import org.obsidium.window.Window;

/**
 * A class with only static members that is used for drawing shapes to the window or a surface.
 * @since 1.0
 */
public class Draw {
    /**
     * Fills the window with a specified color.
     * @param window where will be drawn to
     * @param color that will cover the window
     * @since 1.0
     */
    public static void fill(Window window, Color color) {
        gFill(window.getGraphics2D(), window.getWidth(), window.getHeight(), color);
    }
    /**
     * Fills the surface with a specified color.
     * @param surface where will be drawn to
     * @param color that will cover the surface
     * @since 1.0
     */
    public static void fill(Surface surface, Color color) {
        gFill(surface.getGraphics2D(), surface.getWidth(), surface.getHeight(), color);
    }

    private static void gFill(Graphics2D graphics2D, int width, int height, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillRect(0, 0, width, height);
    }



    /**
     * Draws a rectangle on the window.
     * @param window where will be drawn to
     * @param x the x-coordinate, relative to the window, where you want to draw the rectangle 
     * @param y the y-coordinate, relative to the window, where you want to draw the rectangle 
     * @param width the width of the rectangle
     * @param height the height of the rectangle
     * @param color the color of the rectangle
     * @since 1.0
     */
    public static void rect(Window window, int x, int y, int width, int height, Color color) {
        gRect(window.getGraphics2D(), x, y, width, height, color);
    }

    /**
     * Draws a rectangle on the surface.
     * @param surface where will be drawn to
     * @param x the x-coordinate, relative to the surface, where you want to draw the rectangle 
     * @param y the y-coordinate, relative to the surface, where you want to draw the rectangle 
     * @param width the width of the rectangle
     * @param height the height of the rectangle
     * @param color the color of the rectangle
     * @since 1.0
     */
    public static void rect(Surface surface, int x, int y, int width, int height, Color color) {
        gRect(surface.getGraphics2D(), x, y, width, height, color);
    }

    private static void gRect(Graphics2D graphics2D,  int x, int y, int width, int height, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillRect(x, y, width, height);
    }



    /**
     * Draws a circle on the window.
     * @param window where will be drawn to
     * @param x the x-coordinate, relative to the window, where you want to draw the circle
     * @param y the y-coordinate, relative to the window, where you want to draw the circle 
     * @param r the radius of the circle
     * @param color the color of the circle
     * @since 1.0
     */
    public static void circle(Window window, int x, int y, int r, Color color) {
        gCircle(window.getGraphics2D(), x, y, r, color);
    }

    /**
     * Draws a circle on the surface.
     * @param surface where will be drawn to
     * @param x the x-coordinate, relative to the surface, where you want to draw the circle
     * @param y the y-coordinate, relative to the surface, where you want to draw the circle 
     * @param r the radius of the circle
     * @param color the color of the circle
     * @since 1.0
     */
    public static void circle(Surface surface, int x, int y, int r, Color color) {
        gCircle(surface.getGraphics2D(), x, y, r, color);
    }

    private static void gCircle(Graphics2D graphics2D, int x, int y, int r, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillOval(x, y, r, r);
    }

    /**
     * Draws an oval onto the window.
     * @param window where is being drawn to
     * @param x the x-coordinate, relative to the window, where you want to draw the oval
     * @param y the y-coordinate, relative to the window, where you want to draw the oval
     * @param width the width of the oval
     * @param height the height of the oval
     * @param color the color of the oval
     * @since 1.2
     */
    public static void oval(Window window, int x, int y, int width, int height, Color color) {
        gOval(window.getGraphics2D(), x, y, width, height, color);
    }

    /**
     * Draws an oval onto the surface.
     * @param surface where is being drawn to
     * @param x the x-coordinate, relative to the surface, where you want to draw the oval
     * @param y the y-coordinate, relative to the surface, where you want to draw the oval
     * @param width the width of the oval
     * @param height the height of the oval
     * @param color the color of the oval
     * @since 1.2
     */
    public static void oval(Surface surface, int x, int y, int width, int height, Color color) {
        gOval(surface.getGraphics2D(), x, y, width, height, color);
    }

    private static void gOval(Graphics2D g2d, int x, int y, int width, int height, Color color) {
        g2d.setColor(Color.awtColor(color));
        g2d.fillOval(x, y, width, height);
    }

    /**
     * Draws a filled in polygon on the window.
     * <p> The amount of x-coordinates of the points have to match to amount of y-coordinates. </p>
     * @param window where will be drawn to
     * @param xPoints the x-coordinates of the points where the x-coordinates are relative to the window
     * @param yPoints the y-coordinates of the points where the y-coordinates are relative to the window
     * @param color the color of the polygon
     * @since 1.0
     */
    public static void polygon(Window window, int[] xPoints, int[] yPoints, Color color) {
        gPolygon(window.getGraphics2D(), xPoints, yPoints, color);
    }

    /**
     * Draws a filled in polygon on the surface.
     * <p> The amount of x-coordinates of the points have to match to amount of y-coordinates. </p>
     * @param surface where will be drawn to
     * @param xPoints the x-coordinates of the points where the x-coordinates are relative to the surface
     * @param yPoints the y-coordinates of the points where the y-coordinates are relative to the surface
     * @param color the color of the polygon
     * @since 1.0
     */
    public static void polygon(Surface surface, int[] xPoints, int[] yPoints, Color color) {
        gPolygon(surface.getGraphics2D(), xPoints, yPoints, color);
    }

    private static void gPolygon(Graphics2D graphics2D, int[] xPoints, int[] yPoints, Color color) {
        graphics2D.setColor( Color.awtColor(color));
        graphics2D.fillPolygon(xPoints, yPoints, xPoints.length);
    }



    /**
     * Draws a line to the window.
     * @param window where will be drawn to
     * @param x1 the first x-coordinate that is relative to the window
     * @param y1 the first y-coordinate that is relative to the window
     * @param x2 the second x-coordinate that is relative to the window
     * @param y2 the second y-coordinate that is relative to the window
     * @param thickness the thickness of the line in pixels
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(Window window, int x1, int y1, int x2, int y2, float thickness, Color color) {
        gLine(window.getGraphics2D(), x1, y1, x2, y2, thickness, color);
    }

    /**
     * Draws a line to the window with a thickness of 1.f
     * @param window where will be drawn to
     * @param x1 the first x-coordinate that is relative to the window
     * @param y1 the first y-coordinate that is relative to the window
     * @param x2 the second x-coordinate that is relative to the window
     * @param y2 the second y-coordinate that is relative to the window
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(Window window, int x1, int y1, int x2, int y2, Color color) {
        gLine(window.getGraphics2D(), x1, y1, x2, y2, 1.0f, color);
    }

    /**
     * Draws a line to the surface.
     * @param surface where will be drawn to
     * @param x1 the first x-coordinate that is relative to the surface
     * @param y1 the first y-coordinate that is relative to the surface
     * @param x2 the second x-coordinate that is relative to the surface
     * @param y2 the second y-coordinate that is relative to the surface
     * @param thickness the thickness of the line in pixels
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(Surface surface, int x1, int y1, int x2, int y2, float thickness, Color color) {
        gLine(surface.getGraphics2D(), x1, y1, x2, y2, thickness, color);
    }

    /**
     * Draws a line to the surface with a thickness of 1.
     * @param surface where will be drawn to
     * @param x1 the first x-coordinate that is relative to the surface
     * @param y1 the first y-coordinate that is relative to the surface
     * @param x2 the second x-coordinate that is relative to the surface
     * @param y2 the second y-coordinate that is relative to the surface
     * @param color the color of the line
     * @since 1.0
     */
    public static void line(Surface surface, int x1, int y1, int x2, int y2, Color color) {
        gLine(surface.getGraphics2D(), x1, y1, x2, y2, 1.0f, color);
    }

    private static void gLine(Graphics2D graphics2D, int x1, int y1, int x2, int y2, float thickness, Color color) {
        Stroke stroke = graphics2D.getStroke();
        graphics2D.setStroke(new BasicStroke(thickness));
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.drawLine(x1, y1, x2, y2);
        graphics2D.setStroke(stroke);
    }
}

// JavaDoc = slavery