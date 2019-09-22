package webcrawler;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

public class WebCrawler {
    
    public static void main(String[] args) throws Exception  {  
        ArrayList<String> sites = readFile(args[0]);
        
        Buffer buffer = new Buffer();
        String html;    
        
//        sites.add("https://www.todamateria.com.br/estrelas/");
//        sites.add("http://www.unicap.br/home");
//        sites.add("https://mundoeducacao.bol.uol.com.br/geografia/montanhas.htm");
//        sites.add("https://www.japan-guide.com/e/e2011_species.html");
//        sites.add("http://astro.if.ufrgs.br/const.htm");
                   
        
        for (int i = 0; i < sites.size(); i++) {            
            Thread discoveryThread = new Thread(new Discovery("Discovery["+i+"]", sites.get(i), buffer));  
            Thread downloaderThread = new Thread(new Downloader("Downloader["+i+"]",buffer));        
            discoveryThread.start(); 
            downloaderThread.start();
        }
        
        
        
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
