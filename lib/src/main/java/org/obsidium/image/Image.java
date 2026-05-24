package org.obsidium.image;

import java.awt.image.BufferedImage;
import java.nio.file.Path;

import javax.imageio.ImageIO;

import org.obsidium.graphics.SimpleSurface;
import org.obsidium.graphics.Surface;
import org.obsidium.window.Window;

/**
 * A class designed to handle image functionality.
 * @since 1.0
 */
public class Image {
    private final static String LOGO_PATH = "images/logo.png";

    /**
     * Loads the image, that can be found in the specified path, in a {@link Surface}.
     * @param path where the image can be found
     * @return the surface containing your image
     * @since 1.0
     */
    public static Surface load(String path) {
        BufferedImage bufferedImage = null;
        try {
            var stream = Image.class.getClassLoader().getResourceAsStream(path);
            assert stream != null;
            bufferedImage = ImageIO.read(stream);
        } catch (Exception e) {
            System.err.println("Obsidium loading image error: " + e.getMessage());
            return null;
        }
        return new Surface(bufferedImage);
    }

    private static Surface load(String path, boolean resources) {
        if (resources) {
            return load(path);
        }
        else {
            BufferedImage bI = null;
            try {
                Path p = Path.of(path);
                bI = ImageIO.read(p.toFile());
            }
            catch (Exception e) {
                System.err.println("Obsidium loading image error: " + e.getMessage());
                return null;
            }
            return new Surface(bI);
        }
    }

    /**
     * Saves the content of the surface / window that is currently being displayed.
     * @param surface that needs to be saved
     * @param format that the image uses
     * @param path where the image will be saved + the name
     * @since 1.2
     */
    public static void save(SimpleSurface surface, Format format, String path) {
        try {
            Path filePath = Path.of(path);
            boolean result = ImageIO.write(surface.getBufferedImage(), formatToExtension(format), filePath.toFile());
            if (!result) {
                throw new IllegalArgumentException("Format isn't supported!");
            }
        } catch (Exception e) {
            System.err.println("Obsidium saving image error: " + e.getMessage());
            e.printStackTrace();
        }

    }

    /**
     * Returns a surface that contains tho logo of Obsidium.
     * <p> The logo has a resolution of 1080x1080, and it has an aspect ratio of 1:1. </p>
     * @return {@link Surface} that has the logo of Obsidium
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

            return load(path.toString(), false);
        } catch (Exception e) {
            System.err.println("Obsidium logo error: " + e.getMessage());
            return null;
        }
    }

    private static String formatToExtension (Format format) {
        String f = "";
        switch (format) {
            case BMP -> f = "bmp";
            case JPG -> f = "jpg";
            case PNG -> f = "png";
        }
        return f;
    }
}
