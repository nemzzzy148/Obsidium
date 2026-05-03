package org.obsidium.event;

import java.awt.Frame;
import java.awt.MouseInfo;

import org.obsidium.geometry.Vector2;

public class Mouse {
    private Frame frame;
    
    public Mouse(Frame frame) {
        this.frame = frame;
    }

    public Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    public int getPosX() {
        return  MouseInfo.getPointerInfo().getLocation().x - frame.getLocationOnScreen().x;
    }
    public int getPosY() {
        return MouseInfo.getPointerInfo().getLocation().y - frame.getLocationOnScreen().y;
    }
}
