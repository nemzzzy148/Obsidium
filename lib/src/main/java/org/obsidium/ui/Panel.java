package org.obsidium.ui;

import org.obsidium.math.Vector2;
import org.obsidium.graphics.Color;
import org.obsidium.ui.components.Component;
import org.obsidium.window.Window;

import javax.swing.*;
import java.awt.*;

public class Panel {
    private String name = "Panel";

    public String getName() {
        return name;
    }
    void setName(String name) {
        this.name = name;
    }

    private Color color;

    public void setColor(Color color) {
        jPanel.setBackground( Color.awtColor(color) );
        this.color = color;
    }

    public Color getColor() {
        return color;
    }

    private int width = 800;

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        jPanel.setSize(width, height);
        this.width = width;
    }

    private int height = 600;

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        jPanel.setSize(width, height);
        this.height = height;
    }

    public Vector2 getSize() {
        return new Vector2(width, height);
    }
    public void setSize(int width, int height) {
        this.width = width;
        this.height = height;
    }

    private JPanel jPanel;

    public JPanel getjPanel() {
        return jPanel;
    }

    public Panel(String name, int width, int height, Color color) {
        init(name, width, height, color);
    }

    public Panel(String name, Window window, Color color) {
        init(name, window.getWidth(), window.getHeight(), color);
    }

    public Panel(String name, Color color) {
        init(name, width, height, color);
    }

    public Panel(Window window) {
        init(name, window.getWidth(), window.getHeight(), Color.TRANSPARENT);
    }

    public Panel() {
        init(name, width, height, Color.TRANSPARENT);
    }

    private void init(String name, int width, int height, Color color) {
        this.name = name;
        this.color = color;
        this.width = width;
        this.height = height;
        jPanel = new JPanel();
        jPanel.setBackground( Color.awtColor(color) );
        jPanel.setPreferredSize( new Dimension(width, height));
    }

    // component functionality

    public void add(Component component) {
        jPanel.add(component.getJComponent());
    }
}