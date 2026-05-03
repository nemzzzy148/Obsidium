package org.obsidium.image;

import java.awt.image.BufferedImage;
import java.nio.file.Path;

import javax.imageio.ImageIO;

import org.obsidium.graphics.Surface;

public class Image {
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
}
