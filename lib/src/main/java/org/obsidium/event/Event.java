package org.obsidium.event;

import java.util.Objects;

/**
 * A class that represents an event
 * 
 * <p> This class contains 2 field specifying the type of event it is.
 * You can access the type of event with the {@code event.type}.
 * And if the type has something to do with a key, you can access it with {@code event.key}.
 * To compare these fields, you can use the enums {@link Type} and {@link Key}.
 * Example:
 * {@code if(event.type == Key.KEYDOWN) { if(event.key == Key.A) System.out.println("Pressed A");}}
 * <p>
 * ---advanced---
 * This class should only be instantiated by Obsidium.
 * @since 1.0
 */
public class Event {
    /**
     * The type of event.
     * <p>
     * Example:
     * {@code if(event.type == Key.QUIT) { window.quit(); }}
     * </p>
     */
    public Type type;

    /**
     * The key that is presses in this event
     * <p>
     * There would only be a key if the event type has something to do with a key being presses, released, ...
     * Example:
     * {@code if(event.type == Key.KEYDOWN) { if(event.key == Key.A) System.out.println("Pressed A");}}
     * </p>
     */
    public Key key;

    /**
     * ---advanced---
     * This constructor should only be instantiated by Obsidium.
     */
    public Event(Type type, Key key) {
        this.type = type;
        this.key = key;
    }
    
    /**
     * ---advanced---
     * This constructor should only be instantiated by Obsidium.
     */
    public Event(Type type) {
        this.type = type;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Event other)) return false;
        return this.type == other.type && this.key == other.key;
    }
    @Override
    public int hashCode() {
        return Objects.hash(type, key);
    }
}
