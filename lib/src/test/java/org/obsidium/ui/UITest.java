package org.obsidium.ui;

import org.obsidium.Obsidium;
import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.ui.components.Button;
import org.obsidium.window.Window;

public class UITest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();
        window.setResizable(true);
        Panel panel = new Panel(window);
        window.ui.addChild(panel);
        Button button = new Button();
        panel.addChild(button);

        boolean running = true;
        while (running) {
            var events = window.events.get();
            for (Event e : events) {
                if (e.type == Type.QUIT) {
                    running = false;
                    break;
                }
            }

            window.clear(Color.BLACK);

            window.ui.processEvents(events);

            window.ui.render();

            window.flip();
        }
        window.quit();
    }
}
