
import java.awt.*;
import java.applet.Applet;

public class lines extends Applet {

  public void paint (Graphics g) {
    int width=getSize().width;
    int height=getSize().height;
    int wfactor=0xffffff/width;
    int hfactor=0xffffff/height;
    for(int t=0;t<width;t++) {
      int tcolor=t*wfactor;
      g.setColor(new Color((tcolor&0xff0000)>>16,(tcolor&0xff00)>>8,tcolor&0xff));
      g.drawLine(t,0,width-t,height);
    }
    for(int t=0;t<height;t++) {
      int tcolor=t*hfactor;
      g.setColor(new Color((tcolor&0xff0000)>>16,(tcolor&0xff00)>>8,tcolor&0xff));
      g.drawLine(0,t,width,height-t);
    }
  }
}
