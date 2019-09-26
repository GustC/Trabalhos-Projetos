/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package webcrawler;

import java.awt.image.BufferedImage;
import java.io.File;
import java.net.URL;
import javax.imageio.ImageIO;
import static webcrawler.Consumer.DIR_URL;
import static webcrawler.WebCrawler.SHOW_FILE_NAME;

/**
 *
 * @author Casa
 */
public class Downloader implements Runnable{
    
    String url;
    String fileName;
    String type;

    public Downloader(String url, String fileName, String type) {
        this.url = url;
        this.fileName = fileName;
        this.type = type;
    }

    @Override
    public void run() {
        try {
            URL linkImgSrc = new URL(this.url);
            BufferedImage image = null;
            image = ImageIO.read(linkImgSrc);            
            if(SHOW_FILE_NAME)
                System.out.println(this.fileName);
            ImageIO.write(image, this.type, new File(DIR_URL+"\\src\\tmp\\"+this.fileName));
        } catch ( Exception e ){
            System.out.println(e.getMessage());
        }
    }
    
}
