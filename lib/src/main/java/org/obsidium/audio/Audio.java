package org.obsidium.audio;

import java.nio.file.Path;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.FloatControl;

public class Audio {
    private Clip clip;
    private float volume = 1.0f;

    public Audio(String path) {
        Path p = Path.of(path);
        try (AudioInputStream audioStream = AudioSystem.getAudioInputStream(p.toFile())) {
            clip = AudioSystem.getClip();
            clip.open(audioStream);
        }
        catch (Exception e) {
            System.err.println("Obsidium audio loading error: " + e.getMessage());
        }
    }

    public boolean isLoaded() {
        return clip != null;
    }
    public boolean isPlaying() {
        return isLoaded() && clip.isRunning();
    }

    public void play(int loop) {
        if (!isLoaded()) return;
        clip.setMicrosecondPosition(0);
        clip.loop(loop);
    }
    public void play() {
        if (!isLoaded()) return;
        clip.setMicrosecondPosition(0);
        clip.start();
    }
    public void toggle() {
        if (isPlaying()) {
            pause();
        }
        else {
            resume();
        }
    }
    public void stop() {
        if (!isLoaded()) return;
        clip.stop();
    }
    public void pause() {
        stop();
    }
    public void resume() {
        if (!isLoaded()) return;
        clip.start();
    }

    public void setVolume(float volume) {
        if (!isLoaded()) return;
        if (clip.isControlSupported(FloatControl.Type.MASTER_GAIN)) {
            this.volume = Math.max(0.0f, Math.min(1.0f, volume));
            FloatControl fc = (FloatControl) clip.getControl(FloatControl.Type.MASTER_GAIN);
            float db = volume > 0 ? (float)(Math.log(volume) / Math.log(10.0) * 20.0) : fc.getMinimum(); // idk how this works
            fc.setValue(Math.max(db, fc.getMinimum()));
        }
        else {
            System.err.println("Obsidium set volume error");
        }
    }

    public float getVolume() {
        return volume;
    }

    public void close() {
        if (!isLoaded()) return;
        clip.stop();
        clip.close();
    }
}
