package org.obsidium.ui.components;

import javax.swing.*;

public class Text extends Component {
    protected void init() {
        javax.swing.JLabel j = new JLabel();
    }
    private JLabel jLabel;
    @Override
    public JComponent getJComponent() {
        return jLabel;
    }
}
