package org.obsidium.event;

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
}
