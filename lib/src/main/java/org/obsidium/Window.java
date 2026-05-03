package org.obsidium;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.image.BufferStrategy;

import org.obsidium.event.Events;
import org.obsidium.event.Mouse;
import org.obsidium.geometry.Vector2;
import org.obsidium.graphics.Surface;

public class Window {
    // window props
    private String title = "Obsidium Game";

    public void setTitle(String title) {
        frame.setTitle(title);
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    private int width = 800;

    public int getWidth() {
        return width;
    }

    private int heigth = 600;

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

    // window extentions

    public Events events;
    public Mouse mouse;

    public Window(int width, int height, String title, boolean stopProgramOnClose) {
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
        frame.setVisible(true);


        canvas.createBufferStrategy(2);
        bufferStrategy = canvas.getBufferStrategy();

        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();

        events = new Events(frame, canvas);
        mouse = new Mouse(frame);
    }

    // showing drawn image 

    public void flip() {
        if (disabled)
            return;
        graphics2D.dispose();
        graphics2D = null;
        bufferStrategy.show();
        graphics2D = (Graphics2D) bufferStrategy.getDrawGraphics();
    }

    // graphics 

    public Graphics2D getGraphics2D() {
        return graphics2D;
    }

    public void blit(Surface source, int x, int y) {
        if (source == null) return;
        graphics2D.drawImage(source.getBufferedImage(),null, x, y);
    }

    // handy features

    public Vector2 getCenter() {
        return new Vector2(width/2, heigth/2);
    }

    public void setPos(int x, int y) {
        frame.setLocation(x, y);
    }

    public Vector2 getPos() {
        return new Vector2(getPosX(), getPosY());
    }

    public int getPosX() {
        return frame.getLocation().x;
    }
    public int getPosY() {
        return frame.getLocation().y;
    }

    // close

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