package org.obsidium.event;

/** 
 * An enumerator that contains all the possible types of events.
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
    MOUSE,
    MOUSE_DOWN,
    MOUSE_UP,
    WINDOW_MAXIMIZED,
    WINDOW_RESIZED,
    WINDOW_MINIMIZED,
    WINDOW_SHOWN,
    WINDOW_MOVED,
    /**
     * Activates when a window returns to its normal state.
     */
    WINDOW_RESTORED,
    WINDOW_FOCUSED,
    WINDOW_UNFOCUSED,
    WINDOW_FULL_SCREEN,
    PRESSED_UI_COMPONENT,
    RELEASED_UI_COMPONENT
}
