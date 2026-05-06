package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.time.Clock;

public class MouseTest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();
        
        Clock clock = new Clock();

        while (true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) {
                    window.quit();
                }
                if (e.type == Type.MOUSEDOWN) {
                    System.out.println("Mouse up!");
                }
                if (e.type == Type.MOUSEUP) {
                    System.out.println("Mouse down!");
                }
            }
            
            System.out.println(window.mouse.getPosX() + "," + window.mouse.getPosY());

            clock.tick(10);
        }
    }
}
