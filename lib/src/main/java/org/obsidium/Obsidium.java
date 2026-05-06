package org.obsidium;

import java.awt.Dimension;
import java.awt.MouseInfo;
import java.awt.Toolkit;
import java.util.ArrayList;

import org.obsidium.geometry.Vector2;

public class Obsidium {
    private static final ArrayList<Window> windows = new ArrayList<>();
    private static boolean first = true;

    // default
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;

    private static final String TITLE = "ObsidiumAWT game";

    // main reference constructor
    public static Window createWindow(int width, int height, String title, int x, int y, boolean stopProgramOnClose) {
        init();
        Window window = new Window(width, height, title, x, y, stopProgramOnClose);
        windows.add(window);
        return window;
    }

    public static Window createWindow(int width, int height, int x, int y, String title) {
        return createWindow(width, height, title, x, y, false);
    }

    public static Window createWindow(int width, int height, String title, boolean stopProgramOnClose) {
        Vector2 c = getCenter(width, height);
        return createWindow(width, height, title, c.x, c.y, stopProgramOnClose);
    }

    public static Window createWindow(int width, int height, String title) {
        Vector2 c = getCenter(width, height);
        return createWindow(width, height, title, c.x, c.y, false);
    }

    public static Window createWindow() {
        Vector2 c = getCenter(WIDTH, HEIGHT);
        return createWindow(WIDTH, HEIGHT, TITLE, c.x, c.y, false);
    }

    private static void init() {
        if (first) {
            System.setProperty("sun.java2d.opengl", "true");
            first = false;
        }
    }

    private static Vector2 getCenter(int width, int height) {
        return new Vector2((int)(getScreenSize().x / 2 - width / 2), (int)(getScreenSize().y / 2 - height / 2));
    }

    protected static void closeWindow(Window window) {
        if (window.stopProgramOnClose) {
            System.out.println("Exiting obsidium");
            System.exit(0);
        }
        windows.remove(window);
        if (windows.size() < 1) {
            System.out.println("Exiting obsidium");
            System.exit(0);
        }
    }
    // device info

    public static Vector2 getScreenSize() {
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        return new Vector2(dimension.width, dimension.height);
    }

    // mouse

    public static Vector2 getMousePos() {
        return new Vector2(getMousePosX(), getMousePosY());
    }

    public static int getMousePosX() {
        return MouseInfo.getPointerInfo().getLocation().x;
    }
    public static int getMousePosY() {
        return MouseInfo.getPointerInfo().getLocation().y;
    }
}