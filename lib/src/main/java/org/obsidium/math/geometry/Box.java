package org.obsidium.math.geometry;

public abstract class Box {
    protected int width;
    protected int height;

    public abstract int getWidth();
    public abstract void setWidth(int width);

    public abstract int getHeight();
    public abstract void setHeight(int height);
}
