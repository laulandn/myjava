
import java.awt.*;
import java.applet.Applet;


public class environs  extends Applet{
  public void paint(Graphics g) {
    g.setColor(Color.black);
    int width = size().width;
	int height = size().height;
	/*
    Rectangle r=g.getClipBounds();
    int width =r.width;
    int height = r.height;
    */
    FontMetrics fm=g.getFontMetrics();
    int fh=fm.getHeight();
    g.drawString("java.version: "+System.getProperty("java.version"),0,fh);
    g.drawString("java.class.version: "+System.getProperty("java.class.version"),0,height/4+fh);
    g.drawString("java.vendor: "+System.getProperty("java.vendor"),0,2*(height/4)+fh);
    g.drawString("java.vendor.url: "+System.getProperty("java.vendor.url"),0,3*(height/4)+fh);
  }
}

         
