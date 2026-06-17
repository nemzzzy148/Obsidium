package org.obsidium.event;

import org.obsidium.math.Vector2;
import org.obsidium.window.Window;

import javax.swing.*;
import java.awt.Canvas;
import java.awt.Frame;
import java.awt.event.*;
import java.util.LinkedList;
import java.util.List;

/** 
 * A class that manages the events of windows.
 * <b>---advanced---</b>
 * This class should only be instantiated by Obsidium.
 */
public class Events {
    private final Window window;

    /**
     * <b>---advanced---</b>
     * This constructor should only be instantiated by Obsidium.
     */
    public Events(Window window) {
        this.window = window;
        addEventListener(window.getFrame(), window.getCanvas());
    }

    // events this frame
    private final LinkedList<Event> events = new LinkedList<>();

    private final LinkedList<Event> keys = new LinkedList<>();
    private final LinkedList<Event> pressedKeys = new LinkedList<>();
    private final LinkedList<Event> releasedKeys = new LinkedList<>();

    // thread safety

    private final Object lock = new Object();

    private void addEventListener(Frame frame, Canvas canvas) {
        // window
        frame.addWindowListener(new WindowAdapter(){
            @Override
            public void windowClosing(WindowEvent e) {
                simpleEvent( Type.QUIT );
            }
        });

        // fullscreen window
        frame.addWindowStateListener(new WindowStateListener() {
            @Override
            public void windowStateChanged(WindowEvent e) {
                int newState = e.getNewState();
                int oldState = e.getOldState();
                boolean wasMax = (oldState & Frame.MAXIMIZED_BOTH) == Frame.MAXIMIZED_BOTH;
                boolean isMax = (newState & Frame.MAXIMIZED_BOTH) == Frame.MAXIMIZED_BOTH;


                if (isMax && !wasMax) {
                    simpleEvent( Type.WINDOW_MAXIMIZED );
                }
                if (!isMax && wasMax) {
                    simpleEvent(Type.WINDOW_RESTORED);
                }
            }
        });

        //ui

        frame.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {

            }
        });

        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowIconified(WindowEvent e) {
                simpleEvent( Type.WINDOW_MINIMIZED );
            }

            @Override
            public void windowDeiconified(WindowEvent e) {
                simpleEvent( Type.WINDOW_RESTORED );
            }

            @Override
            public void windowActivated(WindowEvent e) {
                simpleEvent( Type.WINDOW_FOCUSED );
            }

            @Override
            public void windowDeactivated(WindowEvent e) {
                simpleEvent( Type.WINDOW_UNFOCUSED );
            }
        });

        frame.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                simpleEvent( Type.WINDOW_RESIZED );
            }

            @Override
            public void componentMoved(ComponentEvent e) {
                simpleEvent( Type.WINDOW_MOVED );
            }
        });

        // key
        canvas.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                Key k = keyEventToKey(e);
                if (k != null) {
                    keyEvent( new Event(Type.KEY_DOWN, k));
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                Key k = keyEventToKey(e);
                if (k != null) {
                    keyEvent( new Event(Type.KEY_UP, k));
                }
            }
        });

        // mouse
        canvas.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                events.add( new Event(Type.MOUSE_DOWN, window.mouse.getPos()) );
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                events.add( new Event(Type.MOUSE_UP, window.mouse.getPos()) );
            }
        });
    }
    private Key keyEventToKey(KeyEvent e) {
        int keyCode = e.getKeyCode();
        Key k = null;
        switch (keyCode) {
            case KeyEvent.VK_UP -> k = Key.UP;
            case KeyEvent.VK_DOWN -> k = Key.DOWN;
            case KeyEvent.VK_LEFT -> k = Key.LEFT;
            case KeyEvent.VK_RIGHT -> k = Key.RIGHT;  
            case KeyEvent.VK_BACK_SPACE -> k = Key.BACKSPACE; 
            case KeyEvent.VK_TAB -> k = Key.TAB; 
            case KeyEvent.VK_ESCAPE -> k = Key.ESCAPE; 
            case KeyEvent.VK_SPACE -> k = Key.SPACE; 
            case KeyEvent.VK_ENTER -> k = Key.ENTER; 
            case KeyEvent.VK_DELETE -> k = Key.DELETE; 
            case KeyEvent.VK_SHIFT -> k = Key.SHIFT;
            case KeyEvent.VK_CAPS_LOCK -> k = Key.CAPS_LOCK;
            case KeyEvent.VK_0 -> k = Key._0;
            case KeyEvent.VK_1 -> k = Key._1;
            case KeyEvent.VK_2 -> k = Key._2;
            case KeyEvent.VK_3 -> k = Key._3;
            case KeyEvent.VK_4 -> k = Key._4;
            case KeyEvent.VK_5 -> k = Key._5;
            case KeyEvent.VK_6 -> k = Key._6;
            case KeyEvent.VK_7 -> k = Key._7;
            case KeyEvent.VK_8 -> k = Key._8;
            case KeyEvent.VK_9 -> k = Key._9;
            case KeyEvent.VK_A -> k = Key.A;
            case KeyEvent.VK_B -> k = Key.B;
            case KeyEvent.VK_C -> k = Key.C;
            case KeyEvent.VK_D -> k = Key.D;
            case KeyEvent.VK_E -> k = Key.E;
            case KeyEvent.VK_F -> k = Key.F;
            case KeyEvent.VK_G -> k = Key.G;
            case KeyEvent.VK_H -> k = Key.H;
            case KeyEvent.VK_I -> k = Key.I;
            case KeyEvent.VK_J -> k = Key.J;
            case KeyEvent.VK_K -> k = Key.K;
            case KeyEvent.VK_L -> k = Key.L;
            case KeyEvent.VK_M -> k = Key.M;
            case KeyEvent.VK_N -> k = Key.N;
            case KeyEvent.VK_O -> k = Key.O;
            case KeyEvent.VK_P -> k = Key.P;
            case KeyEvent.VK_Q -> k = Key.Q;
            case KeyEvent.VK_R -> k = Key.R;
            case KeyEvent.VK_S -> k = Key.S;
            case KeyEvent.VK_T -> k = Key.T;
            case KeyEvent.VK_U -> k = Key.U;
            case KeyEvent.VK_V -> k = Key.V;
            case KeyEvent.VK_W -> k = Key.W;
            case KeyEvent.VK_X -> k = Key.X;
            case KeyEvent.VK_Y -> k = Key.Y;
            case KeyEvent.VK_Z -> k = Key.Z;
            case KeyEvent.VK_F1 -> k = Key.F1;
            case KeyEvent.VK_F2 -> k = Key.F2;
            case KeyEvent.VK_F3 -> k = Key.F3;
            case KeyEvent.VK_F4 -> k = Key.F4;
            case KeyEvent.VK_F5 -> k = Key.F5;
            case KeyEvent.VK_F6 -> k = Key.F6;
            case KeyEvent.VK_F7 -> k = Key.F7;
            case KeyEvent.VK_F8 -> k = Key.F8;
            case KeyEvent.VK_F9 -> k = Key.F9;
            case KeyEvent.VK_F10 -> k = Key.F10;
            case KeyEvent.VK_F11 -> k = Key.F11;
            case KeyEvent.VK_F12 -> k = Key.F12;
        }
        return k;
    }

    /**
     * Adds a simple event to the event list.
     * <p>A simple event is an event with only a set type.</p>
     * @param type that the event will contain
     * @since 1.0
     */
    public void simpleEvent(Type type) {
        synchronized (lock) {
            events.add( new Event(type) );
        }
    }

    private void keyEvent(Event e) {
        synchronized (lock) {
            if (e.type == Type.KEY_DOWN) {
                if (!keyContains(e.key)) {
                    pressedKeys.add(e);
                }
                keys.add( new Event(Type.KEY, e.key));
            }
            else if (e.type == Type.KEY_UP) {
                if (keyContains(e.key)) {
                    releasedKeys.add(e);
                }
                keys.removeIf(ev -> ev.key == e.key);
            }
        }
        
    }

    private boolean keyContains(Key k) {
        for (Event e : keys) {
            if (e.key == k) return true;
        }
        return false;
    }
    
    /**
     * Clears the event list without receiving the accumulated events.
     * <p> If this method is called, it will clear the event list without receiving the accumulated events.
     * If this method or {@link #get()} isn't called every frame, events will be accumulated without being cleared.</p>
     * 
     * @since 1.0
     */
    public void clear() {
        synchronized (lock) {
            events.clear();
            releasedKeys.clear();
            pressedKeys.clear();
        }
    }

    /** 
     * Returns all the events that happened in this frame.
     * <p> When this method is called all the events are cleared.
     * After this process it is ready to receive new events.</p>
     * @see Event
     * 
     * @return an array of all the {@link Event}
     * @since 1.0
    */
    public List<Event> get() {
        synchronized (lock) {
            List<Event> allEvents = new LinkedList<>() ;
            allEvents.addAll(events);
            allEvents.addAll(pressedKeys);
            allEvents.addAll(releasedKeys);
            allEvents.addAll(keys);

            // mouse
            allEvents.add( new Event(Type.MOUSE, window.mouse.getPos()) );

            events.clear();
            releasedKeys.clear();
            pressedKeys.clear();

            return allEvents;
        }
    }

    /** 
     * Returns an array of keys that were pressed this frame.
     * 
     * <p> This will not clear the event list!
     * Meaning it will not reset the events to receive new ones the next frame.
     * If you want to clear the event list use {@link #get()} of {@link #clear()}.</p>
     * @return an array of pressed keys
     * 
     * @since 1.0
     */
    public Event[] getPressed() {
        synchronized (lock) {
            return keys.stream().map(e -> new Event(Type.KEY, e.key)).toArray(Event[]::new);
        }
    }
}