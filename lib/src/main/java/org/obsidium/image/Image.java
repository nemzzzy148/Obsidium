package org.obsidium.image;

import java.awt.image.BufferedImage;
import java.nio.file.Path;

import javax.imageio.ImageIO;

import org.obsidium.graphics.Surface;

/**
 * A class designed to handle image loading.
 * 
 * @since 1.0
 */
public class Image {
    private final static String LOGO_PATH = "images/logo.png";

    /**
     * Loads the image, that can be found in the specified path, in a {@link Surface}.
     * 
     * @param path where the image can be found
     * 
     * @return the surface containing your image
     * 
     * @since 1.0
     */
    public static Surface load(String path) {
        BufferedImage bufferedImage = null;
        try {
            Path filePath = Path.of(path);
            bufferedImage = ImageIO.read(filePath.toFile());
        } catch (Exception e) {
            System.err.println("Obsidium loading image error: " + e.getMessage());
            return null;
        }
        return new Surface(bufferedImage);
    }

    /**
     * Returns a surface that contains tho logo of Obsidium.
     * 
     * <p> The logo has a resolution of 1080x1080 and it has an aspect ratio of 1:1. </p>
     * 
     * @return {@link Surface} that has the logo of Obsidium
     * 
     * @since 1.0
     */
    public static Surface logo() {
        try {
            var logo = Image.class.getClassLoader().getResource(LOGO_PATH);

            if (logo == null) {
                System.err.println("Obsidium logo error: logo.png was not found!");
                return null;
            }

            Path path = Path.of(logo.toURI());

            return load(path.toString());
        } catch (Exception e) {
            System.err.println("Obsidium logo error: " + e.getMessage());
            return null;
        }
    }
}
