package org.obsidium;

import java.awt.Dimension;
import java.awt.MouseInfo;
import java.awt.Toolkit;
import java.util.ArrayList;

import org.obsidium.geometry.Vector2;

public class Obsidium {
    private static final ArrayList<Window> windows = new ArrayList<>();
    private static boolean first = true;

    public static Window createWindow(int width, int height, String title, boolean stopProgramOnClose) {
        init();
        Window window = new Window(width, height, title, stopProgramOnClose);
        windows.add(window);
        return window;
    }

    public static Window createWindow(int width, int height, String title) {
        return createWindow(width, height, title, false);
    }

    private static void init() {
        if (first) {
            System.setProperty("sun.java2d.opengl", "true");
            first = false;
        }
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