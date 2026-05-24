package org.obsidium.ui;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class UI {
    private JFrame frame;
    private GridBagConstraints gbc;
    private Graphics2D graphics2D;

    public void setGraphics2D(Graphics2D graphics2D) {
        this.graphics2D = graphics2D;
    }

    public UI(JFrame frame, GridBagConstraints gbc, Graphics2D graphics2D) {
        this.frame = frame;
        this.gbc = gbc;
        this.graphics2D = graphics2D;
    }

    // on runtime
    private ArrayList<Panel> panels = new ArrayList<Panel>();

    public void addPanel(Panel panel) {
        frame.add(panel.getjPanel(), gbc);
        panels.add(panel);
    }

    public Panel getPanel(String name) {
        for (Panel p : panels) {
            if (p.getName().equals(name)) return p;
        }
        return null;
    }

    public void removePanel(String name) {
        panels.remove(getPanel(name));
    }

    public void removePanel(Panel panel) {
        panels.remove(panel);
    }

    public void render() {
        for (Panel p : panels) {
            JPanel jp = p.getjPanel();
            jp.setSize(jp.getPreferredSize());
            jp.doLayout();
            jp.printAll(graphics2D);
        }
    }
}
