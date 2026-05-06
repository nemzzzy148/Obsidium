# Obsidium

Obsidium is a lightweight, CPU-rendered game library for Java, built on top of
the **Abstract Window Toolkit (AWT)**. It follows a structure similar to Pygame,
making it easy to pick up if you know Pygame.

## Features:

- Multiple window creation
- Set and get window position
- Mouse on-screen position + separate window position
- Drawing on window (circle, square, image, polygon and line for now)
- Getting input (keys, window quit event, mouse)
- A clock for unlimited + set FPS
- Loading + transforming images (scale + rotate)
- Loading and playing, pausing, looping, stopping, and playing multiple audio clips simultaneously.
- Fonts (built-in and load ttf)
  
And for each component, more specific functionality. 

## Setup with Gradle
 
### 1. Create a Gradle project
 
If you don't have a project yet:
```bash
gradle init --type java-application
```
 
### 2. Add the JAR
 
Place the library(`Obsidium.jar`) in a `libs/` folder at the project root:
```
your-project/
- libs/
- Obsidium.jar
- src/
- build.gradle.kts
```
 
### 3. Configure `build.gradle.kts`
 
```kotlin
plugins {
    java
    application
}
 
application {
    mainClass.set("org.obsidium.Game") // Change to your main class
}
 
dependencies {
    implementation(files("libs/Obsidium.jar"))
}
```
 
### 4. Run your project
 
```bash
./gradlew run
```


## Example

### Obsidium in java:
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

### Pygame in python:
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
