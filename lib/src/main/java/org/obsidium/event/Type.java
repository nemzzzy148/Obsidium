package org.obsidium.event;

/** 
 * An enumerator that contains all the possible types of events.
 * 
 * @since 1.0
 */
public enum Type {
    /**
     * Activates when the window is being closed.
     */
    QUIT,
    KEY,
    KEY_DOWN,
    KEY_UP,
    MOUSE_DOWN,
    MOUSE_UP,
    WINDOW_MAXIMIZED,
    WINDOW_RESIZED,
    WINDOW_MINIMIZED,
    WINDOW_SHOWN,
    WINDOW_MOVED,
    WINDOW_RESTORED,
    WINDOW_FOCUSED,
    WINDOW_UNFOCUSED,
    WINDOW_FULL_SCREEN
}
