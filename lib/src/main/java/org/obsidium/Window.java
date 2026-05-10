package org.obsidium;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.image.BufferStrategy;

import org.obsidium.event.Events;
import org.obsidium.event.Mouse;
import org.obsidium.geometry.Vector2;
import org.obsidium.graphics.Color;
import org.obsidium.graphics.Draw;
import org.obsidium.graphics.Surface;

/**
 * A window object that represents a window on your screen.
 * 
 * <p><b>Note:</b> You should not instantiate this object yourself, instead use {@link Obsidium#createWindow()}</p>
 */
public class Window {
    // window props
    private String title = "Obsidium Game";

    /**
     * Sets the window title.
     * 
     * @param title the title to be displayed in the windows border
     * 
     * @see #getTitle()
     * 
     * @since 1.0
     */
    public void setTitle(String title) {
        frame.setTitle(title);
        this.title = title;
    }

    /**
     * Returns the windows title.
     * 
     * @return the title of the window
     * 
     * @since 1.0
     */
    public String getTitle() {
        return title;
    }

    private int width = 800;

    /** 
     * Returns the width in pixels of the window.
     * 
     * @return the width in pixels
     * 
     * @see #getHeight()
     * 
     * @since 1.0
    */
    public int getWidth() {
        return width;
    }

    private int heigth = 600;

    /**
     * Returns the height in pixels of the window.
     * 
     * @return the height in pixels
     * 
     * @see #getWidth()
     * 
     * @since 1.0
     */
    public int getHeight() {
        return heigth;
    }

    private boolean disabled = false;

    // on creation vars

    private final Frame frame;
    private final Canvas canvas;
    private final BufferStrategy bufferStrategy;
    private Graphics2D graphics2D = null;

    public boolean stopProgramOnClose = false;

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
     * @param stopProgramOnClose
     * 
     * @since 1.0
     */
    public Window(int width, int height, String title, int x, int y, boolean stopProgramOnClose) {
        this.title = title;
        this.width = width;
        this.heigth = height;
        this.stopProgramOnClose = stopProgramOnClose;
        frame = new Frame(title);
        
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(true);
        canvas.requestFocus();

        frame.add(canvas);

        frame.pack();
        frame.setResizable(false);

        setPos(x, y);

        frame.setVisible(true);


        canvas.createBufferStrategy(2);
        bufferStrategy = canvas.getBufferStrategy();

        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();

        events = new Events(frame, canvas);
        mouse = new Mouse(frame);
    }

    // showing drawn image 

    /**
     * Shows the content on the screen that you have been drawing to.
     * 
     * <p> Flips the image to the screen that you have been drawing to.
     * When you draw to the screen, it isn't displayed instantly because you're actually drawing onto another 'screen' that is filled with the current 'screen' that is displayed before the method is executed.
     * This is called double buffering.
     * 
     * If the window is closed, this method will just return without having done anyting.</p>
     * 
     * <p><b>Note:</b> When you flip the screen, the old 'screen' is neither wiped nor deleted. Therefore, before flipping again, you should draw a background onto it or fill it with a color.</p>
     * 
     * @see Draw#fill(Window, Color)
     * 
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
     * ---advanced---
     * 
     * Returns the screen's {@code Graphics2D}.
     * <p> Only use this if you know what you are doing </p>
     * 
     * <p><b>Note:</b> Used for various methods in this library.</p>
     * 
     * @return Graphics2D
     */
    public Graphics2D getGraphics2D() {
        return graphics2D;
    }

    /**
     * Blits a surface to the window.
     * 
     * <p> This method is designed to be used for 'pasting' a surface onto a window. 
     * For example, if you want to draw a sprite to the screen for the user to see it. </p>
     * 
     * @param source the surface that you want to blit to the screen.
     * @param x the x coordinate that specifies where you want the image to be blitted
     * @param y the y coordinate that specifies where you want the image to be blitted
     * 
     * @since 1.0
     */
    public void blit(Surface source, int x, int y) {
        if (source == null) return;
        graphics2D.drawImage(source.getBufferedImage(),null, x, y);
    }

    // handy features

    /**
     * Returns the center of the window, relative to its own coordinate system.
     * 
     * <p> This method returns the width / 2 and the height / 2. </p>
     * 
     * @return a {@link Vector2} containing the coordinates of the window's center.
     * 
     * @since 1.0
     */
    public final Vector2 getCenter() {
        return new Vector2(width/2, heigth/2);
    }

    /**
     * Sets the position of the window, relative to the primary screen.
     * 
     * @param x the x-coordinate for the window position
     * @param y the y-coordinate for the window position
     * 
     * @since 1.0
     */
    public final void setPos(int x, int y) {
        frame.setLocation(x, y);
    }

    /**
     * Returns the positoin of the window, relative to the primary screen.
     * 
     * @return a {@link Vector2} containing the coordinates of the window's position
     * 
     * @since 1.0
     */
    public final Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    /**
     * Returns the individual x-coordinate of the window, relative to the primary screen.
     * 
     * @return a number that contains the x-coordinate of the window's position in pixels
     * 
     * @since 1.0
     */
    public final int getPosX() {
        return frame.getLocation().x;
    }

    /**
     * Returns the individual y-coordinate of the window, relative to the primary screen.
     * 
     * @return a number that contains the y-coordinate of the window's position in pixels
     * 
     * @since 1.0
     */
    public final int getPosY() {
        return frame.getLocation().y;
    }

    // close

    /**
     * Closes the current window.
     * <p> If this is the last window that is open, the program will be closed.
     * Or if you have enabled {@code stopProgramOnClose}, than the program will close immediately even if there are still windows open.
     * 
     * You can still blit to the window or execute other methods of the window after it being closed, but flipping it or quitting it again will result in nothing being done or an error being printed.<p>
     * 
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