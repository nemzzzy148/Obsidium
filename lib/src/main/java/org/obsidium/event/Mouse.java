package org.obsidium.event;

import java.awt.MouseInfo;

import org.obsidium.math.Vector2;
import org.obsidium.window.Window;

import javax.swing.*;

/**
 * <b>---advanced---</b>
 * This class should only be instantiated by Obsidium.
 * @since 1.0
 */
public class Mouse {
    private final Window window;
    
    /**
     * <b>---advanced---</b>
     * This constructor should only be instantiated by Obsidium.
     * @param window used for mouse functionality
     * @since 1.2
     */
    public Mouse(Window window) {
        this.window = window;
    }

    /**
     * Returns the position of the mouse relative to the window.
     * @return {@link Vector2} that contains the x and y-coordinates of the mouse
     * @since 1.0
     */
    public Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    /**
     * Returns the individual x-coordinate of the mouse relative to the screen.
     * @return the x-coordinate of the mouse
     * @since 1.0
     */
    public int getPosX() {
        if (!window.getCanvas().isShowing()) return 0;
        return  MouseInfo.getPointerInfo().getLocation().x - window.getCanvas().getLocationOnScreen().x;
    }

    /**
     * Returns the individual y-coordinate of the mouse relative to the screen.
     * @return the y-coordinate of the mouse
     * @since 1.0
     */
    public int getPosY() {
        if (!window.getCanvas().isShowing()) return 0;
        return MouseInfo.getPointerInfo().getLocation().y - window.getCanvas().getLocationOnScreen().y;
    }
}
