public class Media {
   
    private String title;
    private String url;
        
    public Media(String title, String url) {
        this.title = title;
        this. url = url;
    }
       
    @Override 
    public String toString() {
        return title + " (" + url + ")";
    }
}