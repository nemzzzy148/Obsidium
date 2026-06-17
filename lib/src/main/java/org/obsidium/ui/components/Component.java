package org.obsidium.ui.components;

import org.obsidium.graphics.surface.SimpleSurface;
import org.obsidium.graphics.surface.Surface;
import org.obsidium.math.Vector2;
import org.obsidium.math.geometry.SimpleBoundingBox;

public abstract class Component extends BaseComponent {

    // coordinates, bounding box components
    protected SimpleBoundingBox boundingBox = new SimpleBoundingBox(width, height);

    // states
    protected boolean hovered = false;
    protected boolean active = false;
    protected boolean dirty = true;

    // hierarchy components
    protected BaseComponent parent = null;

    // layout

    protected int anchor = Anchor.CENTER;

    //graphics
    protected Surface surfaceCache;
    public void render(SimpleSurface surface) {
        if (!visible) return;

        if (surfaceCache == null) {
            surfaceCache = new Surface(width, height);
            invalidate();
        }

        if (this.dirty) {
            if ((surfaceCache.getWidth() != width || surfaceCache.getHeight() != height)) {
                surfaceCache.dispose();
                surfaceCache = new Surface(width, height);
            }

            redrawGraphics();
            markClean();
        }

        surface.blit(surfaceCache, absoluteParentX + offsetX, absoluteParentY + offsetY);

        children.forEach(c -> c.render(surface));
    }

    public abstract void redrawGraphics();

    // position and box ---------

    public void setOffsetX(int offsetX) {
        if (this.offsetX != offsetX) {
            this.offsetX = offsetX;
            setChildrenLocalSpace();
        }
    }
    public void setOffsetY(int offsetY) {
        if (this.offsetY != offsetY) {
            this.offsetY = offsetY;
            setChildrenLocalSpace();
        }
    }

    public void setOffsetPosition(int x, int y) {
        this.offsetX = x;
        this.offsetY = y;
        setChildrenLocalSpace();
    }
    public void setOffsetPosition(Vector2 position) { setOffsetPosition(position.x, position.y);}

    public Vector2 getPosition() { return new Vector2(offsetX + absoluteParentX, offsetY + absoluteParentY); }
    public void setPosition(int x, int y) {
        this.offsetX = x - absoluteParentX;
        this.offsetY = y - absoluteParentY;
        anchor = Anchor.TOP_LEFT;
        setChildrenLocalSpace();
    }
    public void setPosition(Vector2 position) { setPosition(position.x, position.y);}

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
        boundingBox.setWidth(width);
        setChildrenLocalSpace();
        invalidate();
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
        boundingBox.setHeight(height);
        setChildrenLocalSpace();
        invalidate();
    }

    public void setSize(int width, int height) {
        setHeight(height);
        setWidth(width);
    }

    public void setSize(Vector2 size) {
        setSize(size.x, size.y);
    }

    public int getAnchor() {
        return anchor;
    }

    public void setAnchor(int anchor) {
        if (this.anchor != anchor) {
            this.anchor = anchor;

            if (parent != null) {
                setLocalSpace(
                        parent.getOffsetX() + parent.getAbsoluteParentX(),
                        parent.getOffsetY() + parent.getAbsoluteParentY(),
                        parent.getWidth(),
                        parent.getHeight()
                );
            }
        }
    }

    public boolean insideComponent(Vector2 point) {
        return boundingBox.insideBox(point, new Vector2(absoluteParentX + offsetX, absoluteParentY + offsetY));
    }

    public void update(Vector2 mousePosition, boolean mouseUp, boolean mouseDown) {
        processMouse(mousePosition, mouseUp, mouseDown);
    }

    public void processMouse(Vector2 mousePosition, boolean mouseUp, boolean mouseDown) {
        for (Component c : children) {
            c.processMouse(mousePosition, mouseUp, mouseDown);
        }
        mouseInput(mousePosition, mouseUp, mouseDown);
    }

    private void mouseInput(Vector2 mousePosition, boolean mouseUp, boolean mouseDown) {
        if (insideComponent(mousePosition)) {
            setHovered(true);
            if (mouseUp) {
                setActive(false);
            }
            if (mouseDown) {
                setActive(true);
            }
        } else {
            setHovered(false);
            setActive(false);
        }
    }

    public void updateLocalSpace() {
        if (parent != null) {
            setLocalSpace(parent.getAbsoluteParentX() + parent.getOffsetX(),
                    parent.absoluteParentY + parent.getOffsetY(),
                    parent.getWidth(), parent.getHeight());
        }
    }

    public void setLocalSpace(int parentAbsoluteX, int parentAbsoluteY, int parentWidth , int parentHeight) {
        switch (anchor) {
            case 0 -> {
                absoluteParentX = parentAbsoluteX;
                absoluteParentY = parentAbsoluteY;
            }
            case 1 -> {
                absoluteParentX = parentAbsoluteX + parentWidth - width;
                absoluteParentY = parentAbsoluteY;
            }
            case 2 -> {
                absoluteParentX = parentAbsoluteX;
                absoluteParentY = parentAbsoluteY + parentHeight - height;
            }
            case 3 -> {
                absoluteParentX = parentAbsoluteX + parentWidth - width;
                absoluteParentY = parentAbsoluteY + parentHeight - height;
            }
            default -> {
                absoluteParentX = parentAbsoluteX + (parentWidth / 2) - (width / 2);
                absoluteParentY = parentAbsoluteY + (parentHeight / 2) - (height / 2);
            }

        }
        setChildrenLocalSpace();
    }

    public void setChildrenLocalSpace() {
        int childrenOffsetX = absoluteParentX + offsetX;
        int childrenOffsetY = absoluteParentY + offsetY;

        children.forEach(c -> c.setLocalSpace(childrenOffsetX, childrenOffsetY, width, height));
    }

    // attributes ---------
    public void setEnabled(boolean enabled) { this.enabled = enabled; invalidate(); }

    public boolean isHovered() { return hovered; }
    public void setHovered(boolean hovered) {
        if (this.hovered != hovered) {
            this.hovered = hovered;
            invalidate();
        }

    }

    public boolean isActive() { return active; }
    public void setActive(boolean active) {
        if (this.active != active) {
            this.active = active;
            invalidate();
        }
    }

    public void invalidate() {
        dirty = true;
    }
    public void markClean() {
        dirty = false;
    }
    public boolean isDirty() {
        return dirty;
    }

    // hierarchy
    public void setParent(BaseComponent parent) {
        if (this.parent == parent) return;

        if (this.parent != null) {
            this.parent.children.remove(this);
        }

        this.parent = parent;

        if (this.parent != null) {
            if (!parent.children.contains(this)) {
                parent.children.add(this);
            }
            setLocalSpace(parent.getOffsetX() + parent.getAbsoluteParentX(), parent.getOffsetY() + parent.getAbsoluteParentY(),
                    parent.getWidth(), parent.getHeight());
        } else {
            setLocalSpace(0, 0, 0, 0);
        }
    }
}