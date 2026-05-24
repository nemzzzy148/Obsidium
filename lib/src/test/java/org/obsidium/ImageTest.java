package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Key;
import org.obsidium.event.Type;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.graphics.Surface;
import org.obsidium.graphics.Transform;
import org.obsidium.image.Format;
import org.obsidium.image.Image;
import org.obsidium.time.Clock;
import org.obsidium.window.State;
import org.obsidium.window.Window;

public class ImageTest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();

        window.setResizable(true);

        Surface logo = new Surface(200, 200);

        logo.blit(Transform.scale(Image.logo(), 200, 200), 0, 0);

        float deg = 0;

        Clock clock = new Clock();

        while(true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) {
                    window.quit();
                } else if (e.type == Type.KEY_DOWN) {
                    if (e.key == Key.SPACE) {
                        window.setFullScreen(!window.getFullScreen());
                    } else if (e.key == Key.ESCAPE) {
                        window.quit();
                    }
                }
            }
            Draw.fill(window, new Color());

            Surface rotated = Transform.rotate(logo, deg++, true);

            int steps = 25;
            int amount = 0;
            for (int i = 0; i < window.getWidth(); i += steps) {
                for (int j = 0; j < window.getHeight(); j += steps) {
                    window.blit(rotated, i,j);
                    amount++;
                }
            }
            System.out.println("Amount: " + amount);

            window.flip();

            clock.tick();

            System.out.println(clock.getFPS());
        }
    }
}
