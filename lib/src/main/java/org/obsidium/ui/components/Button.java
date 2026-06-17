package org.obsidium.ui.components;

import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;

public class Button extends Component {
    protected String text;

    @Override
    public void redrawGraphics() {
        Color color = Color.WINDOWS_BLUE;
        if (hovered) color = Color.BLUE;
        if (active) color = Color.WHITE;
        Draw.rectRounded(surfaceCache, 0, 0, width, height,
                (height > width) ? width / 2 : height/2, color);
    }
}