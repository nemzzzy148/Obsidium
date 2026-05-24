![banner](lib/src/main/resources/images/banner.png)
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

## Platforms:
  - [Discord](https://discord.gg/cW5HUxqZHp)
  - [Documentation website](https://nemzzzy148.github.io/ObsidiumDocumentation/)

## Pygame vs Obsidium

### Obsidium in kotlin:
```kotlin
package org.obsidium
import org.obsidium.event.*

fun main() {
  val window = Obsidium.createWindow()
    while (true) {
        for (e in window.events.get()) {
            if (e.type == Type.QUIT) window.quit()
        }
    }
}
```

### Obsidium in java:
```java
package org.obsidium;
import org.obsidium.event.*;

public class Game {
    public static void main(String[] args) {
        Window window = Obsidium.createWindow();

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

## Setup with IntelliJ
### 1. Create a project
Create a new Java or Kotlin project in IntelliJ IDEA.

### 2. Add the library to the project
- The library can be found in [Releases](https://github.com/nemzzzy148/Obsidium/releases).
- Place `Obsidium.jar` and `Obsidium-javadoc.jar` somewhere in your project, e.g. a `libs/` folder:
```
your-awesome-game/
  -libs/
    -Obsidium.jar
    -Obsidium-javadoc.jar
  -src/
```

### 3. Add the JAR to the project dependencies
1. Right click the `Obsidium.jar`
2. Select **Add as Library...**
3. Add it to the `your-awesome-game.main` module as a `project library`
4. Try to import it in your `Main.kt` or `Main.java`

### 4. Attach the Javadoc
Attaching the Javadoc JAR gives you built-in documentation while coding.
1. Go to **File -> Project Settings -> Libraries -> Obsidium**
2. Press **`+`** and select the `Obsidium-javadoc.jar`
3. Add it as JavaDoc
4. Try it out by hovering over a method from Obsidium

### 5. Run your project
After all that, you are ready to begin making a masterpiece!

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
