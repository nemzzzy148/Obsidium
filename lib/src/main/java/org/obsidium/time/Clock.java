package org.obsidium.time;

public class Clock {
    private long lastTime;
    private double deltaTime;

    public Clock() {
        lastTime = System.nanoTime();
    }

    public double tick() {
        long currentTime = System.nanoTime();
        long diff = currentTime - lastTime;

        if (diff <= 0) diff = 1;

        deltaTime = diff / 1_000_000.0;
        lastTime = currentTime;
        return deltaTime;
    }
    public double tick(double targetFPS) {
        double targetNanos = 1_000_000_000.0 / targetFPS;

        while (System.nanoTime() - lastTime < targetNanos) {
            Thread.yield();
        }

        return tick();
    }
    public double getFPS() {
        return 1_000.0 / deltaTime;
    }
    public double getDeltaTime() {
        return deltaTime;
    }
}
