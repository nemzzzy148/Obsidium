package org.obsidium.graphics;

import java.awt.BasicStroke;
import java.awt.Graphics2D;

import org.obsidium.Window;

public class Draw {
    // fill
    public static void fill(Window window, Color color) {
        gFill(window.getGraphics2D(), window.getWidth(), window.getHeight(), color);
    }
    public static void fill(Surface surface, Color color) {
        gFill(surface.getGraphics2D(), surface.getWidth(), surface.getHeight(), color);
    }

    private static void gFill(Graphics2D graphics2D, int width, int height, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillRect(0, 0, width, height);
    }

    // rectangle
    public static void rect(Window window, int x, int y, int width, int height, Color color) {
        gRect(window.getGraphics2D(), x, y, width, height, color);
    }
    public static void rect(Surface surface, int x, int y, int width, int height, Color color) {
        gRect(surface.getGraphics2D(), x, y, width, height, color);
    }

    private static void gRect(Graphics2D graphics2D,  int x, int y, int width, int height, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillRect(x, y, width, height);
    }

    // circle
    public static void circle(Window window, int x, int y, int r, Color color) {
        gCircle(window.getGraphics2D(), x, y, r, color);
    }
    public static void circle(Surface surface, int x, int y, int r, Color color) {
        gCircle(surface.getGraphics2D(), x, y, r, color);
    }

    private static void gCircle(Graphics2D graphics2D, int x, int y, int r, Color color) {
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.fillOval(x, y, r, r);
    }

    // polygon
    public static void polygon(Window window, int[] xPoints, int[] yPoints, Color color) {
        gPolygon(window.getGraphics2D(), xPoints, yPoints, color);
    }
    public static void polygon(Surface surface, int[] xPoints, int[] yPoints, Color color) {
        gPolygon(surface.getGraphics2D(), xPoints, yPoints, color);
    }

    private static void gPolygon(Graphics2D graphics2D, int[] xPoints, int[] yPoints, Color color) {
        graphics2D.setColor( Color.awtColor(color));
        graphics2D.fillPolygon(xPoints, yPoints, xPoints.length);
    }

    // line
    public static void line(Window window, int x1, int y1, int x2, int y2, float thickness, Color color) {
        gLine(window.getGraphics2D(), x1, y1, x2, y2, thickness, color);
    }
    public static void line(Window window, int x1, int y1, int x2, int y2, Color color) {
        gLine(window.getGraphics2D(), x1, y1, x2, y2, 1.0f, color);
    }
    public static void line(Surface surface, int x1, int y1, int x2, int y2, float thickness, Color color) {
        gLine(surface.getGraphics2D(), x1, y1, x2, y2, thickness, color);
    }
    public static void line(Surface surface, int x1, int y1, int x2, int y2, Color color) {
        gLine(surface.getGraphics2D(), x1, y1, x2, y2, 1.0f, color);
    }

    private static void gLine(Graphics2D graphics2D, int x1, int y1, int x2, int y2, float thickness, Color color) {
        graphics2D.setStroke(new BasicStroke(thickness));
        graphics2D.setColor( Color.awtColor(color) );
        graphics2D.drawLine(x1, y1, x2, y2);
    }
}