package org.obsidium.window;

import java.awt.*;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;

import org.obsidium.Obsidium;
import org.obsidium.event.Event;
import org.obsidium.event.Events;
import org.obsidium.event.Mouse;
import org.obsidium.event.Type;
import org.obsidium.geometry.Vector2;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.graphics.Surface;

/**
 * A window object that represents a window on your screen.
 * <p><b>Note:</b> You should not instantiate this object yourself, instead use {@link Obsidium#createWindow()}</p>
 */
public class Window {
    // window props
    private String title = "Obsidium Game";

    /**
     * Sets the window title.
     * @param title the title to be displayed in the windows border
     * @see #getTitle()
     * @since 1.0
     */
    public void setTitle(String title) {
        frame.setTitle(title);
        this.title = title;
    }

    /**
     * Returns the windows title.
     * @return the title of the window
     * @since 1.0
     */
    public String getTitle() {
        return title;
    }

    private int width = 800;

    /** 
     * Returns the width in pixels of the window.
     * @return the width in pixels
     * @see #getHeight()
     * @since 1.0
    */
    public int getWidth() {
        return width;
    }

    /**
     * Changes the width of the window manually.
     * @param width that will be applied to the window
     * @since 1.2
     */
    public void setWidth(int width) {
        frame.setSize(width, height);
        this.width = width;
    }

    private int height = 600;

    /**
     * Returns the height in pixels of the window.
     * @return the height in pixels
     * @see #getWidth()
     * @since 1.0
     */
    public int getHeight() {
        return height;
    }

    /**
     * Changes the height of the window manually.
     * @param height that will be applied to the window
     * @since 1.2
     */
    public void setHeight(int height) {
        frame.setSize(width, height);
        this.height = height;
    }

    /**
     * Changes the width and height of the window manually.
     * @param width that will be applied to the window
     * @param height that will be applied to the window
     * @since 1.2
     */
    public void setSize(int width, int height) {
        frame.setSize(width, height);
        this.width = width;
        this.height = height;
    }

    /**
     * Changes the width and height of the window manually with a vector.
     * @param size in {@link Vector2} that will be the dimensions of the window
     * @since 1.2
     */
    public void setSize(Vector2 size) {
        frame.setSize(size.x, size.y);
        this.width = size.x;
        this.height = size.y;
    }

    /**
     * Returns the windows dimensions in {@link Vector2} form.
     * @return {@link Vector2} that contains the dimensions
     * @since 1.2
     */
    public Vector2 getSize() {
        return new Vector2(this.width, this.height);
    }

    /**
     * Returns the position that the window would need to be at, to be at the center of the screen.
     *
     * @return a {@link Vector2} containing the coordinates of the window's center position.
     * @since 1.0
     */
    public final Vector2 getCenter() {
        return new Vector2(Obsidium.getScreenSize().x/2 - width/2, Obsidium.getScreenSize().y/2 - height/2);
    }

    /**
     * Sets the position of the window, relative to the primary screen.
     * @param x the x-coordinate for the window position
     * @param y the y-coordinate for the window position
     * @since 1.0
     */
    public final void setPos(int x, int y) {
        frame.setLocation(x, y);
    }

    /**
     * Returns the position of the window, relative to the primary screen.
     * @return a {@link Vector2} containing the coordinates of the window's position
     * @since 1.0
     */
    public final Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    /**
     * Returns the individual x-coordinate of the window, relative to the primary screen.
     * @return a number that contains the x-coordinate of the window's position in pixels
     * @since 1.0
     */
    public final int getPosX() {
        return frame.getLocation().x;
    }

    /**
     * Returns the individual y-coordinate of the window, relative to the primary screen.
     * @return a number that contains the y-coordinate of the window's position in pixels
     * @since 1.0
     */
    public final int getPosY() {
        return frame.getLocation().y;
    }

    private State state = State.NORMAL;

    /**
     * Returns the state of the window.
     * @return {@link State}
     * @since 1.2
     */
    public State getState() { return state; }

    /**
     * Sets the state of the window.
     * @param state that the window will become
     * @since 1.2
     */
    public void setState(State state) {
        int s = awtValue(state);
        if (s > -1) {
            fullScreen(false);
            frame.setExtendedState(s);
        }
        else if (s == -1) {
            fullScreen(true);
        }
        this.state = state;
    }

    private int awtValue(State state) {
        int s = 0;
        switch (state) {
            case ICONIFIED -> s = 1;
            case MAXIMIZED -> s = 6;
            case FULL_SCREEN -> s = -1;
        }
        return s;
    }

    private void fullScreen(boolean enabled) {
        GraphicsDevice gd =  GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
        if (!gd.isFullScreenSupported()) {
            System.err.println("Obsidium full-screen error: device does not support full-screen!");
            return;
        }
        frame.setVisible(false);
        frame.dispose();

        if (enabled) {
            setHideBar(true);
            gd.setFullScreenWindow(frame);
        } else {
            setHideBar(false);
            gd.setFullScreenWindow(null);
            frame.setSize(width, height);
            setPos(getCenter().x, getCenter().y);
        }
        frame.setVisible(true);

        if (events != null) {
            events.simpleEvent(Type.WINDOW_FULL_SCREEN);
        }
    }

    private boolean hideBar = false;

    public boolean getHideBar() { return hideBar; }

    public void setHideBar(boolean hideBar) { frame.setUndecorated(hideBar); this.hideBar = hideBar; }


    private boolean disabled = false;

    // on creation vars

    private final Frame frame;
    private final Canvas canvas;
    private final BufferStrategy bufferStrategy;
    private Graphics2D graphics2D = null;

    private boolean stopProgramOnClose = false;

    /**
     * Returns if the program stops when the window is closed.
     * @return getStopProgramOnClose
     * @since 1.2
     */
    public boolean getStopProgramOnClose() {
        return stopProgramOnClose;
    }

    private boolean resizable = false;

    /**
     * Returns if the window can be resized by the used.
     * @return resizable
     * @see #setResizable(boolean)
     * @since 1.2
     */
    public boolean getResizable() {
        return resizable;
    }

    /**
     * Sets whether this window can be resized by the user.
     * @param resizable {@code true} if this window is resizable, {@code false} otherwise
     * @see #getResizable()
     * @since 1.2
     */
    public void setResizable(boolean resizable) {
        this.resizable = resizable;
        frame.setResizable(resizable);
    }

    // window extensions

    public Events events;
    public Mouse mouse;

    /**
     * Creates a new window
     * <p><b>Note:</b> This is an internal library method. To create a window, 
     *          use {@link Obsidium#createWindow()} instead.</p>
     * 
     * <p><strong>Warning:</strong> Using this method directly is unsupported. 
     * Windows created here are not tracked by the internal registry, which 
     * will prevent the program from terminating correctly and lead to errors.</p>
     *
     * @param width
     * @param height
     * @param title
     * @param x
     * @param y
     * @param resizable
     * @param stopProgramOnClose
     * @param hideBar
     * 
     * @since 1.0
     */
    public Window(int width, int height, String title, int x, int y, boolean resizable, boolean stopProgramOnClose, boolean hideBar, State state) {
        this.title = title;
        this.width = width;
        this.height = height;
        this.stopProgramOnClose = stopProgramOnClose;
        frame = new Frame();
        frame.setTitle(title);

        frame.setUndecorated(hideBar);
        
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(true);

        frame.add(canvas);

        frame.pack();
        frame.setResizable(resizable);

        setPos(x, y);

        frame.setVisible(true);
        canvas.requestFocus();
        setState(state);

        canvas.createBufferStrategy(2);
        bufferStrategy = canvas.getBufferStrategy();

        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();

        events = new Events(frame, canvas);
        mouse = new Mouse(frame);
    }

    // showing drawn image 

    /**
     * Shows the content on the screen that you have been drawing to.
     * <p> Flips the image to the screen that you have been drawing to.
     * When you draw to the screen, it isn't displayed instantly because you're actually drawing onto another 'screen' that is filled with the current 'screen' that is displayed before the method is executed.
     * This is called double buffering.</p>
     * <p>If the window is closed, this method will just return without having done anything.</p>
     * <p><b>Note:</b> When you flip the screen, the old 'screen' is neither wiped nor deleted. Therefore, before flipping again, you should draw a background onto it or fill it with a color.</p>
     * @see Draw#fill(Window, Color)
     * @since 1.0
     */
    public void flip() {
        if (disabled)
            return;
        graphics2D.dispose();
        graphics2D = null;
        bufferStrategy.show();
        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();
    }

    // graphics 

    /**
     * <b>---advanced---</b>
     * Returns the screen's {@code Graphics2D}.
     * <p> Only use this if you know what you are doing </p>
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return Graphics2D
     * @since 1.0
     */
    public Graphics2D getGraphics2D() { return graphics2D; }

    /**
     * <b>---advanced---</b>
     * Returns the canvas that the window uses.
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return the {@link Canvas} that is being used
     * @since 1.2
     */
    public Canvas getCanvas() { return canvas; }

    /**
     * Blits a surface to the window.
     * <p> This method is designed to be used for 'pasting' a surface onto a window. 
     * For example, if you want to draw a sprite to the screen for the user to see it. </p>
     *
     * @param source the surface that you want to blit to the screen.
     * @param x the x coordinate that specifies where you want the image to be blitted
     * @param y the y coordinate that specifies where you want the image to be blitted
     * @since 1.0
     */
    public void blit(Surface source, int x, int y) {
        if (source == null) return;
        graphics2D.drawImage(source.getBufferedImage(),null, x, y);
    }

    public Surface capture() {
        BufferedImage bI = new BufferedImage(
                width,
                height,
                BufferedImage.TYPE_INT_ARGB
        );
        Graphics2D g2D = bI.createGraphics();
        canvas.paint(g2D);
        return new Surface(bI);
    }


    // close

    /**
     * Closes the current window.
     * <p> If this is the last window that is open, the program will be closed.
     * Or if you have enabled {@code stopProgramOnClose}, than the program will close immediately even if there are still windows open.</p>
     *
     * <p>You can still blit to the window or execute other methods of the window after it being closed, but flipping it or quitting it again will result in nothing being done or an error being printed.<p>
     * @since 1.0
     */
    public void quit() {
        if (disabled) {
            System.err.println("Obsidium error: trying to close window that was already closed");
        }

        graphics2D.dispose();
        bufferStrategy.dispose();
        frame.dispose();
        Obsidium.closeWindow(this);

        disabled = true;
    }
}