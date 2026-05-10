package org.obsidium.event;

import java.awt.Frame;
import java.awt.MouseInfo;

import org.obsidium.geometry.Vector2;

/**
 * ---advanced---
 * 
 * This class should only be instantiated by Obsidium.
 */
public class Mouse {
    private Frame frame;
    
    /**
     * ---advanced---
     * 
     * This constructor should only be instantiated by Obsidium.
     * 
     * @param frame
     */
    public Mouse(Frame frame) {
        this.frame = frame;
    }

    /**
     * Returns the position of the mouse relative to the window.
     * 
     * @return {@link Vector2} that contains the x and y-coordinates of the mouse
     * 
     * @since 1.0
     */
    public Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    /**
     * Returns the individual x-coordinate of the mouse relative to the screen.
     * 
     * @return the x-coordinate of the mouse
     */
    public int getPosX() {
        return  MouseInfo.getPointerInfo().getLocation().x - frame.getLocationOnScreen().x;
    }

    /**
     * Returns the individual y-coordinate of the mouse relative to the screen.
     * 
     * @return the y-coordinate of the mouse
     */
    public int getPosY() {
        return MouseInfo.getPointerInfo().getLocation().y - frame.getLocationOnScreen().y;
    }
}
