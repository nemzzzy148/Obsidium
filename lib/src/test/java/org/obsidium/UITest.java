package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.ui.Panel;
import org.obsidium.ui.components.Button;
import org.obsidium.window.Window;

public class UITest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();
        Panel panel = new Panel("panel", window, Color.TRANSPARENT);
        Button button = new Button("hii");
        panel.add(button);
        window.ui.addPanel(panel);

        while (true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) window.quit();
                if(e.type == Type.MOUSE_DOWN) {
                    System.out.println("MOUSE");
                }
            }
            Draw.fill(window, Color.BLACK);
            Draw.circle(window, 100, 100, 50, Color.WHITE);
            window.ui.render();
            window.flip();
        }
    }
}
