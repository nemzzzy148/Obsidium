package org.obsidium.ui;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.graphics.surface.SimpleSurface;
import org.obsidium.math.Vector2;
import org.obsidium.ui.components.BaseComponent;
import org.obsidium.ui.components.Component;
import org.obsidium.window.Window;

import java.util.List;

public class UI extends BaseComponent {
    private Window window;

    public UI(Window window) {
        this.window = window;
        this.width = window.getWidth();
        this.height = window.getHeight();
    }

    public void render() {
        if (window != null) {
            this.width = window.getWidth();
            this.height = window.getHeight();
        }
        else {
            return;
        }

        if (!enabled || !visible) return;

        children.forEach(c -> c.render(window));
    }

    public void processEvents(List<Event> events) {
        if (!enabled) return;

        boolean mouseDown = false;
        boolean mouseUp = false;
        Vector2 mousePos = null;

        for (Event e : events) {
            if (e.type == Type.MOUSE_DOWN) {
                mouseDown = true;
            }
            if (e.type == Type.MOUSE_UP) {
                mouseUp = true;
            }
            if (e.type == Type.MOUSE) {
                mousePos = e.position;
            }
            if (mouseDown && mouseUp && mousePos == null) break;
        }

        if (mousePos != null) {
            for (Component c : children) {
                c.update(mousePos, mouseUp, mouseDown);
            }
        }
    }

    @Override
    public void render(SimpleSurface surface) {
        if (!enabled || !visible) return;

        children.forEach(c -> c.render(surface));
    }

    @Override
    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    @Override
    public int getHeight() {
        return height;
    }

    @Override
    public int getWidth() {
        return width;
    }
}