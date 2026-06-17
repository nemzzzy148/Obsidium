package org.obsidium.ui.components;

import org.obsidium.graphics.surface.SimpleSurface;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseComponent {
    protected int offsetX = 0;
    protected int offsetY = 0;
    protected int absoluteParentX = 0;
    protected int absoluteParentY = 0;
    protected int width = 100;
    protected int height = 100;

    protected boolean visible = true;
    protected boolean enabled = true;

    protected List<Component> children = new ArrayList<>();

    public void addChild(Component component) {
        component.setParent(this);
    }

    public abstract void render(SimpleSurface surface);

    public boolean isVisible() { return visible; }
    public void setVisible(boolean visible) { this.visible = visible; }

    public boolean isEnabled() { return enabled; }
    public abstract void setEnabled(boolean enabled);

    public abstract int getHeight();
    public abstract int getWidth();

    public int getOffsetX() { return offsetX; }
    public int getOffsetY() { return  offsetY; }

    protected int getAbsoluteParentX() { return absoluteParentX; }
    protected int getAbsoluteParentY() { return absoluteParentY; }
}