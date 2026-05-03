# Obsidium

Obsidium is a lightweight, CPU-rendered game library for Java, built on top of
the **Abstract Window Toolkit (AWT)**. It follows a structure similar to Pygame,
making it easy to pick up if you know Pygame.


## Example

```java
package org.obsidium;
import org.obsidium.event.*;

public class Game {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow(400, 400, "Obsidium");

        while (true) { 
            for (Event e : window.events.get()) {
                if (e.type == Type.QUIT) window.quit();
            }
        }
    }
}
```

```python

import pygame 

pygame.init()

pygame.display.set_mode((400,400))
pygame.display.set_caption("Pygame!")

running = True
while running:
    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            running = False

pygame.quit

```


