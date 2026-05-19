package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.window.Window;

public class MinimalTest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow(800,800, "hii", 0, 0);

        while (true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) {
                    window.quit();
                }
            }
        }
    }
}
