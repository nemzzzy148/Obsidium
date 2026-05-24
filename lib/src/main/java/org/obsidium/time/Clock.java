package org.obsidium.time;

/**
 * This class is used to work with time.
 * @since 1.0
 */
public class Clock {
    private long lastTime;
    private double deltaTime;

    /**
     * Creates a clock object.
     * @since 1.0
     */
    public Clock() {
        lastTime = System.nanoTime();
    }

    /**
     * Returns how many milliseconds this frame took to complete.
     * @return the amount of milliseconds this frame took to complete
     * @since 1.0
     */
    public double tick() {
        long currentTime = System.nanoTime();
        long diff = currentTime - lastTime;

        if (diff <= 0) diff = 1;

        deltaTime = diff / 1_000_000.0;
        lastTime = currentTime;
        return deltaTime;
    }

    /**
     * Synchronizes the games loop to a specific frame rate that you set.
     * 
     * @param targetFPS that it tries to approach
     * 
     * @return the amount of milliseconds this frame took to complete
     * 
     * @since 1.0
     */
    public double tick(double targetFPS) {
        double targetNanos = 1_000_000_000.0 / targetFPS;

        while (System.nanoTime() - lastTime < targetNanos) {
            Thread.yield();
        }

        return tick();
    }

    /**
     * Returns the current frames per second.
     * 
     * @return the current number of frames per second
     * 
     * @since 1.0
     */
    public double getFPS() {
        return 1_000.0 / deltaTime;
    }

    /**
     * Returns the time taken to complete the last frame.
     * 
     * @return the duration of the last frame in milliseconds.
     * 
     * @since 1.0
     */
    public double getDeltaTime() {
        return deltaTime;
    }
}
