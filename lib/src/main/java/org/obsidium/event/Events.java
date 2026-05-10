package org.obsidium.event;

import java.awt.Canvas;
import java.awt.Frame;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.LinkedList;

/** 
 * A class that manages the events of windows.
 * 
 * ---advanced---
 * 
 * This class should only be instantiated by Obsidium.
 */
public class Events {
    private final Frame frame;
    private final Canvas canvas;

    /**
     * ---advanced---
     * 
     * This constructor should only be instantiated by Obsidium.
     */
    public Events(Frame frame, Canvas canvas) {
        this.frame = frame;
        this.canvas = canvas;

        addEventListener(this.frame, this.canvas);
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
                synchronized (lock) {
                    events.add( new Event(Type.QUIT) );
                }
            }
        });

        // key
        canvas.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                Key k = keyEventToKey(e);
                if (k != null) {
                    keyEvent( new Event(Type.KEYDOWN, k));
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                Key k = keyEventToKey(e);
                if (k != null) {
                    keyEvent( new Event(Type.KEYUP, k));
                }
            }
        });

        // mouse
        canvas.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouseEvent( new Event(Type.MOUSEDOWN) );
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                mouseEvent( new Event(Type.MOUSEUP));
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

    private void mouseEvent(Event e) {
        synchronized (lock) {
            events.add(e);
        }
    }

    private void keyEvent(Event e) {
        synchronized (lock) {
            if (e.type == Type.KEYDOWN) {
                if (!keyContains(e.key)) {
                    pressedKeys.add( new Event(Type.KEY, e.key) );
                }
                keys.add(e);

            }
            else if (e.type == Type.KEYUP) {
                if (keyContains(e.key)) {
                    releasedKeys.add(e);
                }
                keys.remove(e);
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
     * 
     * <p> If this method is called, it will clear the event list without receiving the accumulated events.
     * 
     * If this method or {@link #get()} isn't called every frame, events will accumulated without being cleared.</p>
     * 
     * @since 1.0
     */
    public void clear() {
        events.clear();
        releasedKeys.clear();
        pressedKeys.clear();
    }

    /** 
     * Returns all the events that happend in this frame.
     * 
     * <p> When this method is called all the events are cleared.
     * After this process it is ready to receive new events.</p>
     * 
     * @see Event
     * 
     * @return an array of all the {@link Event}
     * 
     * @since 1.0
    */
    public Event[] get() {
        synchronized (lock) {
            LinkedList<Event> allEvents = new LinkedList<>();
            allEvents.addAll(events);
            allEvents.addAll(pressedKeys);
            allEvents.addAll(releasedKeys);
            allEvents.addAll(keys);
            Event[] e = allEvents.toArray(Event[]::new);
            clear();
            return e;
        }
    }

    /** 
     * Returns an array of keys that were pressed this frame.
     * 
     * <p> This will not clear the event list!
     * Meaning it will not reset the events to receive new ones the next frame.
     * If you want to clear the event list use {@link #get()} of {@link #clear()}.</p>
     * 
     * @return an array of pressed keys
     * 
     * @since 1.0
     */
    public Event[] getPressed() {
        synchronized (lock) {
            return keys.toArray(Event[]::new);
        }
    }
}