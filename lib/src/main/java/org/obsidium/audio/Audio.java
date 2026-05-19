package org.obsidium.audio;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.FloatControl;

/**
 * A class for playing .wav audio files.
 * 
 * <p> To use the functionality of this audio class, it needs to be instantiated.</p>
 * 
 * @see #Audio(String path)
 * 
 * 
 * @since 1.0
 */
public class Audio {
    private Clip clip;
    private float volume = 1.0f;

    /**
     * The constructor of the audio class.
     * 
     * @param path of the .wav audio file that you want to load in
     * 
     * @since 1.0
     */
    public Audio(String path) {
        try (AudioInputStream audioStream = AudioSystem.getAudioInputStream(Audio.class.getClassLoader().getResource(path))) {
            clip = AudioSystem.getClip();
            clip.open(audioStream);
        }
        catch (Exception e) {
            System.err.println("Obsidium audio loading error: " + e.getMessage());
        }
    }

    /**
     * @return {@code true} if the audio file is loaded in.
     * 
     * @since 1.0
     */
    public boolean isLoaded() {
        return clip != null;
    }

    /**
     * @return {@code true} if the audio file is playing.
     * 
     * @since 1.0
     */
    public boolean isPlaying() {
        return isLoaded() && clip.isRunning();
    }

    /**
     * Plays and loops the audio.
     * 
     * <p> If the audio isn't loaded in, it will do nothing.
     * Otherwise, it will loop how many times you have specified it to.
     * If the argument is {@code -1}, it will loop indefinitely.</p>
     * 
     * @param loop loops the audio a specified set of times, if {@code -1} it will loop indefinitely
     * 
     * @since 1.0
     */
    public void play(int loop) {
        if (!isLoaded()) return;
        clip.setMicrosecondPosition(0);
        clip.loop(loop);
    }

    /**
     * Plays the audio.
     * 
     * <p> If the audio isn't loaded in, it will do nothing.
     * Otherwise, it will begin playing 1 time.</p>
     * 
     * @since 1.0
     */
    public void play() {
        if (!isLoaded()) return;
        clip.setMicrosecondPosition(0);
        clip.start();
    }

    /**
     * Toggles between pausing/resuming.
     * 
     * @since 1.0
     */
    public void toggle() {
        if (isPlaying()) {
            pause();
        }
        else {
            resume();
        }
    }

    /**
     * Stops the music that is currently playing.
     * 
     * <p> If {@link #resume()} is called after the audio has stopped, it will just continue playing.</p>
     * 
     * <p>If the audio has not been loaded in, it will do nothing.
     * You can check if the audio has been loaded in with this {@link #isLoaded()} method. </p>
     * 
     * @since 1.0
     */
    public void stop() {
        if (!isLoaded()) return;
        clip.stop();
    }

    /**
     * Pauses the audio that is currently playing.
     * 
     * <p>If the song has not been loaded in, it will do nothing.
     * You can check if the audio has been loaded in with this {@link #isLoaded()} method. </p>
     * 
     * @since 1.0
     */
    public void pause() {
        stop();
    }

    /**
     * Resumes the audio that is currently playing.
     * 
     * <p>If the audio has not been loaded in, it will do nothing.
     * You can check if the audio has been loaded in with this {@link #isLoaded()} method. </p>
     */
    public void resume() {
        if (!isLoaded()) return;
        clip.start();
    }

    /**
     * Sets the volume of the audio.
     * 
     * <p>If the audio has not been loaded in, it will do nothing.
     * You can check if the audio has been loaded in with this {@link #isLoaded()} method. </p>
     * 
     * @param volume a value between 0 - 1
     * 
     * @since 1.0
     */
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

    /**
     * Returns the volume of the audio.
     * 
     * <p> The audio will be between 0 and 1.
     * 
     * @return volume
     * 
     * @since 1.0
     */
    public float getVolume() {
        return volume;
    }

    /**
     * Closes and releases the memory of the audio.
     * 
     * @since 1.0
     */
    public void close() {
        if (!isLoaded()) return;
        clip.stop();
        clip.close();
    }
}
