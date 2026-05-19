package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.time.Clock;
import org.obsidium.window.Window;

public class MouseTest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();
        
        Clock clock = new Clock();

        while (true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) {
                    window.quit();
                }
                if (e.type == Type.MOUSE_DOWN) {
                    System.out.println("Mouse up!");
                }
                if (e.type == Type.MOUSE_UP) {
                    System.out.println("Mouse down!");
                }
            }
            
            System.out.println(window.mouse.getPosX() + "," + window.mouse.getPosY());

            clock.tick(10);
        }
    }
}
