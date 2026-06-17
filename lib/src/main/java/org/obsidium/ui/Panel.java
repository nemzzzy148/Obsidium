package org.obsidium.ui;

import org.obsidium.graphics.Draw;
import org.obsidium.graphics.Color;
import org.obsidium.math.Vector2;
import org.obsidium.ui.components.Component;
import org.obsidium.window.Window;

public class Panel extends Component {
    private Color color;
    private Window window;

    public Panel(int width, int height, Color color) {
        init(null, width, height, color);
    }

    public Panel(Window window, Color color) {
        init(window, window.getWidth(), window.getHeight(), color);
    }

    public Panel(Window window) {
        init(window, window.getWidth(), window.getHeight(), Color.DEEP_CHARCOAL);
    }

    private void init(Window window, int width, int height, Color color) {
        this.window = window;
        this.color = color;
        this.width = width;
        this.height = height;
    }

    public void setColor(Color color) {
        this.color = color;
    }
    public Color getColor() {
        return color;
    }

    public Window getWindow() {
        return window;
    }
    public void setWindow(Window window) {
        this.window = window;
        setSize(window.getSize());
    }

    @Override
    public void redrawGraphics() {
        Draw.fill(surfaceCache, color);
    }

    @Override
    public void update(Vector2 mousePosition, boolean mouseUp, boolean mouseDown) {
        if (width != window.getWidth() || height != window.getHeight()) {
            setSize(window.getWidth(), window.getHeight());
        }

        processMouse(mousePosition, mouseUp, mouseDown);
    }
}