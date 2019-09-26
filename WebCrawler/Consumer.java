package webcrawler;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import static webcrawler.WebCrawler.NTHREDS;


public class Consumer implements Runnable{
    final static String DIR_URL = System.getProperty("user.dir");
    private URL linkURLImage;
    String name;
    Buffer buffer;
    ExecutorService producerExecutor;

    public Consumer(String thread) {
        this.name = thread;
    }    
    
    public Consumer(String thread,String url) throws MalformedURLException {
        this.name = thread;
        this.linkURLImage = new URL(url);
    }
    
    public Consumer(String thread,String url, Buffer buffer) throws MalformedURLException {
        this.name = thread;
        this.linkURLImage = new URL(url);
        this.buffer = buffer;
    }
    public Consumer(String thread, Buffer buffer) throws MalformedURLException {
        this.name = thread;
        this.buffer = buffer;
    }
    
    public Consumer(String thread, Buffer buffer, ExecutorService producerExecutor) throws MalformedURLException {
        this.name = thread;
        this.buffer = buffer;
        this.producerExecutor = producerExecutor;
    }

    @Override
    public void run() {        
        try{            
            
            ExecutorService executor = Executors.newFixedThreadPool(NTHREDS);
//            executor.awaitTermination(5, TimeUnit.MILLISECONDS);
            System.out.println(this.name+" - Running...");              
            String type,urlSrc;
            
//            synchronized(this){                 
                while(true){                    
                    urlSrc = this.buffer.getLast();                                
                    if(urlSrc.lastIndexOf(".png") > -1){
                        type = "png";
                    } else if (urlSrc.lastIndexOf(".jpeg") > -1){
                        type = "jpeg";
                    } else {
                        type = "jpg";
                    } 
                    int start = urlSrc.lastIndexOf("/");
                    String fileName = urlSrc.substring(start+1, urlSrc.length());
                    int indexLastType = fileName.lastIndexOf("."+type);
                    if(indexLastType != -1 ){
                        fileName = (String) fileName.subSequence(0, indexLastType+type.length()+1);
                    }
                    executor.execute(new Downloader(urlSrc, fileName, type));
                    
                    if(this.producerExecutor.isTerminated() && buffer.isStoped()){
                        break;
                    }
                }
//            }            
                executor.shutdown();
                System.out.println(this.name+" - end");
//            System.out.println(this.name+" End.");  
        }catch (Exception e) {
            e.printStackTrace();
//            System.out.println(e.getMessage());
        }           

    }
    
    
}
