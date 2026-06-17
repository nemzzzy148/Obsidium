package org.obsidium.ui.components;

import org.obsidium.graphics.Color;
import org.obsidium.graphics.Font;

public class Text extends Component {
    protected String text;
    protected Color color;
    protected Font font;
    protected int size;

    public Text(String text, Font font, Color color) { init(text, font, color); }
    public Text(String text, Font font) { init(text, font, Color.WHITE); }
    protected void init(String text, Font font, Color color) {
        this.font = font;
        this.text = text;
        this.color = color;
    }

    public String getText() {
        return this.text;
    }
    public void setText(String text) {
        this.text = text;
    }

    public Color getColor() {
        return this.color;
    }
    protected void setColor(Color color) {
        this.color = color;
    }

    public Font getFont() {
        return  this.font;
    }
    public void setFont(Font font) {
        this.font = font;
        this.font.setSize(this.size);
    }

    public int getSize() {
        return this.size;
    }
    public void setSize(int size) {
        this.size = size;
        if (font != null) {
            font.setSize(size);
        }
    }

    @Override
    public void redrawGraphics() {

    }
}
