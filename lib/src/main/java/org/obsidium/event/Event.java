package org.obsidium.event;

import java.util.Objects;

public class Event {
    public Type type;
    public Key key;
    public Event(Type type, Key key) {
        this.type = type;
        this.key = key;
    }
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
