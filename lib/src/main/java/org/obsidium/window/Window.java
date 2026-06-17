package org.obsidium.window;

import org.obsidium.Obsidium;
import org.obsidium.event.Events;
import org.obsidium.event.Mouse;
import org.obsidium.event.Type;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.graphics.surface.SimpleSurface;
import org.obsidium.graphics.surface.Surface;
import org.obsidium.math.Vector2;
import org.obsidium.ui.UI;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;

import static org.obsidium.window.WindowHelper.awtValue;

/**
 * A window object that represents a window on your screen.
 * <p><b>Note:</b> You should not instantiate this object yourself, instead use {@link Obsidium#createWindow()}</p>
 */
public class Window extends SimpleSurface {
    // window props
    private String title = "Window";
    private State state = State.NORMAL;
    private boolean fullScreen = false;
    private boolean disabled = false;
    private boolean hideBar = false;

    private final JFrame frame;
    private final Canvas canvas;
    private final BufferStrategy bufferStrategy;

    private boolean stopProgramOnClose = false;

    private boolean resizable = false;

    // window extensions

    public Events events;
    public Mouse mouse;
    public UI ui;

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
     * @param state
     *
     * @since 1.0
     */
    public Window(int width, int height, String title, int x, int y, boolean resizable, boolean stopProgramOnClose, boolean hideBar, State state) {
        this.title = title;
        this.width = width;
        this.height = height;
        this.stopProgramOnClose = stopProgramOnClose;
        frame = new JFrame();
        frame.setTitle(title);

        frame.setUndecorated(hideBar);

        frame.setLayout( new GridBagLayout() );

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;

        gbc.weightx = 1.0;
        gbc.weighty = 1.0;

        gbc.fill = GridBagConstraints.BOTH;

        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(true);

        frame.add(canvas, gbc);

        frame.pack();
        frame.setResizable(resizable);

        setPos(x, y);

        events = new Events(this);
        mouse = new Mouse(this);
        ui = new UI(this);

        frame.setVisible(true);
        canvas.requestFocus();

        setState(state);

        canvas.createBufferStrategy(2);
        bufferStrategy = canvas.getBufferStrategy();
        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();
    }

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

    /**
     * Changes the width of the window manually.
     * @param width that will be applied to the window
     * @since 1.2
     */
    public void setWidth(int width) {
        frame.setSize(width, height);
        this.width = width;
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
        setSize(size.x, size.y);
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

    /**
     * Returns the state of the window.
     * @return {@link State}
     * @since 1.2
     */
    public State getState() { return state; }

    /**
     * Sets the state of the window.
     * <p>As an example you could fullscreen it, minimize it, etc.</p>
     * @param state that the window will become
     * @since 1.2
     */
    public void setState(State state) {
        int s = awtValue(state);
        if (s > -1) {
            setFullScreen(false);
            frame.setExtendedState(s);
        }
        else if (s == -1) {
            setFullScreen(true);
        }
        this.state = state;
    }

    /**
     * Returns {@code true} if the window is full screened, otherwise returns {@code false}.
     * @return {@code true} if the window is full screened, otherwise {@code false}
     * @since 1.2
     * @see #setFullScreen(boolean)
     */
    public boolean getFullScreen() { return fullScreen; }

    /**
     * This method enables / disables fullscreen mode.
     * @param enabled if the window will go into fullscreen mode
     * @since 1.2
     * @see #setState(State) 
     */
    public void setFullScreen(boolean enabled) {
        if ((!enabled && !fullScreen) || (enabled && fullScreen)) return;

        GraphicsDevice gd =  GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
        if (!gd.isFullScreenSupported()) {
            System.err.println("Obsidium full-screen error: device does not support full-screen!");
            return;
        }
        frame.setVisible(false);
        frame.dispose();

        if (enabled && !fullScreen) {
            setHideBar(true);
            gd.setFullScreenWindow(frame);
            width = frame.getWidth();
            height = frame.getHeight();
            if (events != null) {
                events.simpleEvent(Type.WINDOW_FULL_SCREEN);
            }
            fullScreen = true;
        } else {
            setHideBar(false);
            gd.setFullScreenWindow(null);
            frame.setSize(width, height);
            setPos(getCenter().x, getCenter().y);
            if (events != null) {
                events.simpleEvent(Type.WINDOW_RESTORED);
            }
            fullScreen = false;
        }
        frame.setVisible(true);
    }

    /**
     * Returns {@code true} if the window's frame(the bar) is hidden, otherwise {@code false}.
     * <p><b>Note:</b>After the window isn't full screened anymore, it will show the frame(even when you have previously disabled it).</p>
     * @return {@code true} if the window's frame(the bar) is hidden, otherwise {@code false}.
     * @since 1.2
     * @see #setHideBar(boolean) 
     */
    public boolean getHideBar() { return hideBar; }

    /**
     * Changes the visibility of the bar.
     * <p>If {@code true}, the window's bar will become invisible, otherwise it will become visible again.</p>
     * @param hideBar if the bar should be hidden
     * @since 1.2
     * @see #getHideBar()
     */
    public void setHideBar(boolean hideBar) { frame.setUndecorated(hideBar); this.hideBar = hideBar; }

    /**
     * Returns if the program stops when the window is closed.
     * @return getStopProgramOnClose
     * @since 1.2
     */
    public boolean getStopProgramOnClose() {
        return stopProgramOnClose;
    }

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

    // showing drawn image 

    /**
     * Shows the content on the screen that you have been drawing to.
     * <p> Flips the image to the screen that you have been drawing to.
     * When you draw to the screen, it isn't displayed instantly because you're actually drawing onto another 'screen' that is filled with the current 'screen' that is displayed before the method is executed.
     * This is called double buffering.</p>
     * <p>If the window is closed, this method will just return without having done anything.</p>
     * <p><b>Note:</b> When you flip the screen, the old 'screen' is neither wiped nor deleted. Therefore, before flipping again, you should draw a background onto it or fill it with a color.</p>
     * @see Draw#fill(SimpleSurface, Color)
     * @since 1.0
     */
    public void flip() {
        if (disabled) return;

        graphics2D.dispose();
        bufferStrategy.show();
        width = frame.getWidth();
        height = frame.getHeight();
        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();
    }

    public void clear(Color color) {
        Draw.fill(this, color);
    }

    public void clear() {
        Draw.fill(this, Color.WHITE);
    }

    // graphics
    /**
     * <b>---advanced---</b>
     * Returns the canvas that the window uses.
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return the {@link Canvas} that is being used
     * @since 1.2
     */
    public Canvas getCanvas() { return canvas; }

    /**
     * <b>---advanced---</b>
     * Returns the AWT frame that is being used by the window.
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * @return the {@link JFrame} that is being used
     * @since 1.2
     */
    public JFrame getFrame() { return frame; }

    /**
     * Captures the current frame and paints it on a {@link Surface}.
     * @return {@link Surface} containing the frame
     * @since 1.2
     */
    public Surface capture() {
        int w = Math.max(1, canvas.getWidth());
        int h = Math.max(1, canvas.getHeight());

        BufferedImage bF = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = bF.createGraphics();

        canvas.printAll(g2d);
        g2d.dispose();

        return new Surface(bF);
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

        if (graphics2D != null) graphics2D.dispose();
        bufferStrategy.dispose();
        frame.dispose();
        Obsidium.closeWindow(this);

        disabled = true;
    }
}