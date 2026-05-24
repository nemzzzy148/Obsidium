package org.obsidium.ui.components;

import org.obsidium.graphics.Color;

import javax.swing.*;

public class Button extends Component {
    private String text;

    public Button(String text) {
        this.text = text;
    }

    private void init(String text) {
        this.text = text;
        jButton = new JButton(text);
    }

    private JButton jButton;
    @Override
    public JComponent getJComponent() {
        return jButton;
    }
}