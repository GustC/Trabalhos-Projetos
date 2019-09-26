package webcrawler;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;

public class WebCrawler {
    
    public static final int NTHREDS = 20;
    public static final boolean SHOW_FILE_NAME = false;
    
    public static void main(String[] args) throws Exception  {  
        ArrayList<String> sites = readFile(args[0]);
        
        Buffer buffer = new Buffer();        
         
               
        ExecutorService executorProducer = Executors.newFixedThreadPool(NTHREDS);
        Thread downloaderThread = new Thread(new Consumer("Consumer",buffer,executorProducer));            
        downloaderThread.start(); 
        for (int i = 0; i < sites.size(); i++) {  
            executorProducer.execute(new Producer("Discovery["+i+"]", sites.get(i), buffer));
        }
        executorProducer.shutdown();             
        
        
    }
    
    static ArrayList<String> readFile(String src) throws FileNotFoundException, IOException{
        ArrayList<String> result = new ArrayList<String>();
        
        FileInputStream fstream_school = new FileInputStream(src);
        DataInputStream data_input = new DataInputStream(fstream_school); 
        BufferedReader buffer = new BufferedReader(new InputStreamReader(data_input));
        String str_line;
        
        while ((str_line = buffer.readLine()) != null) 
        { 
            str_line = str_line.trim(); 
            if ((str_line.length()!=0))  
            { 
                result.add(str_line);
            } 
        }
        
        return result;
    } 
    
}
