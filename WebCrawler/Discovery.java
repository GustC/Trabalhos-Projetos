package webcrawler;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Casa
 */ 
public class Discovery implements Runnable{
    
    String name;
    private String link;
    Buffer buffer;
    

    public Discovery(String name) {
        this.name = name;
    }

    public Discovery(String name, String url) throws MalformedURLException {
        this.name = name;
        this.link = url;
    }
    
    public Discovery(String name, String url, Buffer buffer) throws MalformedURLException {
        this.name = name;
        this.link = url;
        this.buffer = buffer;
    }

    public String getLink() {
        return link;
    }

    public void setLink(String link) {
        this.link = link;
    }
    
    

    @Override
    public void run() {
        
        try {
            String html = getHTML(this.link);
            ArrayList<String> links = getSrcLinks(html,this.link);
            for (int i = 0; i < links.size(); i++) {

//                Thread object = new Thread(new Downloader(this.name+"[Downloader "+i+"]",this.buffer));                    

                synchronized(this){
                    try{
//                        object.start();
                                                  
                        this.buffer.add(links.get(i));
//                        object.wait();
                    }catch(InterruptedException e){
                        e.printStackTrace();
                    }
                }

            }
        } catch (Exception ex) {
            Logger.getLogger(Discovery.class.getName()).log(Level.SEVERE, null, ex);
        } 
    }
    
    
    static public String getHTML(String url) throws Exception{
        URL link = new URL(url);
        String html = "";
        
        BufferedReader in = new BufferedReader(new InputStreamReader(link.openStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null){
            html += inputLine.trim();
        }
        in.close();
        
        return html;
    }
    
    static public ArrayList<String> getSrcLinks(String html, String link){
        ArrayList<String> srcLinks = new ArrayList<String>(); 
        Boolean find;
        int lastIndex=0,indexOcurrence,closeTag,srcFirstIndex,srcLastIndex;
        do{
            find = false;
            indexOcurrence = html.indexOf("<img ", lastIndex+1);
            if(indexOcurrence != -1){
                find = true;
                lastIndex = indexOcurrence;
                closeTag = html.indexOf(">", lastIndex);
                srcFirstIndex = html.subSequence(lastIndex, closeTag).toString().indexOf(" src=\"");
//                if(srcFirstIndex == -1){
////                    System.out.println("result = "+html.subSequence(lastIndex, closeTag).toString());
//                    int x,y;
//                    x = link.indexOf(".");
//                    y = link.substring(x).indexOf("/");
//                    String resp = "", pow = html.subSequence(lastIndex, closeTag).toString();
//                    if(x != -1 && y != -1){
//                        resp = link.subSequence(0, x+y).toString();
//                        x = pow.indexOf("data-src=");
////                        y = pow.substring(x+5).indexOf("\" ");
//                        System.out.println("opa="+pow.substring(x+8));
//                    }                    
//                    System.out.println(resp);
//                    
//                    continue;
//                }
                srcLastIndex = html.subSequence(lastIndex, closeTag).toString().indexOf("\"",srcFirstIndex+6);                
                String aux = (String) html.subSequence(lastIndex, closeTag).subSequence(srcFirstIndex+6, srcLastIndex);    
                if(aux.indexOf("://") == -1)
                    continue;
                if(aux.indexOf(".php") != -1)
                    continue;
                srcLinks.add(aux);
            }
        }while(find);
        
        return srcLinks;
    }
    
}
