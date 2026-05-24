package org.obsidium.window;

// helper class for private methods bc the window class got to long, from version 1.2
class WindowHelper {
    static int awtValue(State state) {
        int s = 0;
        switch (state) {
            case ICONIFIED -> s = 1;
            case MAXIMIZED -> s = 6;
            case FULL_SCREEN -> s = -1;
        }
        return s;
    }
}
