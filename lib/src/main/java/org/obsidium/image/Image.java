package org.obsidium.image;

import java.awt.image.BufferedImage;
import java.nio.file.Path;

import javax.imageio.ImageIO;

import org.obsidium.graphics.Surface;

public class Image {
    private final static String LOGO_PATH = "images/logo.png";
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
