package org.obsidium;

import org.obsidium.event.Event;
import org.obsidium.event.Type;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.graphics.Surface;
import org.obsidium.graphics.Transform;
import org.obsidium.image.Image;
import org.obsidium.time.Clock;
import org.obsidium.window.Window;

public class ImageTest {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();

        Surface logo = new Surface(200, 200);

        logo.blit(Transform.scale(Image.logo(), 200, 200), 0, 0);

        float deg = 0;

        Clock clock = new Clock();

        while(true) {
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) {
                    window.quit();
                }
            }
            Draw.fill(window, new Color());

            Surface rotated = Transform.rotate(logo, deg++);


            int x = (int)(window.getWidth() / 2 - rotated.getWidth() / 2);

            int y = (int)(window.getHeight() / 2 - rotated.getHeight() / 2);

            window.blit(rotated, x, y);

            window.flip();

            clock.tick();

            System.out.println(clock.getFPS());
        }
    }
}
