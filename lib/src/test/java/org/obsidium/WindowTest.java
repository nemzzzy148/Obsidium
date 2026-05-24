package org.obsidium;

import org.obsidium.event.*;
import org.obsidium.math.Vector2;
import org.obsidium.time.Clock;
import org.obsidium.window.State;
import org.obsidium.window.Window;

public class WindowTest {
    public static void main(String[] args) {
        Clock clock = new Clock();

        Vector2 size = new Vector2(400, 400);
        Vector2 position = new Vector2(Obsidium.getScreenSize().x / 2 - size.x/2, Obsidium.getScreenSize().y / 2 - size.y/2);

        Window window = Obsidium.createWindow(size.x, size.y, "WindowTest", position.x, position.y, true, true, false, State.FULL_SCREEN);

        boolean setPos = true;

        while (true) {
            for (Event e : window.events.get()) {
                switch (e.type) {
                    case WINDOW_MAXIMIZED -> System.out.println("WINDOW_MAXIMIZED");
                    case WINDOW_FULL_SCREEN -> System.out.println("WINDOW_FULL_SCREEN");
                    case WINDOW_MINIMIZED ->  System.out.println("WINDOW_MINIMIZED");
                    case WINDOW_MOVED -> System.out.println("WINDOW_MOVED");
                    case WINDOW_RESIZED -> System.out.println("WINDOW_RESIZED");
                    case WINDOW_SHOWN -> System.out.println("WINDOW_SHOWN");
                    case WINDOW_FOCUSED -> System.out.println("WINDOW_FOCUSED");
                    case WINDOW_RESTORED -> System.out.println("WINDOW_RESTORED");
                    case WINDOW_UNFOCUSED -> System.out.println("WINDOW_UNFOCUSED");
                    case QUIT -> window.quit();
                }
                if (e.type == Type.KEY_DOWN) {
                    switch (e.key) {
                        case SPACE -> window.setResizable(!window.getResizable());
                        case SHIFT -> window.setState(window.getState() == State.FULL_SCREEN ? State.NORMAL : State.FULL_SCREEN);
                    }
                }
            }
            for (Event e : window.events.getPressed()) {
                switch (e.key) {
                    case A -> position.x--;
                    case D -> position.x++;
                    case W -> position.y--;
                    case S -> position.y++;
                    case UP -> size.y--;
                    case DOWN -> size.y++;
                    case LEFT -> size.x--;
                    case RIGHT -> size.x++;
                }
            }
            clock.tick(60);
        }
    }
}
