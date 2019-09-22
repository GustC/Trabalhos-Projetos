package webcrawler;

import java.util.ArrayList;


public class Buffer {
    ArrayList<String> buffer;
    int lastReadIndex;
    int maxSize;
    Boolean inWork, inRemove;

    public Buffer() {
        this.buffer = new ArrayList<>();
        this.lastReadIndex = 0;
        this.inWork = false;
        this.inRemove = false;
        this.maxSize = 20;
    }    
    
    public void add(String link) throws InterruptedException{
        synchronized(this){ 
            while(this.isFull()){
                this.wait();
            }
            if(this.inWork){
                this.wait();
            }            
            this.inWork = true;
            this.buffer.add(link);
            this.inWork = false;
            this.notify();
        }
        
    }
    
    public String getFirst(){
        String result = this.buffer.get(this.lastReadIndex);
        this.remove(this.lastReadIndex);
        this.lastReadIndex++;
        return result;
    }
    
    public String getLast() throws InterruptedException{
        
        String result;
        synchronized(this){ 
            while(this.isEmpty()){                
                this.wait();            
            }
            if(this.inRemove){
                System.out.println("inRemove - waiting...");
                this.wait();
                System.out.println("inRemove - return");
            }            
            this.inRemove = true;
            int index = this.buffer.size();
            result = this.buffer.get(index-1);                
            this.buffer.remove(index-1);
            this.inRemove = false;
            this.notify();
        }
        return result;
    }
    
    public void remove(int index){
        this.buffer.remove(index);
    }
    
    public int firstIndex(){
        return this.lastReadIndex;
    }
    
    public Boolean isEmpty(){
        return this.buffer.isEmpty();
    }
    
    public Boolean isFull(){
        if(this.buffer.size() == this.maxSize)
            return true;
        return false;
    }
    
    public Boolean isStoped(){
        if(this.isEmpty() && !this.inWork && !this.inRemove)
            return true;
        return false;
    }
    
}
