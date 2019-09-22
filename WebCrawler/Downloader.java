package webcrawler;

import java.awt.image.BufferedImage;
import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import javax.imageio.ImageIO;


public class Downloader implements Runnable{
    final static String DIR_URL = System.getProperty("user.dir");
    private URL linkURLImage;
    String name;
    Buffer buffer;

    public Downloader(String thread) {
        this.name = thread;
    }    
    
    public Downloader(String thread,String url) throws MalformedURLException {
        this.name = thread;
        this.linkURLImage = new URL(url);
    }
    
    public Downloader(String thread,String url, Buffer buffer) throws MalformedURLException {
        this.name = thread;
        this.linkURLImage = new URL(url);
        this.buffer = buffer;
    }
    public Downloader(String thread, Buffer buffer) throws MalformedURLException {
        this.name = thread;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        BufferedImage image = null;
        try{
            
            System.out.println(this.name+" Running...");              
            String type,urlSrc;
            synchronized(this){                 
                while(true){                    
                    urlSrc = this.buffer.getLast();                                
                    if(urlSrc.lastIndexOf(".png") > -1){
                        type = "png";
                    } else {
                        type = "jpg";
                    } 
                    int start = urlSrc.lastIndexOf("/");
                    String fileName = urlSrc.substring(start+1, urlSrc.length());
                    int indexLastType = fileName.lastIndexOf("."+type);
                    if(indexLastType != -1 )
                        fileName = (String) fileName.subSequence(0, indexLastType+4);
                    URL linkImgSrc = new URL(urlSrc);

                    image = ImageIO.read(linkImgSrc);
                    System.out.println(fileName);
                    ImageIO.write(image, type, new File(DIR_URL+"\\src\\tmp\\"+fileName));
                    if(this.buffer.isStoped())
                        break;                    
                }
                notify();
            }            
            
            
//            System.out.println(this.name+" End.");  
        }catch (Exception e) {
            e.printStackTrace();
//            System.out.println(e.getMessage());
        }           

    }
    
    
}
