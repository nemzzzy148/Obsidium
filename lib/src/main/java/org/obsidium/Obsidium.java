package org.obsidium;

import java.awt.Dimension;
import java.awt.MouseInfo;
import java.awt.Toolkit;
import java.util.ArrayList;

import org.obsidium.geometry.Vector2;

/**
 * The central class for creating windows and retrieving properties of the current device.
 * 
 * @see #createWindow()
 * 
 * @since 1.0
 */
public class Obsidium {
    private static final ArrayList<Window> windows = new ArrayList<>();
    private static boolean first = true;

    // default
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;

    private static final String TITLE = "ObsidiumAWT game";

    // main reference constructor

    /**
    * Creates a new window with full configuration.
    *
    * <p>If this is the last open window, closing it will exit the program,
    * even if {@code stopProgramOnClose} is {@code false}.</p>
    *
    * @param width  the width in pixels; if {@code <= 0}, defaults to {@code 800}
    * @param height the height in pixels; if {@code <= 0}, defaults to {@code 600}
    * @param title  the window title
    * @param x the x-coordinate of the window, relative to the physical display
    * @param y the y-coordinate of the window, relative to the physical display
    * @param stopProgramOnClose if {@code true}, closing this window exits the program
    * @return the created and registered {@link Window}
    * @since 1.0
    */
    public static Window createWindow(int width, int height, String title, int x, int y, boolean stopProgramOnClose) {
        if (width <= 0) width = WIDTH;
        if (height <= 0) height = HEIGHT;
        init();
        Window window = new Window(width, height, title, x, y, stopProgramOnClose);
        windows.add(window);
        return window;
    }

    /**
     * Creates a new window with {@code stopProgramOnClose = false}.
     * 
     * <p>See {@link #createWindow(int, int, String, int, int, boolean)}
     * for full documentation.</p>
     */
    public static Window createWindow(int width, int height, String title, int x, int y) {
        return createWindow(width, height, title, x, y, false);
    }

    /**
     * Creates a new window at the center of the screen.
     * 
     * <p>See {@link #createWindow(int, int, String, int, int, boolean)}
     * for full documentation.</p>
     */
    public static Window createWindow(int width, int height, String title, boolean stopProgramOnClose) {
        Vector2 c = getCenter(width, height);
        return createWindow(width, height, title, c.x, c.y, stopProgramOnClose);
    }

    /**
     * Creates a new window at the center of the screen with {@code stopProgramOnClose = false}.
     * 
     * <p>See {@link #createWindow(int, int, String, int, int, boolean)}
     * for full documentation.</p>
     */
    public static Window createWindow(int width, int height, String title) {
        Vector2 c = getCenter(width, height);
        return createWindow(width, height, title, c.x, c.y, false);
    }

    /**
     * Creates a new window with the propertys:
     * <ul>
     *   <li>a resolution of {@code 800x600}</li>
     *   <li>centered on the screen</li>
     *   <li>{@code stopProgramOnClose = false}</li>
     * </ul>
     * <p>See {@link #createWindow(int, int, String, int, int, boolean)}
     * for full documentation.</p>
     */
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

    /**
     * Returns the size of the primary screen.
     * 
     * @return a {@link Vector2} representing the screen dimensions
     */
    public static Vector2 getScreenSize() {
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        return new Vector2(dimension.width, dimension.height);
    }

    // mouse

    /**
     * Returns the coordinates of the mouse relative to the primary screen.
     * 
     * @return a {@link Vector2} containing the mouse cursor position in pixels
     */
    public static Vector2 getMousePos() {
        return new Vector2(getMousePosX(), getMousePosY());
    }

    /**
     * Returns the x coordinate of the mouse relative to the primary screen.
     * 
     * @return the x coordinate of the mouse in pixels
     */
    public static int getMousePosX() {
        return MouseInfo.getPointerInfo().getLocation().x;
    }

    /**
     * Returns the y coordinate of the mouse relative to the primary screen.
     * 
     * @return the y coordinate of the mouse in pixels
     */
    public static int getMousePosY() {
        return MouseInfo.getPointerInfo().getLocation().y;
    }
}